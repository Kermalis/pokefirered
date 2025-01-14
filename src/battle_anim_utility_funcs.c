#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "malloc.h"
#include "palette.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "util.h"
#include "constants/songs.h"

struct AnimStatsChangeData
{
    u8 battler1;
    u8 battler2;
    u8 higherPriority;
    s16 data[8];
    u16 species;
};

static void StartBlendAnimSpriteColor(u8 taskId, u32 selectedPalettes);
static void AnimTask_BlendSpriteColor_Step2(u8 taskId);
static void sub_80BAB78(u8 taskId);
static void sub_80BABD0(u8 taskId);
static void sub_80BACA8(struct Sprite *sprite);
static void sub_80BAF38(u8 taskId);
static void sub_80BB0D8(u8 taskId);
static void sub_80BB2A0(u8 taskId);
static void sub_80BB4B8(u8 taskId);
static void sub_80BB6CC(u8 taskId);
static void sub_80BB790(u32 selectedPalettes, u16 color);
static void sub_80BB8A4(u8 taskId);
static void sub_80BBC2C(u8 taskId);
static void sub_80BC19C(u8 taskId);

static EWRAM_DATA struct AnimStatsChangeData *sAnimStatsChangeData = NULL;

static const u16 gUnknown_83E7CC8[] = { RGB(31, 31, 31) };
const u8 gUnknown_83E7CCA[] = { REG_OFFSET_BG0CNT, REG_OFFSET_BG1CNT, REG_OFFSET_BG2CNT, REG_OFFSET_BG3CNT };
const u8 gUnknown_83E7CCE[] = { REG_OFFSET_BG0CNT, REG_OFFSET_BG1CNT, REG_OFFSET_BG2CNT, REG_OFFSET_BG3CNT };

void sub_80BA7F8(u8 taskId)
{
    u32 selectedPalettes = UnpackSelectedBattleAnimPalettes(gBattleAnimArgs[0]);
    
    selectedPalettes |= sub_8075CB8((gBattleAnimArgs[0] >>  7) & 1,
                                    (gBattleAnimArgs[0] >>  8) & 1,
                                    (gBattleAnimArgs[0] >>  9) & 1,
                                    (gBattleAnimArgs[0] >> 10) & 1);
    StartBlendAnimSpriteColor(taskId, selectedPalettes);
}

void sub_80BA83C(u8 taskId)
{
    u8 battler;
    u32 selectedPalettes;
    u8 animBattlers[2];

    animBattlers[1] = 0xFF;
    selectedPalettes = UnpackSelectedBattleAnimPalettes(1);
    switch (gBattleAnimArgs[0])
    {
    case 2:
        selectedPalettes = 0;
        // fall through
    case 0:
        animBattlers[0] = gBattleAnimAttacker;
        break;
    case 3:
        selectedPalettes = 0;
        // fall through
    case 1:
        animBattlers[0] = gBattleAnimTarget;
        break;
    case 4:
        animBattlers[0] = gBattleAnimAttacker;
        animBattlers[1] = gBattleAnimTarget;
        break;
    case 5:
        animBattlers[0] = 0xFF;
        break;
    case 6:
        selectedPalettes = 0;
        animBattlers[0] = BATTLE_PARTNER(gBattleAnimAttacker);
        break;
    case 7:
        selectedPalettes = 0;
        animBattlers[0] = BATTLE_PARTNER(gBattleAnimTarget);
        break;
    }
    for (battler = 0; battler < MAX_BATTLERS_COUNT; ++battler)
    {
        if (battler != animBattlers[0] 
         && battler != animBattlers[1]
         && IsBattlerSpriteVisible(battler))
            selectedPalettes |= 0x10000 << sub_8075D80(battler);
    }
    StartBlendAnimSpriteColor(taskId, selectedPalettes);
}

void AnimTask_SetCamouflageBlend(u8 taskId)
{
    u32 selectedPalettes = UnpackSelectedBattleAnimPalettes(gBattleAnimArgs[0]);
    
    switch (gBattleTerrain)
    {
    case BATTLE_TERRAIN_GRASS:
        gBattleAnimArgs[4] = RGB(12, 24, 2);
        break;
    case BATTLE_TERRAIN_LONG_GRASS:
        gBattleAnimArgs[4] = RGB(0, 15, 2);
        break;
    case BATTLE_TERRAIN_SAND:
        gBattleAnimArgs[4] = RGB(30, 24, 11);
        break;
    case BATTLE_TERRAIN_UNDERWATER:
        gBattleAnimArgs[4] = RGB(0, 0, 18);
        break;
    case BATTLE_TERRAIN_WATER:
        gBattleAnimArgs[4] = RGB(11, 22, 31);
        break;
    case BATTLE_TERRAIN_POND:
        gBattleAnimArgs[4] = RGB(11, 22, 31);
        break;
    case BATTLE_TERRAIN_MOUNTAIN:
        gBattleAnimArgs[4] = RGB(22, 16, 10);
        break;
    case BATTLE_TERRAIN_CAVE:
        gBattleAnimArgs[4] = RGB(14, 9, 3);
        break;
    case BATTLE_TERRAIN_BUILDING:
        gBattleAnimArgs[4] = RGB(31, 31, 31);
        break;
    case BATTLE_TERRAIN_PLAIN:
        gBattleAnimArgs[4] = RGB(31, 31, 31);
        break;
    }
    StartBlendAnimSpriteColor(taskId, selectedPalettes);
}

void AnimTask_BlendParticle(u8 taskId)
{
    u8 paletteIndex = IndexOfSpritePaletteTag(gBattleAnimArgs[0]);
    u32 selectedPalettes = 1 << (paletteIndex + 16);

    StartBlendAnimSpriteColor(taskId, selectedPalettes);
}

static void StartBlendAnimSpriteColor(u8 taskId, u32 selectedPalettes)
{
    gTasks[taskId].data[0] = selectedPalettes;
    gTasks[taskId].data[1] = selectedPalettes >> 16;
    gTasks[taskId].data[2] = gBattleAnimArgs[1];
    gTasks[taskId].data[3] = gBattleAnimArgs[2];
    gTasks[taskId].data[4] = gBattleAnimArgs[3];
    gTasks[taskId].data[5] = gBattleAnimArgs[4];
    gTasks[taskId].data[10] = gBattleAnimArgs[2];
    gTasks[taskId].func = AnimTask_BlendSpriteColor_Step2;
    gTasks[taskId].func(taskId);
}

static void AnimTask_BlendSpriteColor_Step2(u8 taskId)
{
    u32 selectedPalettes;
    u16 singlePaletteMask = 0;

    if (gTasks[taskId].data[9] == gTasks[taskId].data[2])
    {
        gTasks[taskId].data[9] = 0;
        selectedPalettes = gTasks[taskId].data[0] | (gTasks[taskId].data[1] << 16);
        while (selectedPalettes)
        {
            if (selectedPalettes & 1)
                BlendPalette(singlePaletteMask, 16, gTasks[taskId].data[10], gTasks[taskId].data[5]);
            singlePaletteMask += 0x10;
            selectedPalettes >>= 1;
        }
        if (gTasks[taskId].data[10] < gTasks[taskId].data[4])
            ++gTasks[taskId].data[10];
        else if (gTasks[taskId].data[10] > gTasks[taskId].data[4])
            --gTasks[taskId].data[10];
        else
            DestroyAnimVisualTask(taskId);
    }
    else
    {
        ++gTasks[taskId].data[9];
    }
}

void sub_80BAB38(u8 taskId)
{
    BeginHardwarePaletteFade(gBattleAnimArgs[0],
                             gBattleAnimArgs[1],
                             gBattleAnimArgs[2],
                             gBattleAnimArgs[3],
                             gBattleAnimArgs[4]);
    gTasks[taskId].func = sub_80BAB78;
}

static void sub_80BAB78(u8 taskId)
{
    if (!gPaletteFade.active)
        DestroyAnimVisualTask(taskId);
}

void sub_80BAB98(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    task->data[0] = gBattleAnimArgs[0];
    task->data[1] = 0;
    task->data[2] = gBattleAnimArgs[1];
    task->data[3] = gBattleAnimArgs[2];
    task->data[4] = gBattleAnimArgs[3];
    task->data[5] = 0;
    task->func = sub_80BABD0;
}
static void sub_80BABD0(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    if (task->data[4])
    {
        if (task->data[1])
        {
            --task->data[1];
        }
        else
        {
            task->data[6] = CloneBattlerSpriteWithBlend(task->data[0]);
            if (task->data[6] >= 0)
            {
                gSprites[task->data[6]].oam.priority = task->data[0] ? 1 : 2;
                gSprites[task->data[6]].data[0] = task->data[3];
                gSprites[task->data[6]].data[1] = taskId;
                gSprites[task->data[6]].data[2] = 5;
                gSprites[task->data[6]].callback = sub_80BACA8;
                ++task->data[5];
            }
            --task->data[4];
            task->data[1] = task->data[2];
        }
    }
    else if (task->data[5] == 0)
    {
        DestroyAnimVisualTask(taskId);
    }
}

static void sub_80BACA8(struct Sprite *sprite)
{
    if (sprite->data[0])
    {
        --sprite->data[0];
    }
    else
    {
        --gTasks[sprite->data[1]].data[sprite->data[2]];
        obj_delete_but_dont_free_vram(sprite);
    }
}

void sub_80BACEC(u8 taskId)
{
    u16 species;
    s32 newSpriteId;
    u16 var0;
    u16 bg1Cnt;
    u8 spriteId;
    struct BattleAnimBgData animBgData;

    var0 = 0;
    gBattle_WIN0H = 0;
    gBattle_WIN0V = 0;
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR
                              | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG2 | WINOUT_WIN01_BG3 | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR
                               | WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR);
    SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG1 | BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(8, 12));
    bg1Cnt = GetGpuReg(REG_OFFSET_BG1CNT);
    ((struct BgCnt *)&bg1Cnt)->priority = 0;
    ((struct BgCnt *)&bg1Cnt)->screenSize = 0;
    SetGpuReg(REG_OFFSET_BG1CNT, bg1Cnt);
    if (!IsContest())
    {
        ((struct BgCnt *)&bg1Cnt)->charBaseBlock = 1;
        SetGpuReg(REG_OFFSET_BG1CNT, bg1Cnt);
    }
    if (IsDoubleBattle() && !IsContest())
    {
        if (GetBattlerPosition(gBattleAnimAttacker) == B_POSITION_OPPONENT_RIGHT
         || GetBattlerPosition(gBattleAnimAttacker) == B_POSITION_PLAYER_LEFT)
        {
            if (IsBattlerSpriteVisible(BATTLE_PARTNER(gBattleAnimAttacker)) == TRUE)
            {
                gSprites[gBattlerSpriteIds[BATTLE_PARTNER(gBattleAnimAttacker)]].oam.priority -= 1;
                ((struct BgCnt *)&bg1Cnt)->priority = 1;
                SetGpuReg(REG_OFFSET_BG1CNT, bg1Cnt);
                var0 = 1;
            }
        }
    }
    if (GetBattlerSide(gBattleAnimAttacker) != B_SIDE_PLAYER)
        species = GetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattleAnimAttacker]], MON_DATA_SPECIES);
    else
        species = GetMonData(&gPlayerParty[gBattlerPartyIndexes[gBattleAnimAttacker]], MON_DATA_SPECIES);
    spriteId = GetAnimBattlerSpriteId(0);
    newSpriteId = sub_8076E34(gBattleAnimAttacker, spriteId, species);
    sub_80752A0(&animBgData);
    AnimLoadCompressedBgTilemap(animBgData.bgId, gFile_graphics_battle_anims_masks_curse_tilemap);
    if (IsContest())
        sub_80730C0(animBgData.paletteId, animBgData.bgTilemap, 0, 0);
    AnimLoadCompressedBgGfx(animBgData.bgId, gFile_graphics_battle_anims_masks_curse_sheet, animBgData.tilesOffset);
    LoadPalette(gUnknown_83E7CC8, animBgData.paletteId * 16 + 1, 2);
    gBattle_BG1_X = -gSprites[spriteId].pos1.x + 32;
    gBattle_BG1_Y = -gSprites[spriteId].pos1.y + 32;
    gTasks[taskId].data[0] = newSpriteId;
    gTasks[taskId].data[6] = var0;
    gTasks[taskId].func = sub_80BAF38;
}

static void sub_80BAF38(u8 taskId)
{
    struct BattleAnimBgData animBgData;
    struct Sprite *sprite;
    u16 bg1Cnt;

    gTasks[taskId].data[10] += 4;
    gBattle_BG1_Y -= 4;
    if (gTasks[taskId].data[10] == 64)
    {
        gTasks[taskId].data[10] = 0;
        gBattle_BG1_Y += 64;
        if (++gTasks[taskId].data[11] == 4)
        {
            sub_8073128(0);
            gBattle_WIN0H = 0;
            gBattle_WIN0V = 0;
            SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR
                                      | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR);
            SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG_ALL  | WINOUT_WIN01_OBJ  | WINOUT_WIN01_CLR
                                       | WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR);
            if (!IsContest())
            {
                bg1Cnt = GetGpuReg(REG_OFFSET_BG1CNT);
                ((struct BgCnt *)&bg1Cnt)->charBaseBlock = 0;
                SetGpuReg(REG_OFFSET_BG1CNT, bg1Cnt);
            }
            SetGpuReg(REG_OFFSET_DISPCNT, GetGpuReg(REG_OFFSET_DISPCNT) ^ DISPCNT_OBJWIN_ON);
            SetGpuReg(REG_OFFSET_BLDCNT, 0);
            SetGpuReg(REG_OFFSET_BLDALPHA, 0);
            sprite = &gSprites[GetAnimBattlerSpriteId(0)]; // unused
            sprite = &gSprites[gTasks[taskId].data[0]];
            DestroySprite(sprite);
            sub_80752A0(&animBgData);
            sub_8075358(animBgData.bgId);
            if (gTasks[taskId].data[6] == 1)
                ++gSprites[gBattlerSpriteIds[BATTLE_PARTNER(gBattleAnimAttacker)]].oam.priority;
            gBattle_BG1_Y = 0;
            DestroyAnimVisualTask(taskId);
        }
    }
}

void sub_80BB088(u8 taskId)
{
    u8 i;

    sAnimStatsChangeData = AllocZeroed(sizeof(struct AnimStatsChangeData));
    for (i = 0; i < 8; ++i)
        sAnimStatsChangeData->data[i] = gBattleAnimArgs[i];
    gTasks[taskId].func = sub_80BB0D8;
}

static void sub_80BB0D8(u8 taskId)
{
    if (sAnimStatsChangeData->data[2] == 0)
        sAnimStatsChangeData->battler1 = gBattleAnimAttacker;
    else
        sAnimStatsChangeData->battler1 = gBattleAnimTarget;
    sAnimStatsChangeData->battler2 = BATTLE_PARTNER(sAnimStatsChangeData->battler1);
    if (IsContest() || (sAnimStatsChangeData->data[3] && !IsBattlerSpriteVisible(sAnimStatsChangeData->battler2)))
        sAnimStatsChangeData->data[3] = 0;
    gBattle_WIN0H = 0;
    gBattle_WIN0V = 0;
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR
                              | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG2 | WINOUT_WIN01_BG3 | WINOUT_WIN01_OBJ  | WINOUT_WIN01_CLR
                               | WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR);
    SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG1 | BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 16));
    SetAnimBgAttribute(1, BG_ANIM_PRIORITY, 0);
    SetAnimBgAttribute(1, BG_ANIM_SCREEN_SIZE, 0);
    if (!IsContest())
        SetAnimBgAttribute(1, BG_ANIM_CHAR_BASE_BLOCK, 1);
    if (IsDoubleBattle() && sAnimStatsChangeData->data[3] == 0)
    {
        if (GetBattlerPosition(sAnimStatsChangeData->battler1) == B_POSITION_OPPONENT_RIGHT
         || GetBattlerPosition(sAnimStatsChangeData->battler1) == B_POSITION_PLAYER_LEFT)
        {
            if (IsBattlerSpriteVisible(sAnimStatsChangeData->battler2) == TRUE)
            {
                gSprites[gBattlerSpriteIds[sAnimStatsChangeData->battler2]].oam.priority -= 1;
                SetAnimBgAttribute(1, BG_ANIM_PRIORITY, 1);
                sAnimStatsChangeData->higherPriority = 1;
            }
        }
    }
    if (GetBattlerSide(sAnimStatsChangeData->battler1) != B_SIDE_PLAYER)
        sAnimStatsChangeData->species = GetMonData(&gEnemyParty[gBattlerPartyIndexes[sAnimStatsChangeData->battler1]], MON_DATA_SPECIES);
    else
        sAnimStatsChangeData->species = GetMonData(&gPlayerParty[gBattlerPartyIndexes[sAnimStatsChangeData->battler1]], MON_DATA_SPECIES);
    gTasks[taskId].func = sub_80BB2A0;
}

static void sub_80BB2A0(u8 taskId)
{
    struct BattleAnimBgData animBgData;
    u8 spriteId, newSpriteId = 0;
    u8 battlerSpriteId;

    battlerSpriteId = gBattlerSpriteIds[sAnimStatsChangeData->battler1];
    spriteId = sub_8076E34(sAnimStatsChangeData->battler1, battlerSpriteId, sAnimStatsChangeData->species);
    if (sAnimStatsChangeData->data[3])
    {
        battlerSpriteId = gBattlerSpriteIds[sAnimStatsChangeData->battler2];
        newSpriteId = sub_8076E34(sAnimStatsChangeData->battler2, battlerSpriteId, sAnimStatsChangeData->species);
    }
    sub_80752A0(&animBgData);
    if (sAnimStatsChangeData->data[0] == 0)
        AnimLoadCompressedBgTilemap(animBgData.bgId, gBattleStatMask1_Tilemap);
    else
        AnimLoadCompressedBgTilemap(animBgData.bgId, gBattleStatMask2_Tilemap);
    if (IsContest())
        sub_80730C0(animBgData.paletteId, animBgData.bgTilemap, 0, 0);
    AnimLoadCompressedBgGfx(animBgData.bgId, gBattleStatMask_Gfx, animBgData.tilesOffset);
    switch (sAnimStatsChangeData->data[1])
    {
    case 0:
        LoadCompressedPalette(gBattleStatMask2_Pal, animBgData.paletteId * 16, 32);
        break;
    case 1:
        LoadCompressedPalette(gBattleStatMask1_Pal, animBgData.paletteId * 16, 32);
        break;
    case 2:
        LoadCompressedPalette(gBattleStatMask3_Pal, animBgData.paletteId * 16, 32);
        break;
    case 3:
        LoadCompressedPalette(gBattleStatMask4_Pal, animBgData.paletteId * 16, 32);
        break;
    case 4:
        LoadCompressedPalette(gBattleStatMask6_Pal, animBgData.paletteId * 16, 32);
        break;
    case 5:
        LoadCompressedPalette(gBattleStatMask7_Pal, animBgData.paletteId * 16, 32);
        break;
    case 6:
        LoadCompressedPalette(gBattleStatMask8_Pal, animBgData.paletteId * 16, 32);
        break;
    default:
        LoadCompressedPalette(gBattleStatMask5_Pal, animBgData.paletteId * 16, 32);
        break;
    }
    gBattle_BG1_X = 0;
    gBattle_BG1_Y = 0;
     if (sAnimStatsChangeData->data[0] == 1)
    {
        gBattle_BG1_X = 64;
        gTasks[taskId].data[1] = -3;
    }
    else
    {
        gTasks[taskId].data[1] = 3;
    }

    if (sAnimStatsChangeData->data[4] == 0)
    {
        gTasks[taskId].data[4] = 10;
        gTasks[taskId].data[5] = 20;
    }
    else
    {
        gTasks[taskId].data[4] = 13;
        gTasks[taskId].data[5] = 30;
    }
    gTasks[taskId].data[0] = spriteId;
    gTasks[taskId].data[2] = sAnimStatsChangeData->data[3];
    gTasks[taskId].data[3] = newSpriteId;
    gTasks[taskId].data[6] = sAnimStatsChangeData->higherPriority;
    gTasks[taskId].data[7] = gBattlerSpriteIds[sAnimStatsChangeData->battler2];
    gTasks[taskId].func = sub_80BB4B8;
    if (sAnimStatsChangeData->data[0] == 0)
        PlaySE12WithPanning(SE_W287, BattleAnimAdjustPanning2(PAN_SIDE_PLAYER));
    else
        PlaySE12WithPanning(SE_W287B, BattleAnimAdjustPanning2(PAN_SIDE_PLAYER));
}

static void sub_80BB4B8(u8 taskId)
{
    gBattle_BG1_Y += gTasks[taskId].data[1];
    switch (gTasks[taskId].data[15])
    {
    case 0:
        if (gTasks[taskId].data[11]++ > 0)
        {
            gTasks[taskId].data[11] = 0;
            ++gTasks[taskId].data[12];
            SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(gTasks[taskId].data[12], 16 - gTasks[taskId].data[12]));
            if (gTasks[taskId].data[12] == gTasks[taskId].data[4])
                ++gTasks[taskId].data[15];
        }
        break;
    case 1:
        if (++gTasks[taskId].data[10] == gTasks[taskId].data[5])
            ++gTasks[taskId].data[15];
        break;
    case 2:
        if (gTasks[taskId].data[11]++ > 0)
        {
            gTasks[taskId].data[11] = 0;
            --gTasks[taskId].data[12];
            SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(gTasks[taskId].data[12], 16 - gTasks[taskId].data[12]));
            if (gTasks[taskId].data[12] == 0)
            {
                sub_8073128(0);
                ++gTasks[taskId].data[15];
            }
        }
        break;
    case 3:
        gBattle_WIN0H = 0;
        gBattle_WIN0V = 0;
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR
                                  | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG_ALL  | WINOUT_WIN01_OBJ  | WINOUT_WIN01_CLR
                                   | WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR);
        if (!IsContest())
            SetAnimBgAttribute(1, BG_ANIM_CHAR_BASE_BLOCK, 0);
        SetGpuReg(REG_OFFSET_DISPCNT, GetGpuReg(REG_OFFSET_DISPCNT) ^ DISPCNT_OBJWIN_ON);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        DestroySprite(&gSprites[gTasks[taskId].data[0]]);
        if (gTasks[taskId].data[2])
            DestroySprite(&gSprites[gTasks[taskId].data[3]]);
        if (gTasks[taskId].data[6] == 1)
            ++gSprites[gTasks[taskId].data[7]].oam.priority;
        Free(sAnimStatsChangeData);
        sAnimStatsChangeData = NULL;
        DestroyAnimVisualTask(taskId);
        break;
    }
}

void sub_80BB660(u8 taskId)
{
    u32 selectedPalettes = sub_8075CB8(1, 1, 1, 1);

    sub_80BB790(selectedPalettes, 0);
    gTasks[taskId].data[14] = selectedPalettes >> 16;
    selectedPalettes = sub_8075BE8(1, 0, 0, 0, 0, 0, 0) & 0xFFFF;
    sub_80BB790(selectedPalettes, 0xFFFF);
    gTasks[taskId].data[15] = selectedPalettes;
    gTasks[taskId].data[0] = 0;
    gTasks[taskId].data[1] = 0;
    gTasks[taskId].func = sub_80BB6CC;
}

static void sub_80BB6CC(u8 taskId)
{
    u16 i;
    struct Task *task = &gTasks[taskId];

    switch (task->data[0])
    {
    case 0:
        if (++task->data[1] > 6)
        {
            task->data[1] = 0;
            task->data[2] = 16;
            ++task->data[0];
        }
        break;
    case 1:
        if (++task->data[1] > 1)
        {
            task->data[1] = 0;
            --task->data[2];
            for (i = 0; i < 16; ++i)
            {
                if ((task->data[15] >> i) & 1)
                {
                    u16 paletteOffset = i * 16;
                    BlendPalette(paletteOffset, 16, task->data[2], 0xFFFF);
                }

                if ((task->data[14] >> i) & 1)
                {
                    u16 paletteOffset = i * 16 + 0x100;
                    BlendPalette(paletteOffset, 16, task->data[2], 0);
                }
            }

            if (task->data[2] == 0)
                ++task->data[0];
        }
        break;
    case 2:
        DestroyAnimVisualTask(taskId);
        break;
    }
}

static void sub_80BB790(u32 selectedPalettes, u16 color)
{
    u16 i, curOffset, paletteOffset;

    for (i = 0; i < 32; selectedPalettes >>= 1, ++i)
        if (selectedPalettes & 1)
            for (curOffset = i * 16, paletteOffset = curOffset; curOffset < paletteOffset + 16; ++curOffset)
                gPlttBufferFaded[curOffset] = color;
}

void sub_80BB7DC(u8 taskId)
{
    s32 j;
    u32 battler, selectedPalettes = 0;

    for (battler = 0; battler < MAX_BATTLERS_COUNT; ++battler)
        if (gBattleAnimAttacker != battler)
            selectedPalettes |= 1 << (battler + 16);
    for (j = 5; j != 0; --j)
        gBattleAnimArgs[j] = gBattleAnimArgs[j - 1];
    StartBlendAnimSpriteColor(taskId, selectedPalettes);
}

void sub_80BB82C(u8 taskId)
{
    u8 newTaskId;

    sub_8075458(0);
    newTaskId = CreateTask(sub_80BB8A4, 5);
    if (gBattleAnimArgs[2] && GetBattlerSide(gBattleAnimAttacker) != B_SIDE_PLAYER)
    {
        gBattleAnimArgs[0] = -gBattleAnimArgs[0];
        gBattleAnimArgs[1] = -gBattleAnimArgs[1];
    }
    gTasks[newTaskId].data[1] = gBattleAnimArgs[0];
    gTasks[newTaskId].data[2] = gBattleAnimArgs[1];
    gTasks[newTaskId].data[3] = gBattleAnimArgs[3];
    ++gTasks[newTaskId].data[0];
    DestroyAnimVisualTask(taskId);
}

static void sub_80BB8A4(u8 taskId)
{
    gTasks[taskId].data[10] += gTasks[taskId].data[1];
    gTasks[taskId].data[11] += gTasks[taskId].data[2];
    gBattle_BG3_X += gTasks[taskId].data[10] >> 8;
    gBattle_BG3_Y += gTasks[taskId].data[11] >> 8;
    gTasks[taskId].data[10] &= 0xFF;
    gTasks[taskId].data[11] &= 0xFF;
    if (gBattleAnimArgs[7] == gTasks[taskId].data[3])
    {
        gBattle_BG3_X = 0;
        gBattle_BG3_Y = 0;
        sub_8075458(1);
        DestroyTask(taskId);
    }
}

void AnimTask_GetAttackerSide(u8 taskId)
{
    gBattleAnimArgs[7] = GetBattlerSide(gBattleAnimAttacker);
    DestroyAnimVisualTask(taskId);
}

void AnimTask_GetTargetSide(u8 taskId)
{
    gBattleAnimArgs[7] = GetBattlerSide(gBattleAnimTarget);
    DestroyAnimVisualTask(taskId);
}

void AnimTask_GetTargetIsAttackerPartner(u8 taskId)
{
    gBattleAnimArgs[7] = BATTLE_PARTNER(gBattleAnimAttacker) == gBattleAnimTarget;
    DestroyAnimVisualTask(taskId);
}

void sub_80BB9B0(u8 taskId)
{
    u16 battler;

    for (battler = 0; battler < MAX_BATTLERS_COUNT; ++battler)
        if (battler != gBattleAnimAttacker && IsBattlerSpriteVisible(battler))
            gSprites[gBattlerSpriteIds[battler]].invisible = gBattleAnimArgs[0];
    DestroyAnimVisualTask(taskId);
}

void sub_80BBA20(u8 taskId, s32 unused, u16 arg2, u8 battler1, u8 arg4, u8 arg5, u8 arg6, u8 arg7, const u32 *gfx, const u32 *tilemap, const u32 *palette)
{
    u16 species;
    u8 spriteId, newSpriteId = 0;
    u16 bg1Cnt;
    struct BattleAnimBgData animBgData;
    u8 battler2 = BATTLE_PARTNER(battler1);

    if (IsContest() || (arg4 && !IsBattlerSpriteVisible(battler2)))
        arg4 = 0;
    gBattle_WIN0H = 0;
    gBattle_WIN0V = 0;
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR
                              | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG2 | WINOUT_WIN01_BG3 | WINOUT_WIN01_OBJ  | WINOUT_WIN01_CLR
                               | WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR);
    SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG1 | BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 16));
    bg1Cnt = GetGpuReg(REG_OFFSET_BG1CNT);
    ((vBgCnt *)&bg1Cnt)->priority = 0;
    ((vBgCnt *)&bg1Cnt)->screenSize = 0;
    ((vBgCnt *)&bg1Cnt)->areaOverflowMode = 1;
    if (!IsContest())
        ((vBgCnt *)&bg1Cnt)->charBaseBlock = 1;
    SetGpuReg(REG_OFFSET_BG1CNT, bg1Cnt);
    if (GetBattlerSide(battler1) != B_SIDE_PLAYER)
        species = GetMonData(&gEnemyParty[gBattlerPartyIndexes[battler1]], MON_DATA_SPECIES);
    else
        species = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler1]], MON_DATA_SPECIES);
    spriteId = sub_8076E34(battler1, gBattlerSpriteIds[battler1], species);
    if (arg4)
        newSpriteId = sub_8076E34(battler2, gBattlerSpriteIds[battler2], species);
    sub_80752A0(&animBgData);
    AnimLoadCompressedBgTilemap(animBgData.bgId, tilemap);
    if (IsContest())
        sub_80730C0(animBgData.paletteId, animBgData.bgTilemap, 0, 0);
    AnimLoadCompressedBgGfx(animBgData.bgId, gfx, animBgData.tilesOffset);
    LoadCompressedPalette(palette, animBgData.paletteId * 16, 32);
    gBattle_BG1_X = 0;
    gBattle_BG1_Y = 0;
    gTasks[taskId].data[1] = arg2;
    gTasks[taskId].data[4] = arg5;
    gTasks[taskId].data[5] = arg7;
    gTasks[taskId].data[6] = arg6;
    gTasks[taskId].data[0] = spriteId;
    gTasks[taskId].data[2] = arg4;
    gTasks[taskId].data[3] = newSpriteId;
    gTasks[taskId].func = sub_80BBC2C;
}

static void sub_80BBC2C(u8 taskId)
{
    gTasks[taskId].data[13] += gTasks[taskId].data[1] < 0 ? -gTasks[taskId].data[1] : gTasks[taskId].data[1];
    if (gTasks[taskId].data[1] < 0)
        gBattle_BG1_Y -= gTasks[taskId].data[13] >> 8;
    else
        gBattle_BG1_Y += gTasks[taskId].data[13] >> 8;
    gTasks[taskId].data[13] &= 0xFF;
    switch (gTasks[taskId].data[15])
    {
    case 0:
        if (gTasks[taskId].data[11]++ >= gTasks[taskId].data[6])
        {
            gTasks[taskId].data[11] = 0;
            ++gTasks[taskId].data[12];
            SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(gTasks[taskId].data[12], 16 - gTasks[taskId].data[12]));
            if (gTasks[taskId].data[12] == gTasks[taskId].data[4])
                ++gTasks[taskId].data[15];
        }
        break;
    case 1:
        if (++gTasks[taskId].data[10] == gTasks[taskId].data[5])
            ++gTasks[taskId].data[15];
        break;
    case 2:
        if (gTasks[taskId].data[11]++ >= gTasks[taskId].data[6])
        {
            gTasks[taskId].data[11] = 0;
            --gTasks[taskId].data[12];
            SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(gTasks[taskId].data[12], 16 - gTasks[taskId].data[12]));
            if (gTasks[taskId].data[12] == 0)
            {
                sub_8073128(0);
                gBattle_WIN0H = 0;
                gBattle_WIN0V = 0;
                SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR
                                          | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR);
                SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG_ALL  | WINOUT_WIN01_OBJ  | WINOUT_WIN01_CLR
                                           | WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR);
                if (!IsContest())
                {
                    u16 bg1Cnt = GetGpuReg(REG_OFFSET_BG1CNT);
                    ((vBgCnt *)&bg1Cnt)->charBaseBlock = 0;
                    SetGpuReg(REG_OFFSET_BG1CNT, bg1Cnt);
                }
                SetGpuReg(REG_OFFSET_DISPCNT, GetGpuReg(REG_OFFSET_DISPCNT) ^ DISPCNT_OBJWIN_ON);
                SetGpuReg(REG_OFFSET_BLDCNT, 0);
                SetGpuReg(REG_OFFSET_BLDALPHA, 0);
                DestroySprite(&gSprites[gTasks[taskId].data[0]]);
                if (gTasks[taskId].data[2])
                    DestroySprite(&gSprites[gTasks[taskId].data[3]]);
                DestroyAnimVisualTask(taskId);
            }
        }
        break;
    }
}

void AnimTask_GetBattleTerrain(u8 taskId)
{
    gBattleAnimArgs[0] = gBattleTerrain;
    DestroyAnimVisualTask(taskId);
}

void sub_80BBE10(u8 taskId)
{
    gMonSpritesGfxPtr->field_17C = AllocZeroed(0x2000);
    DestroyAnimVisualTask(taskId);
}

void sub_80BBE3C(u8 taskId)
{
    FREE_AND_SET_NULL(gMonSpritesGfxPtr->field_17C);
    DestroyAnimVisualTask(taskId);
}

void sub_80BBE6C(u8 taskId)
{
    u32 selectedPalettes;
    s32 paletteIndex = 0;

    if (gBattleAnimArgs[0] == 0)
        for (selectedPalettes = sub_8075BE8(1, 0, 0, 0, 0, 0, 0);
             (selectedPalettes & 1) == 0;
             ++paletteIndex)
            selectedPalettes >>= 1;
    else if (gBattleAnimArgs[0] == 1)
        paletteIndex = gBattleAnimAttacker + 16;
    else if (gBattleAnimArgs[0] == 2)
        paletteIndex = gBattleAnimTarget + 16;
    memcpy(&gMonSpritesGfxPtr->field_17C[gBattleAnimArgs[1] * 16], &gPlttBufferUnfaded[paletteIndex * 16], 32);
    DestroyAnimVisualTask(taskId);
}

void sub_80BBF08(u8 taskId)
{
    u32 selectedPalettes;
    s32 paletteIndex = 0;

    if (gBattleAnimArgs[0] == 0)
        for (selectedPalettes = sub_8075BE8(1, 0, 0, 0, 0, 0, 0);
             (selectedPalettes & 1) == 0;
             ++paletteIndex)
            selectedPalettes >>= 1;
    else if (gBattleAnimArgs[0] == 1)
        paletteIndex = gBattleAnimAttacker + 16;
    else if (gBattleAnimArgs[0] == 2)
        paletteIndex = gBattleAnimTarget + 16;
    memcpy(&gPlttBufferUnfaded[paletteIndex * 16], &gMonSpritesGfxPtr->field_17C[gBattleAnimArgs[1] * 16], 32);
    DestroyAnimVisualTask(taskId);
}

void sub_80BBFA4(u8 taskId)
{
    u32 selectedPalettes;
    s32 paletteIndex = 0;

    if (gBattleAnimArgs[0] == 0)
        for (selectedPalettes = sub_8075BE8(1, 0, 0, 0, 0, 0, 0);
             (selectedPalettes & 1) == 0;
             ++paletteIndex)
            selectedPalettes >>= 1;
    else if (gBattleAnimArgs[0] == 1)
        paletteIndex = gBattleAnimAttacker + 16;
    else if (gBattleAnimArgs[0] == 2)
        paletteIndex = gBattleAnimTarget + 16;
    memcpy(&gPlttBufferUnfaded[paletteIndex * 16], &gPlttBufferFaded[paletteIndex * 16], 32);
    DestroyAnimVisualTask(taskId);
}

void AnimTask_IsContest(u8 taskId)
{
    if (IsContest())
        gBattleAnimArgs[7] = 1;
    else
        gBattleAnimArgs[7] = 0;
    DestroyAnimVisualTask(taskId);
}

void sub_80BC060(u8 taskId)
{
    gBattleAnimAttacker = gBattlerTarget;
    gBattleAnimTarget = gEffectBattler;
    DestroyAnimVisualTask(taskId);
}

void AnimTask_IsTargetSameSide(u8 taskId)
{
    if (GetBattlerSide(gBattleAnimAttacker) == GetBattlerSide(gBattleAnimTarget))
        gBattleAnimArgs[7] = 1;
    else
        gBattleAnimArgs[7] = 0;
    DestroyAnimVisualTask(taskId);
}

void sub_80BC0DC(u8 taskId)
{
    gBattleAnimTarget = gBattlerTarget;
    DestroyAnimVisualTask(taskId);
}

void sub_80BC0FC(u8 taskId)
{
    gBattleAnimAttacker = gBattlerAttacker;
    gBattleAnimTarget = gEffectBattler;
    DestroyAnimVisualTask(taskId);
}

void sub_80BC12C(u8 taskId)
{
    if (IsContest())
    {
        DestroyAnimVisualTask(taskId);
    }
    else
    {
        gTasks[taskId].data[0] = gBattleSpritesDataPtr->battlerData[gBattleAnimAttacker].invisible;
        gBattleSpritesDataPtr->battlerData[gBattleAnimAttacker].invisible = 1;
        gTasks[taskId].func = sub_80BC19C;
        --gAnimVisualTaskCount;
    }
}

static void sub_80BC19C(u8 taskId)
{
    if (gBattleAnimArgs[7] == 0x1000)
    {
        gBattleSpritesDataPtr->battlerData[gBattleAnimAttacker].invisible = (u8)gTasks[taskId].data[0] & 1;
        DestroyTask(taskId);
    }
}

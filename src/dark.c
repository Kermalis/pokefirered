#include "global.h"
#include "battle_anim.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "palette.h"
#include "scanline_effect.h"
#include "trig.h"
#include "util.h"

static void sub_80B7ACC(struct Sprite *sprite);
static void sub_80B7BD4(struct Sprite *sprite);
static void sub_80B7C88(struct Sprite *sprite);
static void sub_80B86B0(struct Sprite *sprite);
static void sub_80B7954(u8 taskId);
static void sub_80B7A14(u8 taskId);
static void sub_80B7B48(struct Sprite *sprite);
static void sub_80B7C10(struct Sprite *sprite);
static void sub_80B7C50(struct Sprite *sprite);
static void sub_80B7D88(struct Sprite *sprite);
static void sub_80B856C(u8 priority);
static void sub_80B7F58(u8 taskId);
static void sub_80B843C(struct Task *task);
static void sub_80B82C0(u8 taskId);
static void sub_80B8920(u8 taskId);

const struct SpriteTemplate gUnknown_83E7878 =
{
    .tileTag = ANIM_TAG_TIED_BAG,
    .paletteTag = ANIM_TAG_TIED_BAG,
    .oam = &gOamData_83AC9D0,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B7ACC,
};

static const union AffineAnimCmd gUnknown_83E7890[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, 0, 1),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E78A0[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, 32, 1),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E78B0[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, 64, 1),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E78C0[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, 96, 1),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E78D0[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, -128, 1),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E78E0[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, -96, 1),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E78F0[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, -64, 1),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E7900[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, -32, 1),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd *const gUnknown_83E7910[] =
{
    gUnknown_83E7890,
    gUnknown_83E78A0,
    gUnknown_83E78B0,
    gUnknown_83E78C0,
    gUnknown_83E78D0,
    gUnknown_83E78E0,
    gUnknown_83E78F0,
    gUnknown_83E7900,
};

const struct SpriteTemplate gUnknown_83E7930 =
{
    .tileTag = ANIM_TAG_SHARP_TEETH,
    .paletteTag = ANIM_TAG_SHARP_TEETH,
    .oam = &gOamData_83ACB60,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E7910,
    .callback = sub_80B7BD4,
};

const struct SpriteTemplate gUnknown_83E7948 =
{
    .tileTag = ANIM_TAG_CLAMP,
    .paletteTag = ANIM_TAG_CLAMP,
    .oam = &gOamData_83ACB60,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E7910,
    .callback = sub_80B7BD4,
};

static const union AffineAnimCmd gUnknown_83E7960[] =
{
    AFFINEANIMCMD_FRAME(0xC0, 0xC0, 80, 0),
    AFFINEANIMCMD_FRAME(0x0, 0x0, -2, 8),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E7978[] =
{
    AFFINEANIMCMD_FRAME(0xC0, 0xC0, -80, 0),
    AFFINEANIMCMD_FRAME(0x0, 0x0, 2, 8),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd *const gUnknown_83E7990[] =
{
    gUnknown_83E7960,
    gUnknown_83E7978,
};

const struct SpriteTemplate gUnknown_83E7998 =
{
    .tileTag = ANIM_TAG_SMALL_BUBBLES,
    .paletteTag = ANIM_TAG_SMALL_BUBBLES,
    .oam = &gOamData_83ACA30,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E7990,
    .callback = sub_80B7C88,
};

static const union AnimCmd gUnknown_83E79B0[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(16, 4),
    ANIMCMD_FRAME(32, 4),
    ANIMCMD_FRAME(48, 4),
    ANIMCMD_FRAME(64, 4),
    ANIMCMD_END,
};

static const union AnimCmd gUnknown_83E79C8[] =
{
    ANIMCMD_FRAME(0, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(16, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(32, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(48, 4, .hFlip = TRUE),
    ANIMCMD_FRAME(64, 4, .hFlip = TRUE),
    ANIMCMD_END,
};

static const union AnimCmd *const gUnknown_83E79E0[] =
{
    gUnknown_83E79B0,
    gUnknown_83E79C8,
};

const struct SpriteTemplate gUnknown_83E79E8 =
{
    .tileTag = ANIM_TAG_CLAW_SLASH,
    .paletteTag = ANIM_TAG_CLAW_SLASH,
    .oam = &gOamData_83AC9D8,
    .anims = gUnknown_83E79E0,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B86B0,
};

void sub_80B78E0(u8 taskId)
{
    s32 battler;

    gTasks[taskId].data[0] = gBattleAnimArgs[0];
    battler = gBattleAnimAttacker;
    gTasks[taskId].data[1] = 16;
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(16, 0));
    if (GetBattlerSpriteBGPriorityRank(battler) == 1)
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND | BLDCNT_TGT1_BG1);
    else
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND | BLDCNT_TGT1_BG2);
    gTasks[taskId].func = sub_80B7954;
}

static void sub_80B7954(u8 taskId)
{
    u8 blendA = gTasks[taskId].data[1] >> 8;
    u8 blendB = gTasks[taskId].data[1];

    if (gTasks[taskId].data[2] == (u8)gTasks[taskId].data[0])
    {
        ++blendA;
        --blendB;
        gTasks[taskId].data[1] = BLDALPHA_BLEND(blendB, blendA);
        SetGpuReg(REG_OFFSET_BLDALPHA, gTasks[taskId].data[1]);
        gTasks[taskId].data[2] = 0;
        if (blendA == 16)
        {
            gSprites[gBattlerSpriteIds[gBattleAnimAttacker]].invisible = TRUE;
            DestroyAnimVisualTask(taskId);
        }
    }
    else
    {
        ++gTasks[taskId].data[2];
    }
}

void sub_80B79DC(u8 taskId)
{
    gTasks[taskId].data[0] = gBattleAnimArgs[0];
    gTasks[taskId].data[1] = BLDALPHA_BLEND(0, 16);
    gTasks[taskId].func = sub_80B7A14;
    SetGpuReg(REG_OFFSET_BLDALPHA, gTasks[taskId].data[1]);
}

static void sub_80B7A14(u8 taskId)
{
    u8 blendA = gTasks[taskId].data[1] >> 8;
    u8 blendB = gTasks[taskId].data[1];

    if (gTasks[taskId].data[2] == (u8)gTasks[taskId].data[0])
    {
        --blendA;
        ++blendB;
        gTasks[taskId].data[1] = (blendA << 8) | blendB;
        SetGpuReg(REG_OFFSET_BLDALPHA, gTasks[taskId].data[1]);
        gTasks[taskId].data[2] = 0;
        if (blendA == 0)
        {
            SetGpuReg(REG_OFFSET_BLDCNT, 0);
            SetGpuReg(REG_OFFSET_BLDALPHA, 0);
            DestroyAnimVisualTask(taskId);
        }
    }
    else
    {
        ++gTasks[taskId].data[2];
    }
}

void sub_80B7A80(u8 taskId)
{
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 16));
    if (GetBattlerSpriteBGPriorityRank(gBattleAnimAttacker) == 1)
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND | BLDCNT_TGT1_BG1);
    else
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND | BLDCNT_TGT1_BG2);
    DestroyAnimVisualTask(taskId);
}

static void sub_80B7ACC(struct Sprite *sprite)
{
    sprite->data[1] = GetBattlerSpriteCoord(gBattleAnimTarget, BATTLER_COORD_X_2);
    sprite->data[2] = GetBattlerSpriteCoord(gBattleAnimAttacker, BATTLER_COORD_X_2);
    sprite->data[3] = GetBattlerSpriteCoord(gBattleAnimTarget, BATTLER_COORD_Y_PIC_OFFSET);
    sprite->data[4] = GetBattlerSpriteCoord(gBattleAnimAttacker, BATTLER_COORD_Y_PIC_OFFSET);
    sprite->data[0] = 0x7E;
    InitSpriteDataForLinearTranslation(sprite);
    sprite->data[3] = -sprite->data[1];
    sprite->data[4] = -sprite->data[2];
    sprite->data[6] = 0xFFD8;
    sprite->callback = sub_80B7B48;
    sprite->callback(sprite);
}

static void sub_80B7B48(struct Sprite *sprite)
{
    sprite->data[3] += sprite->data[1];
    sprite->data[4] += sprite->data[2];
    sprite->pos2.x = sprite->data[3] >> 8;
    sprite->pos2.y = sprite->data[4] >> 8;
    if (sprite->data[7] == 0)
    {
        sprite->data[3] += sprite->data[1];
        sprite->data[4] += sprite->data[2];
        sprite->pos2.x = sprite->data[3] >> 8;
        sprite->pos2.y = sprite->data[4] >> 8;
        --sprite->data[0];
    }
    sprite->pos2.y += Sin(sprite->data[5], sprite->data[6]);
    sprite->data[5] = (sprite->data[5] + 3) & 0xFF;
    if (sprite->data[5] > 0x7F)
    {
        sprite->data[5] = 0;
        sprite->data[6] += 20;
        ++sprite->data[7];
    }
    if (--sprite->data[0] == 0)
        DestroyAnimSprite(sprite);
}

static void sub_80B7BD4(struct Sprite *sprite)
{
    sprite->pos1.x += gBattleAnimArgs[0];
    sprite->pos1.y += gBattleAnimArgs[1];
    StartSpriteAffineAnim(sprite, gBattleAnimArgs[2]);
    sprite->data[0] = gBattleAnimArgs[3];
    sprite->data[1] = gBattleAnimArgs[4];
    sprite->data[2] = gBattleAnimArgs[5];
    sprite->callback = sub_80B7C10;
}

static void sub_80B7C10(struct Sprite *sprite)
{
    sprite->data[4] += sprite->data[0];
    sprite->data[5] += sprite->data[1];
    sprite->pos2.x = sprite->data[4] >> 8;
    sprite->pos2.y = sprite->data[5] >> 8;
    if (++sprite->data[3] == sprite->data[2])
        sprite->callback = sub_80B7C50;
}

static void sub_80B7C50(struct Sprite *sprite)
{
    sprite->data[4] -= sprite->data[0];
    sprite->data[5] -= sprite->data[1];
    sprite->pos2.x = sprite->data[4] >> 8;
    sprite->pos2.y = sprite->data[5] >> 8;
    if (--sprite->data[3] == 0)
        DestroySpriteAndMatrix(sprite);
}

static void sub_80B7C88(struct Sprite *sprite)
{
    u8 battler;
    s8 xOffset;

    if (gBattleAnimArgs[0] == 0)
        battler = gBattleAnimAttacker;
    else
        battler = gBattleAnimTarget;
    xOffset = 20;
    sprite->oam.tileNum += 4;
    switch (gBattleAnimArgs[1])
    {
    case 0:
        sprite->pos1.x = GetBattlerSpriteCoordAttr(battler, BATTLER_COORD_ATTR_RIGHT) - 8;
        sprite->pos1.y = GetBattlerSpriteCoordAttr(battler, BATTLER_COORD_ATTR_TOP) + 8;
        break;
    case 1:
        sprite->pos1.x = GetBattlerSpriteCoordAttr(battler, BATTLER_COORD_ATTR_RIGHT) - 14;
        sprite->pos1.y = GetBattlerSpriteCoordAttr(battler, BATTLER_COORD_ATTR_TOP) + 16;
        break;
    case 2:
        sprite->pos1.x = GetBattlerSpriteCoordAttr(battler, BATTLER_COORD_ATTR_LEFT) + 8;
        sprite->pos1.y = GetBattlerSpriteCoordAttr(battler, BATTLER_COORD_ATTR_TOP) + 8;
        StartSpriteAffineAnim(sprite, 1);
        xOffset = -20;
        break;
    case 3:
        sprite->pos1.x = GetBattlerSpriteCoordAttr(battler, BATTLER_COORD_ATTR_LEFT) + 14;
        sprite->pos1.y = GetBattlerSpriteCoordAttr(battler, BATTLER_COORD_ATTR_TOP) + 16;
        StartSpriteAffineAnim(sprite, 1);
        xOffset = -20;
        break;
    }
    sprite->data[0] = 32;
    sprite->data[2] = sprite->pos1.x + xOffset;
    sprite->data[4] = sprite->pos1.y + 12;
    sprite->data[5] = -12;
    InitAnimArcTranslation(sprite);
    sprite->callback = sub_80B7D88;
}

static void sub_80B7D88(struct Sprite *sprite)
{
    if (TranslateAnimHorizontalArc(sprite))
        DestroySpriteAndMatrix(sprite);
}

void sub_80B7DA4(u8 taskId)
{
    struct ScanlineEffectParams scanlineParams;
    struct BattleAnimBgData animBg;
    u16 i;
    u8 pos;
    s32 var0;
    struct Task *task = &gTasks[taskId];

    task->data[7] = GetBattlerSpriteCoord(gBattleAnimAttacker, BATTLER_COORD_Y) + 31;
    task->data[6] = GetBattlerSpriteCoordAttr(gBattleAnimAttacker, BATTLER_COORD_ATTR_TOP) - 7;
    task->data[5] = task->data[7];
    task->data[4] = task->data[6];
    task->data[13] = (task->data[7] - task->data[6]) << 8;
    pos = GetBattlerSpriteCoord(gBattleAnimAttacker, BATTLER_COORD_X);
    task->data[14] = pos - 32;
    task->data[15] = pos + 32;
    if (GetBattlerSide(gBattleAnimAttacker) == B_SIDE_PLAYER)
        task->data[8] = -12;
    else
        task->data[8] = -64;
    task->data[3] = GetBattlerSpriteBGPriorityRank(gBattleAnimAttacker);
    if (task->data[3] == 1)
    {
        sub_80752A0(&animBg);
        task->data[10] = gBattle_BG1_Y;
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND | BLDCNT_TGT1_BG1);
        FillPalette(0, animBg.paletteId * 16, 32);
        scanlineParams.dmaDest = &REG_BG1VOFS;
        var0 = WINOUT_WIN01_BG1;
        if (!IsContest())
            gBattle_BG2_X += 240;
    }
    else
    {
        task->data[10] = gBattle_BG2_Y;
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND | BLDCNT_TGT1_BG2);
        FillPalette(0, 144, 32);
        scanlineParams.dmaDest = &REG_BG2VOFS;
        var0 = WINOUT_WIN01_BG2;
        if (!IsContest())
            gBattle_BG1_X += 240;
    }
    scanlineParams.dmaControl = SCANLINE_EFFECT_DMACNT_16BIT;
    scanlineParams.initState = 1;
    scanlineParams.unused9 = 0;
    task->data[11] = 0;
    task->data[12] = 16;
    task->data[0] = 0;
    task->data[1] = 0;
    task->data[2] = 0;
    sub_80B856C(3);
    for (i = 0; i < 112; ++i)
    {
        gScanlineEffectRegBuffers[0][i] = task->data[10];
        gScanlineEffectRegBuffers[1][i] = task->data[10];
    }
    ScanlineEffect_SetParams(scanlineParams);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR | (var0 ^ (WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR)));
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR);
    gBattle_WIN0H = (task->data[14] << 8) | task->data[15];
    gBattle_WIN0V = 160;

    task->func = sub_80B7F58;
}

static void sub_80B7F58(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    switch (task->data[0])
    {
    case 0:
        if (++task->data[1] > 1)
        {
            task->data[1] = 0;
            if (++task->data[2] & 1)
            {
                if (task->data[11] != 12)
                    ++task->data[11];
            }
            else if (task->data[12] != 8)
            {
                --task->data[12];
            }
            SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(task->data[11], task->data[12]));
            if (task->data[11] == 12 && task->data[12] == 8)
                ++task->data[0];
        }
        break;
    case 1:
        task->data[4] -= 8;
        sub_80B843C(task);
        if (task->data[4] < task->data[8])
            ++task->data[0];
        break;
    case 2:
        task->data[4] -= 8;
        sub_80B843C(task);
        task->data[14] += 4;
        task->data[15] -= 4;
        if (task->data[14] >= task->data[15])
            task->data[14] = task->data[15];
        gBattle_WIN0H = (task->data[14] << 8) | task->data[15];
        if (task->data[14] == task->data[15])
            ++task->data[0];
        break;
    case 3:
        gScanlineEffect.state = 3;
        ++task->data[0];
        break;
    case 4:
        DestroyAnimVisualTask(taskId);
        break;
    }
}

void sub_80B8070(u8 taskId)
{
    struct BattleAnimBgData animBg;
    struct ScanlineEffectParams scanlineParams;
    u8 x;
    u16 i;
    struct Task *task = &gTasks[taskId];

    switch (task->data[0])
    {
    case 0:
        if (IsContest() == TRUE)
        {
            gBattle_WIN0H = 0;
            gBattle_WIN0V = 0;
            SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR);
            SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR | WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
            DestroyAnimVisualTask(taskId);
        }
        else
        {
            task->data[3] = GetBattlerSpriteBGPriorityRank(gBattleAnimTarget);
            if (task->data[3] == 1)
            {
                SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND | BLDCNT_TGT1_BG1);
                gBattle_BG2_X += 240;
            }
            else
            {
                SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND | BLDCNT_TGT1_BG2);
                gBattle_BG1_X += 240;
            }
            ++task->data[0];
        }
        break;
    case 1:
        if (task->data[3] == 1)
        {
            sub_80752A0(&animBg);
            task->data[10] = gBattle_BG1_Y;
            FillPalette(0, animBg.paletteId * 16, 32);
        }
        else
        {
            task->data[10] = gBattle_BG2_Y;
            FillPalette(0, 9 * 16, 32);
        }
        sub_80B856C(3);
        ++task->data[0];
        break;
    case 2:
        task->data[7] = GetBattlerSpriteCoord(gBattleAnimTarget, BATTLER_COORD_Y) + 31;
        task->data[6] = GetBattlerSpriteCoordAttr(gBattleAnimTarget, BATTLER_COORD_ATTR_TOP) - 7;
        task->data[13] = (task->data[7] - task->data[6]) << 8;
        x = GetBattlerSpriteCoord(gBattleAnimTarget, BATTLER_COORD_X);
        task->data[14] = x - 4;
        task->data[15] = x + 4;
        if (GetBattlerSide(gBattleAnimTarget) == B_SIDE_PLAYER)
            task->data[8] = -12;
        else
            task->data[8] = -64;
        task->data[4] = task->data[8];
        task->data[5] = task->data[8];
        task->data[11] = 12;
        task->data[12] = 8;
        ++task->data[0];
        break;
    case 3:
        if (task->data[3] == 1)
            scanlineParams.dmaDest = &REG_BG1VOFS;
        else
            scanlineParams.dmaDest = &REG_BG2VOFS;
        for (i = 0; i < 112; ++i)
        {
            gScanlineEffectRegBuffers[0][i] = task->data[10] + (159 - i);
            gScanlineEffectRegBuffers[1][i] = task->data[10] + (159 - i);
        }
        scanlineParams.dmaControl = SCANLINE_EFFECT_DMACNT_16BIT;
        scanlineParams.initState = 1;
        scanlineParams.unused9 = 0;
        ScanlineEffect_SetParams(scanlineParams);
        ++task->data[0];
        break;
    case 4:
        if (task->data[3] == 1)
            SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR | WINOUT_WIN01_BG0 | WINOUT_WIN01_BG2 | WINOUT_WIN01_BG3 | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
        else
            SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR | WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_BG3 | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR);
        gBattle_WIN0H = (task->data[14] << 8) | task->data[15];
        gBattle_WIN0V = 160;
        task->data[0] = 0;
        task->data[1] = 0;
        task->data[2] = 0;
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(12, 8));
        task->func = sub_80B82C0;
        break;
    }
}

static void sub_80B82C0(u8 taskId)
{
    u8 pos;
    u16 i;
    struct Task *task = &gTasks[taskId];

    switch (task->data[0])
    {
    case 0:
        task->data[5] += 8;
        if (task->data[5] >=  task->data[7])
            task->data[5] = task->data[7];
        sub_80B843C(task);
        if (task->data[5] == task->data[7])
            ++task->data[0];
        break;
    case 1:
        if (task->data[15] - task->data[14] < 0x40)
        {
            task->data[14] -= 4;
            task->data[15] += 4;
        }
        else
        {
            task->data[1] = 1;
        }
        gBattle_WIN0H = (task->data[14] << 8) | task->data[15];
        task->data[4] += 8;
        if (task->data[4] >= task->data[6])
            task->data[4] = task->data[6];
        sub_80B843C(task);
        if (task->data[4] == task->data[6] && task->data[1])
        {
            task->data[1] = 0;
            ++task->data[0];
        }
        break;
    case 2:
        if (++task->data[1] > 1)
        {
            task->data[1] = 0;
            ++task->data[2];
            if (task->data[2] & 1)
            {
                if (task->data[11])
                    --task->data[11];
            }
            else if (task->data[12] < 16)
            {
                ++task->data[12];
            }
            SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(task->data[11], task->data[12]));
            if (task->data[11] == 0 && task->data[12] == 16)
                ++task->data[0];
        }
        break;
    case 3:
        gScanlineEffect.state = 3;
        ++task->data[0];
        break;
    case 4:
        gBattle_WIN0H = 0;
        gBattle_WIN0V = 0;
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR | WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
        DestroyAnimVisualTask(taskId);
        break;
    }
}

static void sub_80B843C(struct Task *task)
{
    s32 var0, var1, var4;
    s16 var2, i;

    var2 = task->data[5] - task->data[4];
    if (var2 != 0)
    {
        var0 = task->data[13] / var2;
        var1 = task->data[6] << 8;
        for (i = 0; i < task->data[4]; ++i)
            gScanlineEffectRegBuffers[gScanlineEffect.srcBuffer][i] = task->data[10] - (i - 159);
        for (i = task->data[4]; i <= task->data[5]; ++i)
        {
            if (i >= 0)
            {
                s16 var3 = (var1 >> 8) - i;

                gScanlineEffectRegBuffers[gScanlineEffect.srcBuffer][i] = var3 + task->data[10];
            }
            var1 += var0;
        }
        var4 = task->data[10] - (i - 159);
        for (; i < task->data[7]; ++i)
            if (i >= 0)
                gScanlineEffectRegBuffers[gScanlineEffect.srcBuffer][i] = var4--;
    }
    else
    {
        var4 = task->data[10] + 159;
        for (i = 0; i < 112; ++i)
        {
            gScanlineEffectRegBuffers[0][i] = var4;
            gScanlineEffectRegBuffers[1][i] = var4;
            --var4;
        }
    }
}

static void sub_80B856C(u8 priority)
{
    u16 i;

    for (i = 0; i < MAX_BATTLERS_COUNT; ++i)
    {
        u8 spriteId = GetAnimBattlerSpriteId(i);

        if (spriteId != 0xFF)
            gSprites[spriteId].oam.priority = priority;
    }
}

void sub_80B85B8(u8 taskId)
{
    bool8 toBG2 = GetBattlerSpriteBGPriorityRank(gBattleAnimAttacker) ^ 1 ? TRUE : FALSE;

    MoveBattlerSpriteToBG(gBattleAnimAttacker, toBG2);
    gSprites[gBattlerSpriteIds[gBattleAnimAttacker]].invisible = FALSE;
    if (IsBattlerSpriteVisible(BATTLE_PARTNER(gBattleAnimAttacker)))
    {
        MoveBattlerSpriteToBG(gBattleAnimAttacker ^ 2, toBG2 ^ 1);
        gSprites[gBattlerSpriteIds[gBattleAnimAttacker ^ 2]].invisible = FALSE;
    }
    DestroyAnimVisualTask(taskId);
}

void sub_80B8664(u8 taskId)
{
    bool8 toBG2 = GetBattlerSpriteBGPriorityRank(gBattleAnimAttacker) ^ 1 ? TRUE : FALSE;
    
    sub_8073128(toBG2);
    if (IsBattlerSpriteVisible(BATTLE_PARTNER(gBattleAnimAttacker)))
        sub_8073128(toBG2 ^ 1);
    DestroyAnimVisualTask(taskId);
}

static void sub_80B86B0(struct Sprite *sprite)
{
    sprite->pos1.x += gBattleAnimArgs[0];
    sprite->pos1.y += gBattleAnimArgs[1];
    StartSpriteAnim(sprite, gBattleAnimArgs[2]);
    sprite->callback = RunStoredCallbackWhenAnimEnds;
    StoreSpriteCallbackInData6(sprite, DestroyAnimSprite);
}

// Makes the attacker metallic and shining.
// Used by MOVE_HARDEN and MOVE_IRON_DEFENSE.
// arg0: if true won't change battler's palette back
// arg1: if true, use custom color
// arg2: custom color
// Custom color argument is used in MOVE_POISON_TAIL to make the mon turn purplish/pinkish as if became cloaked in poison.
void AnimTask_MetallicShine(u8 taskId)
{
    u16 species;
    u8 spriteId, newSpriteId;
    u16 paletteNum;
    struct BattleAnimBgData animBg;
    bool32 priorityChanged = FALSE;

    gBattle_WIN0H = 0;
    gBattle_WIN0V = 0;
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR | WINOUT_WIN01_BG0 | WINOUT_WIN01_BG2 | WINOUT_WIN01_BG3 | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
    SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND | BLDCNT_TGT1_BG1);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(8, 12));
    SetAnimBgAttribute(1, BG_ANIM_PRIORITY, 0);
    SetAnimBgAttribute(1, BG_ANIM_SCREEN_SIZE, 0);
    if (!IsContest())
        SetAnimBgAttribute(1, BG_ANIM_CHAR_BASE_BLOCK, 1);
    if (IsDoubleBattle() && !IsContest())
    {
        if (GetBattlerPosition(gBattleAnimAttacker) == B_POSITION_OPPONENT_RIGHT || GetBattlerPosition(gBattleAnimAttacker) == B_POSITION_PLAYER_LEFT)
        {
            if (IsBattlerSpriteVisible(BATTLE_PARTNER(gBattleAnimAttacker)) == TRUE)
            {
                gSprites[gBattlerSpriteIds[BATTLE_PARTNER(gBattleAnimAttacker)]].oam.priority--;
                SetAnimBgAttribute(1, BG_ANIM_PRIORITY, 1);
                priorityChanged = TRUE;
            }
        }
    }
    if (GetBattlerSide(gBattleAnimAttacker) != B_SIDE_PLAYER)
        species = GetMonData(&gEnemyParty[gBattlerPartyIndexes[gBattleAnimAttacker]], MON_DATA_SPECIES);
    else
        species = GetMonData(&gPlayerParty[gBattlerPartyIndexes[gBattleAnimAttacker]], MON_DATA_SPECIES);
    spriteId = GetAnimBattlerSpriteId(ANIM_ATTACKER);
    newSpriteId = sub_8076E34(gBattleAnimAttacker, spriteId, species);
    sub_80752A0(&animBg);
    AnimLoadCompressedBgTilemap(animBg.bgId, gMetalShineTilemap);
    AnimLoadCompressedBgGfx(animBg.bgId, gMetalShineGfx, animBg.tilesOffset);
    LoadCompressedPalette(gMetalShinePalette, animBg.paletteId * 16, 32);
    gBattle_BG1_X = -gSprites[spriteId].pos1.x + 96;
    gBattle_BG1_Y = -gSprites[spriteId].pos1.y + 32;
    paletteNum = 16 + gSprites[spriteId].oam.paletteNum;
    if (gBattleAnimArgs[1] == 0)
        SetGreyscaleOrOriginalPalette(paletteNum, FALSE);
    else
        BlendPalette(paletteNum * 16, 16, 11, gBattleAnimArgs[2]);
    gTasks[taskId].data[0] = newSpriteId;
    gTasks[taskId].data[1] = gBattleAnimArgs[0];
    gTasks[taskId].data[2] = gBattleAnimArgs[1];
    gTasks[taskId].data[3] = gBattleAnimArgs[2];
    gTasks[taskId].data[6] = priorityChanged;
    gTasks[taskId].func = sub_80B8920;
}

static void sub_80B8920(u8 taskId)
{
    struct BattleAnimBgData animBg;
    u16 paletteNum;
    u8 spriteId;

    gTasks[taskId].data[10] += 4;
    gBattle_BG1_X -= 4;
    if (gTasks[taskId].data[10] == 128)
    {
        gTasks[taskId].data[10] = 0;
        gBattle_BG1_X += 128;
        gTasks[taskId].data[11]++;
        if (gTasks[taskId].data[11] == 2)
        {
            spriteId = GetAnimBattlerSpriteId(ANIM_ATTACKER);
            paletteNum = 16 + gSprites[spriteId].oam.paletteNum;
            if (gTasks[taskId].data[1] == 0)
                SetGreyscaleOrOriginalPalette(paletteNum, 1);
            DestroySprite(&gSprites[gTasks[taskId].data[0]]);
            sub_80752A0(&animBg);
            sub_8075358(animBg.bgId);
            if (gTasks[taskId].data[6] == 1)
                gSprites[gBattlerSpriteIds[BATTLE_PARTNER(gBattleAnimAttacker)]].oam.priority++;
        }
        else if (gTasks[taskId].data[11] == 3)
        {
            gBattle_WIN0H = 0;
            gBattle_WIN0V = 0;
            SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR);
            SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR | WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
            if (!IsContest())
                SetAnimBgAttribute(1, BG_ANIM_CHAR_BASE_BLOCK, 0);
            SetGpuReg(REG_OFFSET_DISPCNT, GetGpuReg(REG_OFFSET_DISPCNT) ^ DISPCNT_OBJWIN_ON);
            SetGpuReg(REG_OFFSET_BLDCNT, 0);
            SetGpuReg(REG_OFFSET_BLDALPHA, 0);
            DestroyAnimVisualTask(taskId);
        }
    }
}

// Changes battler's palette to either greyscale or original.
// arg0: which battler
// arg1: 0 grayscale, 1 original
void AnimTask_SetGreyscaleOrOriginalPal(u8 taskId)
{
    u8 spriteId, battler;
    bool8 calcSpriteId = FALSE;
    u8 position = B_POSITION_PLAYER_LEFT;

    switch (gBattleAnimArgs[0])
    {
    case 0:
    case 1:
    case 2:
    case 3:
        spriteId = GetAnimBattlerSpriteId(gBattleAnimArgs[0]);
        break;
    case 4:
        position = B_POSITION_PLAYER_LEFT;
        calcSpriteId = TRUE;
        break;
    case 5:
        position = B_POSITION_PLAYER_RIGHT;
        calcSpriteId = TRUE;
        break;
    case 6:
        position = B_POSITION_OPPONENT_LEFT;
        calcSpriteId = TRUE;
        break;
    case 7:
        position = B_POSITION_OPPONENT_RIGHT;
        calcSpriteId = TRUE;
        break;
    default:
        spriteId = 0xFF;
        break;
    }
    if (calcSpriteId)
    {
        battler = GetBattlerAtPosition(position);
        if (IsBattlerSpriteVisible(battler))
            spriteId = gBattlerSpriteIds[battler];
        else
            spriteId = 0xFF;
    }
    if (spriteId != 0xFF)
        SetGreyscaleOrOriginalPalette(gSprites[spriteId].oam.paletteNum + 16, gBattleAnimArgs[1]);
    DestroyAnimVisualTask(taskId);
}

void sub_80B8B38(u8 taskId)
{
    if (gAnimMoveTurn < 2)
        gBattleAnimArgs[7] = 0;
    if (gAnimMoveTurn == 2)
        gBattleAnimArgs[7] = 1;
    DestroyAnimVisualTask(taskId);
}

#include "global.h"
#include "battle_anim.h"
#include "bg.h"
#include "gpu_regs.h"
#include "palette.h"
#include "scanline_effect.h"
#include "malloc.h"
#include "graphics.h"
#include "sound.h"
#include "trig.h"
#include "util.h"
#include "decompress.h"
#include "constants/songs.h"

static void sub_80B5268(struct Sprite *sprite);
static void sub_80B52D0(struct Sprite *sprite);
static void sub_80B5344(struct Sprite *sprite);
static void sub_80B53C0(struct Sprite *sprite);
static void sub_80B5450(struct Sprite *sprite);
static void sub_80B5470(struct Sprite *sprite);
static void sub_80B5570(u8 taskId);
static void sub_80B55C8(u8 taskId);
static void InitAnimShadowBall(struct Sprite *sprite);
static void AnimShadowBallStep(struct Sprite *sprite);
static void sub_80B57F8(struct Sprite *sprite);
static void sub_80B5810(struct Sprite *sprite);
static void sub_80B59D4(u8 taskId);
static void sub_80B5AD4(u8 taskId);
static void sub_80B5D38(u8 taskId);
static void sub_80B5DCC(u8 taskId);
static void sub_80B5EC0(struct Sprite *sprite);
static void sub_80B5FE0(struct Sprite *sprite);
static void sub_80B623C(u8 taskId);
static void sub_80B6468(u8 taskId);
static void sub_80B65F0(u8 taskId);
static void sub_80B664C(struct Sprite *sprite);
static void sub_80B66A8(struct Sprite *sprite);
static void sub_80B6728(struct Sprite *sprite);
static void sub_80B67A0(struct Sprite *sprite);
static void sub_80B67D4(struct Sprite *sprite);
static void sub_80B68A8(struct Sprite *sprite);
static void sub_80B696C(u8 taskId);
static void sub_80B6AF8(struct Sprite *sprite);
static void sub_80B7158(struct Sprite *sprite);
static void sub_80B6BE4(u8 taskId);
static void sub_80B6F30(u8 taskId);
static void sub_80B6FC4(u8 taskId);
static void sub_80B71B0(struct Sprite *sprite);

static const union AffineAnimCmd gUnknown_83E75A8[] =
{
    AFFINEANIMCMD_FRAME(0x1E, 0x1E, 10, 5),
    AFFINEANIMCMD_FRAME(0xFFE2, 0xFFE2, 10, 5),
    AFFINEANIMCMD_JUMP(0),
};

static const union AffineAnimCmd *const gUnknown_83E75C0[] =
{
    gUnknown_83E75A8,
};

const struct SpriteTemplate gUnknown_83E75C4 =
{
    .tileTag = ANIM_TAG_YELLOW_BALL,
    .paletteTag = ANIM_TAG_YELLOW_BALL,
    .oam = &gOamData_83ACA90,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E75C0,
    .callback = sub_80B5268,
};

const struct SpriteTemplate gUnknown_83E75DC =
{
    .tileTag = ANIM_TAG_YELLOW_BALL,
    .paletteTag = ANIM_TAG_YELLOW_BALL,
    .oam = &gOamData_83ACAF0,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B5450,
};

static const union AffineAnimCmd gUnknown_83E75F4[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, 10, 1),
    AFFINEANIMCMD_JUMP(0),
};

static const union AffineAnimCmd *const gUnknown_83E7604[] =
{
    gUnknown_83E75F4,
};

const struct SpriteTemplate gShadowBallSpriteTemplate =
{
    .tileTag = ANIM_TAG_SHADOW_BALL,
    .paletteTag = ANIM_TAG_SHADOW_BALL,
    .oam = &gOamData_83ACA38,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E7604,
    .callback = InitAnimShadowBall,
};

const union AnimCmd gUnknown_83E7620[] =
{
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(8, 2),
    ANIMCMD_FRAME(16, 2),
    ANIMCMD_FRAME(24, 2),
    ANIMCMD_FRAME(32, 2),
    ANIMCMD_END,
};

static const union AnimCmd *const gUnknown_83E7638[] =
{
    gUnknown_83E7620,
};

const struct SpriteTemplate gUnknown_83E763C =
{
    .tileTag = ANIM_TAG_LICK,
    .paletteTag = ANIM_TAG_LICK,
    .oam = &gOamData_83ACA18,
    .anims = gUnknown_83E7638,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B57F8,
};

// not used
static const union AffineAnimCmd gUnknown_83E7654[] =
{
    AFFINEANIMCMD_FRAME(0x200, 0x200, 0, 0),
    AFFINEANIMCMD_END,
};

// not used
static const union AffineAnimCmd *const gUnknown_83E7664[] =
{
    gUnknown_83E7654,
};

const struct SpriteTemplate gUnknown_83E7668 =
{
    .tileTag = ANIM_TAG_WHITE_SHADOW,
    .paletteTag = ANIM_TAG_WHITE_SHADOW,
    .oam = &gOamData_83ACB20,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B5EC0,
};

const struct SpriteTemplate gUnknown_83E7680 =
{
    .tileTag = ANIM_TAG_NAIL,
    .paletteTag = ANIM_TAG_NAIL,
    .oam = &gOamData_83ACB18,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B664C,
};

const struct SpriteTemplate gUnknown_83E7698 =
{
    .tileTag = ANIM_TAG_GHOSTLY_SPIRIT,
    .paletteTag = ANIM_TAG_GHOSTLY_SPIRIT,
    .oam = &gOamData_83ACAF8,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B67D4,
};

const struct SpriteTemplate gUnknown_83E76B0 =
{
    .tileTag = ANIM_TAG_DEVIL,
    .paletteTag = ANIM_TAG_DEVIL,
    .oam = &gOamData_83ACAF8,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B67D4,
};

static const union AnimCmd gUnknown_83E76C8[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(8, 4),
    ANIMCMD_FRAME(16, 4),
    ANIMCMD_FRAME(24, 4),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gUnknown_83E76DC[] =
{
    gUnknown_83E76C8,
};

const struct SpriteTemplate gUnknown_83E76E0 =
{
    .tileTag = ANIM_TAG_PURPLE_FLAME,
    .paletteTag = ANIM_TAG_PURPLE_FLAME,
    .oam = &gOamData_83ACB38,
    .anims = gUnknown_83E76DC,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B6AF8,
};

const struct SpriteTemplate gUnknown_83E76F8 =
{
    .tileTag = 0,
    .paletteTag = 0,
    .oam = &gDummyOamData,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B7158,
};

static void sub_80B5268(struct Sprite *sprite)
{
    InitSpritePosToAnimAttacker(sprite, 1);
    sprite->data[0] = gBattleAnimArgs[2];
    sprite->data[1] = sprite->pos1.x;
    sprite->data[2] = GetBattlerSpriteCoord(gBattleAnimTarget, 2);
    sprite->data[3] = sprite->pos1.y;
    sprite->data[4] = GetBattlerSpriteCoord(gBattleAnimTarget, 3);
    sub_8075678(sprite);
    sprite->callback = sub_80B52D0;
    sprite->data[6] = 16;
    SetGpuReg(REG_OFFSET_BLDCNT, (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL));
    SetGpuReg(REG_OFFSET_BLDALPHA, sprite->data[6]);
}

static void sub_80B52D0(struct Sprite *sprite)
{
    s16 r0, r2;

    sub_80B53C0(sprite);
    if (AnimTranslateLinear(sprite))
    {
        sprite->callback = sub_80B5344;
        return;
    }
    sprite->pos2.x += Sin(sprite->data[5], 10);
    sprite->pos2.y += Cos(sprite->data[5], 15);
    r2 = sprite->data[5];
    sprite->data[5] = (sprite->data[5] + 5) & 0xFF;
    r0 = sprite->data[5];
    if (r2 != 0 && r2 <= 196)
        return;
    if (r0 <= 0)
        return;
    PlaySE12WithPanning(SE_W109, gUnknown_2037F24);
}

static void sub_80B5344(struct Sprite *sprite)
{
    s16 r2, r0;

    sprite->data[0] = 1;
    AnimTranslateLinear(sprite);
    sprite->pos2.x += Sin(sprite->data[5], 10);
    sprite->pos2.y += Cos(sprite->data[5], 15);
    r2 = sprite->data[5];
    sprite->data[5] = (sprite->data[5] + 5) & 0xFF;
    r0 = sprite->data[5];
    if ((r2 == 0 || r2 > 196) && r0 > 0)
        PlaySE(SE_W109);
    if (sprite->data[6] == 0)
    {
        sprite->invisible = TRUE;
        sprite->callback = DestroyAnimSpriteAndDisableBlend;
    }
    else
    {
        sub_80B53C0(sprite);
    }
}

static void sub_80B53C0(struct Sprite *sprite)
{
    s16 r0;

    if (sprite->data[6] > 0xFF)
    {
        if (++sprite->data[6] == 0x10d)
            sprite->data[6] = 0;
        return;
    }
    r0 = sprite->data[7];
    ++sprite->data[7];
    if ((r0 & 0xFF) == 0)
    {
        sprite->data[7] &= 0xff00;
        if ((sprite->data[7] & 0x100) != 0)
            ++sprite->data[6];
        else
            --sprite->data[6];
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(sprite->data[6], 16 - sprite->data[6]));
        if (sprite->data[6] == 0 || sprite->data[6] == 16)
            sprite->data[7] ^= 0x100;
        if (sprite->data[6] == 0)
            sprite->data[6] = 0x100;
    }
}

static void sub_80B5450(struct Sprite *sprite)
{
    InitSpritePosToAnimTarget(sprite, TRUE);
    sprite->callback = sub_80B5470;
    sprite->callback(sprite);
}

static void sub_80B5470(struct Sprite *sprite)
{
    u16 temp1;

    sprite->pos2.x = Sin(sprite->data[0], 32);
    sprite->pos2.y = Cos(sprite->data[0], 8);
    temp1 = sprite->data[0] - 65;
    if (temp1 <= 130)
        sprite->oam.priority = 2;
    else
        sprite->oam.priority = 1;
    sprite->data[0] = (sprite->data[0] + 19) & 0xFF;
    sprite->data[2] += 80;
    sprite->pos2.y += sprite->data[2] >> 8;
    sprite->data[7] += 1;
    if (sprite->data[7] == 61)
        DestroyAnimSprite(sprite);
}

void sub_80B54E8(u8 taskId)
{
    u8 spriteId;

    SetGpuReg(REG_OFFSET_BLDCNT, (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL));
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 0x10));
    spriteId = GetAnimBattlerSpriteId(0);
    PrepareBattlerSpriteForRotScale(spriteId, ST_OAM_OBJ_BLEND);
    SetSpriteRotScale(spriteId, 128, 128, 0);
    gSprites[spriteId].invisible = FALSE;
    gTasks[taskId].data[0] = 128;
    gTasks[taskId].data[1] = *gBattleAnimArgs;
    gTasks[taskId].data[2] = 0;
    gTasks[taskId].data[3] = 16;
    gTasks[taskId].func = sub_80B5570;
}

static void sub_80B5570(u8 taskId)
{
    gTasks[taskId].data[10] += 1;
    if (gTasks[taskId].data[10] == 3)
    {
        gTasks[taskId].data[10] = 0;
        gTasks[taskId].data[2] += 1;
        gTasks[taskId].data[3] -= 1;
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(gTasks[taskId].data[2], gTasks[taskId].data[3]));
        if (gTasks[taskId].data[2] != 9)
            return;
        gTasks[taskId].func = sub_80B55C8;
    }
}

static void sub_80B55C8(u8 taskId)
{
    u8 spriteId;

    if (gTasks[taskId].data[1] > 0)
    {
        gTasks[taskId].data[1] -= 1;
        return;
    }
    spriteId = GetAnimBattlerSpriteId(0);
    gTasks[taskId].data[0] += 8;
    if (gTasks[taskId].data[0] <= 0xFF)
    {
        SetSpriteRotScale(spriteId, gTasks[taskId].data[0], gTasks[taskId].data[0], 0);
    }
    else
    {
        ResetSpriteRotScale(spriteId);
        DestroyAnimVisualTask(taskId);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    }
}

// Spins a sprite towards the target, pausing in the middle.
// Used in Shadow Ball.
// arg 0: duration step 1 (attacker -> center)
// arg 1: duration step 2 (spin center)
// arg 2: duration step 3 (center -> target)
static void InitAnimShadowBall(struct Sprite *sprite)
{
    s16 oldPosX = sprite->pos1.x;
    s16 oldPosY = sprite->pos1.y;

    sprite->pos1.x = GetBattlerSpriteCoord(gBattleAnimAttacker, 2);
    sprite->pos1.y = GetBattlerSpriteCoord(gBattleAnimAttacker, 3);
    sprite->data[0] = 0;
    sprite->data[1] = gBattleAnimArgs[0];
    sprite->data[2] = gBattleAnimArgs[1];
    sprite->data[3] = gBattleAnimArgs[2];
    sprite->data[4] = sprite->pos1.x << 4;
    sprite->data[5] = sprite->pos1.y << 4;
    sprite->data[6] = ((oldPosX - sprite->pos1.x) << 4) / (gBattleAnimArgs[0] << 1);
    sprite->data[7] = ((oldPosY - sprite->pos1.y) << 4) / (gBattleAnimArgs[0] << 1);
    sprite->callback = AnimShadowBallStep;
}

static void AnimShadowBallStep(struct Sprite *sprite)
{
    switch (sprite->data[0])
    {
    case 0:
        sprite->data[4] += sprite->data[6];
        sprite->data[5] += sprite->data[7];
        sprite->pos1.x = sprite->data[4] >> 4;
        sprite->pos1.y = sprite->data[5] >> 4;
        sprite->data[1] -= 1;
        if (sprite->data[1] > 0)
            break;
        sprite->data[0] += 1;
        break;
    case 1:
        sprite->data[2] -= 1;
        if (sprite->data[2] > 0)
            break;
        sprite->data[1] = GetBattlerSpriteCoord(gBattleAnimTarget, 2);
        sprite->data[2] = GetBattlerSpriteCoord(gBattleAnimTarget, 3);
        sprite->data[4] = sprite->pos1.x << 4;
        sprite->data[5] = sprite->pos1.y << 4;
        sprite->data[6] = ((sprite->data[1] - sprite->pos1.x) << 4) / sprite->data[3];
        sprite->data[7] = ((sprite->data[2] - sprite->pos1.y) << 4) / sprite->data[3];
        sprite->data[0] += 1;
        break;
    case 2:
        sprite->data[4] += sprite->data[6];
        sprite->data[5] += sprite->data[7];
        sprite->pos1.x = sprite->data[4] >> 4;
        sprite->pos1.y = sprite->data[5] >> 4;
        sprite->data[3] -= 1;
        if (sprite->data[3] > 0)
            break;
        sprite->pos1.x = GetBattlerSpriteCoord(gBattleAnimTarget, 2);
        sprite->pos1.y = GetBattlerSpriteCoord(gBattleAnimTarget, 3);
        sprite->data[0] += 1;
        break;
    case 3:
        DestroySpriteAndMatrix(sprite);
        break;
    }
}

static void sub_80B57F8(struct Sprite *sprite)
{
    InitSpritePosToAnimTarget(sprite, TRUE);
    sprite->callback = sub_80B5810;
}

static void sub_80B5810(struct Sprite *sprite)
{
    bool8 r5 = FALSE;
    bool8 r6 = FALSE;

    if (sprite->animEnded)
    {
        if (!sprite->invisible)
            sprite->invisible = TRUE;

        switch (sprite->data[0])
        {
        default:
            r6 = TRUE;
            break;
        case 0:
            if (sprite->data[1] == 2)
                r5 = TRUE;
            break;
        case 1:
            if (sprite->data[1] == 4)
                r5 = TRUE;
            break;
        }
        if (r5)
        {
            sprite->invisible ^= 1;
            ++sprite->data[2];
            sprite->data[1] = 0;
            if (sprite->data[2] == 5)
            {
                sprite->data[2] = 0;
                ++sprite->data[0];
            }
        }
        else if (r6)
        {
            DestroyAnimSprite(sprite);
        }
        else
        {
            ++sprite->data[1];
        }
    }
}

void sub_80B58AC(u8 taskId)
{
    struct Task *task;

    task = &gTasks[taskId];
    task->data[0] = CloneBattlerSpriteWithBlend(1);
    if (task->data[0] < 0)
    {
        DestroyAnimVisualTask(taskId);
        return;
    }
    task->data[1] = 0;
    task->data[2] = 15;
    task->data[3] = 2;
    task->data[4] = 0;
    SetGpuReg(REG_OFFSET_BLDCNT, (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL));
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(task->data[2], task->data[3]));
    gSprites[task->data[0]].data[0] = 80;
    if (GetBattlerSide(gBattleAnimTarget) == B_SIDE_PLAYER)
    {
        gSprites[task->data[0]].data[1] = -144;
        gSprites[task->data[0]].data[2] = 112;
    }
    else
    {
        gSprites[task->data[0]].data[1] = 144;
        gSprites[task->data[0]].data[2] = -112;
    }
    gSprites[task->data[0]].data[3] = 0;
    gSprites[task->data[0]].data[4] = 0;
    StoreSpriteCallbackInData6(&gSprites[task->data[0]], SpriteCallbackDummy);
    gSprites[task->data[0]].callback = TranslateSpriteLinearFixedPoint;
    task->func = sub_80B59D4;
}

static void sub_80B59D4(u8 taskId)
{
    struct Task *task;

    task = &gTasks[taskId];
    switch (task->data[4])
    {
    case 0:
        task->data[1] += 1;
        task->data[5] = task->data[1] & 3;
        if (task->data[5] == 1)
            if (task->data[2] > 0)
                task->data[2] -= 1;
        if (task->data[5] == 3)
            if (task->data[3] <= 15)
                task->data[3] += 1;
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(task->data[2], task->data[3]));
        if (task->data[3] != 16 || task->data[2] != 0)
            break;
        if (task->data[1] <= 80)
            break;
        obj_delete_but_dont_free_vram(&gSprites[task->data[0]]);
        task->data[4] = 1;
        break;
    case 1:
        if (++task->data[6] <= 1)
            break;
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        task->data[4] += 1;
        break;
    case 2:
        DestroyAnimVisualTask(taskId);
        break;
    }
}

void sub_80B5AAC(u8 taskId)
{
    struct Task *task;

    task = &gTasks[taskId];
    task->data[15] = 0;
    task->func = sub_80B5AD4;
    task->func(taskId);
}

static void sub_80B5AD4(u8 taskId)
{
    s16 startLine;
    struct Task *task = &gTasks[taskId];
    u8 position = GetBattlerSpriteBGPriorityRank(gBattleAnimTarget);

    switch (task->data[15])
    {
    case 0:
        task->data[14] = AllocSpritePalette(ANIM_TAG_BENT_SPOON);
        if (task->data[14] == 0xFF || task->data[14] == 0xF)
        {
            DestroyAnimVisualTask(taskId);
        }
        else
        {
            task->data[0] = CloneBattlerSpriteWithBlend(1);
            if (task->data[0] < 0)
            {
                FreeSpritePaletteByTag(ANIM_TAG_BENT_SPOON);
                DestroyAnimVisualTask(taskId);
            }
            else
            {
                s16 mask2;

                gSprites[task->data[0]].oam.paletteNum = task->data[14];
                gSprites[task->data[0]].oam.objMode = ST_OAM_OBJ_NORMAL;
                gSprites[task->data[0]].oam.priority = 3;
                gSprites[task->data[0]].invisible = (gBattleSpritesDataPtr->battlerData[gBattleAnimTarget].invisible);
                task->data[1] = 0;
                task->data[2] = 0;
                task->data[3] = 16;
                task->data[13] = GetAnimBattlerSpriteId(1);
                task->data[4] = (gSprites[task->data[13]].oam.paletteNum + 16) * 16;
                if (position == 1)
                {
                    u16 mask = DISPCNT_BG1_ON;

                    mask2 = mask;
                }
                else
                {
                    u16 mask = DISPCNT_BG2_ON;

                    mask2 = mask;
                }
                ClearGpuRegBits(REG_OFFSET_DISPCNT, mask2);
                ++task->data[15];
            }
        }
        break;
    case 1:
        task->data[14] = (task->data[14] + 16) * 16;
        CpuSet(&gPlttBufferUnfaded[task->data[4]], &gPlttBufferFaded[task->data[14]], 0x4000008);
        BlendPalette(task->data[4], 16, 10, RGB(13, 0, 15));
        ++task->data[15];
        break;
    case 2:
        startLine = gSprites[task->data[13]].pos1.y + gSprites[task->data[13]].pos2.y - 32;
        if (startLine < 0)
            startLine = 0;
        if (position == 1)
            task->data[10] = ScanlineEffect_InitWave(startLine, startLine + 64, 2, 6, 0, 4, 1);
        else
            task->data[10] = ScanlineEffect_InitWave(startLine, startLine + 64, 2, 6, 0, 8, 1);
        ++task->data[15];
        break;
    case 3:
        if (position == 1)
            SetGpuReg(REG_OFFSET_BLDCNT, (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL | BLDCNT_TGT1_BG1));
        else
            SetGpuReg(REG_OFFSET_BLDCNT, (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL | BLDCNT_TGT1_BG2));
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 0x10));
        ++task->data[15];
        break;
    case 4:
        if (position == 1)
            SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_BG1_ON);
        else
            SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_BG2_ON);
        task->func = sub_80B5D38;
        ++task->data[15];
        break;
    default:
        ++task->data[15];
        break;
    }
}

static void sub_80B5D38(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    ++task->data[1];
    task->data[5] = task->data[1] & 1;
    if (task->data[5] == 0)
        task->data[2] = gSineTable[task->data[1]] / 18;
    if (task->data[5] == 1)
        task->data[3] = 16 - (gSineTable[task->data[1]] / 18);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(task->data[2], task->data[3]));
    if (task->data[1] == 128)
    {
        task->data[15] = 0;
        task->func = sub_80B5DCC;
        task->func(taskId);
    }
}

static void sub_80B5DCC(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    u8 rank = GetBattlerSpriteBGPriorityRank(gBattleAnimTarget);

    switch (task->data[15])
    {
    case 0:
        gScanlineEffect.state = 3;
        task->data[14] = GetAnimBattlerSpriteId(1);
        if (rank == 1)
            ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_BG1_ON);
        else
            ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_BG2_ON);
        break;
    case 1:
        BlendPalette(task->data[4], 16, 0, RGB(13, 0, 15));
        break;
    case 2:
        gSprites[task->data[14]].invisible = TRUE;
        obj_delete_but_dont_free_vram(&gSprites[task->data[0]]);
        FreeSpritePaletteByTag(ANIM_TAG_BENT_SPOON);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        if (rank == 1)
            SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_BG1_ON);
        else
            SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_BG2_ON);
        DestroyAnimVisualTask(taskId);
        break;
    }
    ++task->data[15];
}

static void sub_80B5EC0(struct Sprite *sprite)
{
    s16 battler1X, battler1Y;
    s16 battler2X, battler2Y;
    s16 yDiff;

    if (gBattleAnimArgs[0] == 0)
    {
        battler1X = GetBattlerSpriteCoord(gBattleAnimAttacker, 0);
        battler1Y = GetBattlerSpriteCoord(gBattleAnimAttacker, 1) + 28;
        battler2X = GetBattlerSpriteCoord(gBattleAnimTarget, 0);
        battler2Y = GetBattlerSpriteCoord(gBattleAnimTarget, 1) + 28;
    }
    else
    {
        battler1X = GetBattlerSpriteCoord(gBattleAnimTarget, 0);
        battler1Y = GetBattlerSpriteCoord(gBattleAnimTarget, 1) + 28;
        battler2X = GetBattlerSpriteCoord(gBattleAnimAttacker, 0);
        battler2Y = GetBattlerSpriteCoord(gBattleAnimAttacker, 1) + 28;
    }
    yDiff = battler2Y - battler1Y;
    sprite->data[0] = battler1X * 16;
    sprite->data[1] = battler1Y * 16;
    sprite->data[2] = ((battler2X - battler1X) * 16) / gBattleAnimArgs[1];
    sprite->data[3] = (yDiff * 16) / gBattleAnimArgs[1];
    sprite->data[4] = gBattleAnimArgs[1];
    sprite->data[5] = battler2X;
    sprite->data[6] = battler2Y;
    sprite->data[7] = sprite->data[4] / 2;
    sprite->oam.priority = 2;
    sprite->pos1.x = battler1X;
    sprite->pos1.y = battler1Y;
    sprite->callback = sub_80B5FE0;
    sprite->invisible = TRUE;
}

static void sub_80B5FE0(struct Sprite *sprite)
{
    if (sprite->data[4])
    {
        sprite->data[0] += sprite->data[2];
        sprite->data[1] += sprite->data[3];
        sprite->pos1.x = sprite->data[0] >> 4;
        sprite->pos1.y = sprite->data[1] >> 4;
        if (--sprite->data[4] == 0)
            sprite->data[0] = 0;
    }
}

void sub_80B6020(u8 taskId)
{
    struct Task *task;
    s16 battler;
    u8 spriteId;
    s16 baseX, baseY;
    s16 x, y;

    task = &gTasks[taskId];
    SetGpuReg(REG_OFFSET_BLDCNT, (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL));
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 0x10));
    task->data[5] = 0;
    task->data[6] = 0;
    task->data[7] = 0;
    task->data[8] = 0;
    task->data[9] = 16;
    task->data[10] = gBattleAnimArgs[0];
    baseX = GetBattlerSpriteCoord(gBattleAnimAttacker, 2);
    baseY = GetBattlerSpriteCoordAttr(gBattleAnimAttacker, BATTLER_COORD_ATTR_BOTTOM);
    if (!IsContest())
    {
        for (battler = 0; battler < 4; ++battler)
        {
            if (battler != gBattleAnimAttacker
             && battler != (gBattleAnimAttacker ^ 2)
             && IsBattlerSpriteVisible(battler))
            {
                spriteId = CreateSprite(&gUnknown_83E7668, baseX, baseY, 55);
                if (spriteId != MAX_SPRITES)
                {
                    x = GetBattlerSpriteCoord(battler, 2);
                    y = GetBattlerSpriteCoordAttr(battler, BATTLER_COORD_ATTR_BOTTOM);
                    gSprites[spriteId].data[0] = baseX << 4;
                    gSprites[spriteId].data[1] = baseY << 4;
                    gSprites[spriteId].data[2] = ((x - baseX) << 4) / gBattleAnimArgs[1];
                    gSprites[spriteId].data[3] = ((y - baseY) << 4) / gBattleAnimArgs[1];
                    gSprites[spriteId].data[4] = gBattleAnimArgs[1];
                    gSprites[spriteId].data[5] = x;
                    gSprites[spriteId].data[6] = y;
                    gSprites[spriteId].callback = sub_80B5FE0;
                    task->data[task->data[12] + 13] = spriteId;
                    ++task->data[12];
                }
            }
        }
    }
    else
    {
        spriteId = CreateSprite(&gUnknown_83E7668, baseX, baseY, 55);
        if (spriteId != MAX_SPRITES)
        {
            x = 48;
            y = 40;
            gSprites[spriteId].data[0] = baseX << 4;
            gSprites[spriteId].data[1] = baseY << 4;
            gSprites[spriteId].data[2] = ((x - baseX) << 4) / gBattleAnimArgs[1];
            gSprites[spriteId].data[3] = ((y - baseY) << 4) / gBattleAnimArgs[1];
            gSprites[spriteId].data[4] = gBattleAnimArgs[1];
            gSprites[spriteId].data[5] = x;
            gSprites[spriteId].data[6] = y;
            gSprites[spriteId].callback = sub_80B5FE0;
            task->data[13] = spriteId;
            task->data[12] = 1;
        }
    }
    task->func = sub_80B623C;
}

static void sub_80B623C(u8 taskId)
{
    u16 i;
    struct Task *task = &gTasks[taskId];

    switch (task->data[0])
    {
    case 0:
        if (task->data[6] == 0)
        {
            if (++task->data[5] > 1)
            {
                task->data[5] = 0;
                ++task->data[7];
                if (task->data[7] & 1)
                {
                    if (task->data[8] < 16)
                        ++task->data[8];
                }
                else
                {
                    if (task->data[9])
                        --task->data[9];
                }
                SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(task->data[8], task->data[9]));
                if (task->data[7] >= 24)
                {
                    task->data[7] = 0;
                    task->data[6] = 1;
                }
            }
        }
        if (task->data[10])
            --task->data[10];
        else if (task->data[6])
            ++task->data[0];
        break;
    case 1:
        if (++task->data[5] > 1)
        {
            task->data[5] = 0;
            ++task->data[7];
            if (task->data[7] & 1)
            {
                if (task->data[8])
                    --task->data[8];
            }
            else if (task->data[9] < 16)
            {
                    ++task->data[9];
            }
            SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(task->data[8], task->data[9]));
            if (task->data[8] == 0 && task->data[9] == 16)
            {
                for (i = 0; i < task->data[12]; ++i)
                    DestroySprite(&gSprites[task->data[i + 13]]);
                ++task->data[0];
            }
        }
        break;
    case 2:
        if (++task->data[5] > 0)
            ++task->data[0];
        break;
    case 3:
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        DestroyAnimVisualTask(taskId);
        break;
    }
}

void sub_80B63B4(u8 taskId)
{
    s16 startX, startY;
    s16 leftDistance, topDistance, bottomDistance, rightDistance;

    gBattle_WIN0H = 0;
    gBattle_WIN0V = 0;
    SetGpuReg(REG_OFFSET_WININ, ((WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR) |
                                    (WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR)));
    SetGpuReg(REG_OFFSET_WINOUT, ((WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ) |
                                    (WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR)));
    SetGpuReg(REG_OFFSET_BLDCNT, (BLDCNT_TGT1_BG3 | BLDCNT_EFFECT_DARKEN));
    SetGpuReg(REG_OFFSET_BLDY, 0x10);
    if (GetBattlerSide(gBattleAnimAttacker) != B_SIDE_PLAYER || IsContest())
        startX = 40;
    else
        startX = 200;
    gBattle_WIN0H = WIN_RANGE(startX, startX);
    startY = 40;
    gBattle_WIN0V = WIN_RANGE(startY, startY);
    leftDistance = startX;
    rightDistance = 240 - startX;
    topDistance = startY;
    bottomDistance = 72;
    gTasks[taskId].data[1] = leftDistance;
    gTasks[taskId].data[2] = rightDistance;
    gTasks[taskId].data[3] = topDistance;
    gTasks[taskId].data[4] = bottomDistance;
    gTasks[taskId].data[5] = startX;
    gTasks[taskId].data[6] = startY;
    gTasks[taskId].func = sub_80B6468;
}

static void sub_80B6468(u8 taskId)
{
    s16 step, leftDistance, rightDistance, topDistance, bottomDistance, startX, startY;
    u16 left, right, top, bottom, selectedPalettes;

    step = gTasks[taskId].data[0];
    ++gTasks[taskId].data[0];
    leftDistance = gTasks[taskId].data[1];
    rightDistance = gTasks[taskId].data[2];
    topDistance = gTasks[taskId].data[3];
    bottomDistance = gTasks[taskId].data[4];
    startX = gTasks[taskId].data[5];
    startY = gTasks[taskId].data[6];
    if (step < 16)
    {
        left   = startX - (leftDistance   * 0.0625) * step;
        right  = startX + (rightDistance  * 0.0625) * step;
        top    = startY - (topDistance    * 0.0625) * step;
        bottom = startY + (bottomDistance * 0.0625) * step;
    }
    else
    {
        left = 0;
        right = 240;
        top = 0;
        bottom = 112;
        selectedPalettes = sub_8075BE8(1, 0, 0, 0, 0, 0, 0);
        BeginNormalPaletteFade(selectedPalettes, 0, 16, 16, RGB(0, 0, 0));
        gTasks[taskId].func = sub_80B65F0;
    }
    gBattle_WIN0H = WIN_RANGE(left, right);
    gBattle_WIN0V = WIN_RANGE(top, bottom);
}

static void sub_80B65F0(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        gBattle_WIN0H = 0;
        gBattle_WIN0V = 0;
        SetGpuReg(REG_OFFSET_WININ, ((WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR) |
                                        (WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR)));
        SetGpuReg(REG_OFFSET_WINOUT, ((WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR) |
                                        (WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR)));
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        DestroyAnimVisualTask(taskId);
    }
}

static void sub_80B664C(struct Sprite *sprite)
{
    s16 xDelta, xDelta2;

    InitSpritePosToAnimAttacker(sprite, 1);
    if (GetBattlerSide(gBattleAnimAttacker) == B_SIDE_PLAYER)
    {
        xDelta = 24;
        xDelta2 = -2;
        sprite->oam.matrixNum = ST_OAM_HFLIP;
    }
    else
    {
        xDelta = -24;
        xDelta2 = 2;
    }
    sprite->pos1.x += xDelta;
    sprite->data[1] = xDelta2;
    sprite->data[0] = 60;
    sprite->callback = sub_80B66A8;
}

static void sub_80B66A8(struct Sprite *sprite)
{
    u16 var0;

    if (sprite->data[0] > 0)
    {
        --sprite->data[0];
    }
    else
    {
        sprite->pos2.x += sprite->data[1];
        var0 = sprite->pos2.x + 7;
        if (var0 > 14)
        {
            sprite->pos1.x += sprite->pos2.x;
            sprite->pos2.x = 0;
            sprite->oam.tileNum += 8;
            if (++sprite->data[2] == 3)
            {
                sprite->data[0] = 30;
                sprite->callback = WaitAnimForDuration;
                StoreSpriteCallbackInData6(sprite, sub_80B6728);
            }
            else
            {
                sprite->data[0] = 40;
            }
        }
    }
}

static void sub_80B6728(struct Sprite *sprite)
{
    if (sprite->data[0] == 0)
    {
        SetGpuReg(REG_OFFSET_BLDCNT, (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL));
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(16, 0));
        ++sprite->data[0];
        sprite->data[1] = 0;
        sprite->data[2] = 0;
    }
    else if (sprite->data[1] < 2)
    {
        ++sprite->data[1];
    }
    else
    {
        sprite->data[1] = 0;
        ++sprite->data[2];
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND2(16 - sprite->data[2], sprite->data[2]));
        if (sprite->data[2] == 16)
        {
            sprite->invisible = TRUE;
            sprite->callback = sub_80B67A0;
        }
    }
}

static void sub_80B67A0(struct Sprite *sprite)
{
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    gBattle_WIN0H = 0;
    gBattle_WIN0V = 0;
    DestroyAnimSprite(sprite);
}

static void sub_80B67D4(struct Sprite *sprite)
{
    u16 coeffB, coeffA;

    sprite->pos2.x = Sin(sprite->data[0], 12);
    if (GetBattlerSide(gBattleAnimAttacker) != B_SIDE_PLAYER)
        sprite->pos2.x = -sprite->pos2.x;
    sprite->data[0] = (sprite->data[0] + 6) & 0xFF;
    sprite->data[1] += 0x100;
    sprite->pos2.y = -(sprite->data[1] >> 8);
    ++sprite->data[7];
    if (sprite->data[7] == 1)
    {
        sprite->data[6] = 0x050B;
        SetGpuReg(REG_OFFSET_BLDCNT, (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL));
        SetGpuReg(REG_OFFSET_BLDALPHA, sprite->data[6]);
    }
    else if (sprite->data[7] > 30)
    {
        ++sprite->data[2];
        coeffB = sprite->data[6] >> 8;
        coeffA = sprite->data[6] & 0xFF;
        if (++coeffB > 16)
            coeffB = 16;
        --coeffA;
        if ((s16)coeffA < 0)
            coeffA = 0;
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(coeffA, coeffB));
        sprite->data[6] = BLDALPHA_BLEND(coeffA, coeffB);
        if (coeffB == 16 && coeffA == 0)
        {
            sprite->invisible = TRUE;
            sprite->callback = sub_80B68A8;
        }
    }
}

static void sub_80B68A8(struct Sprite *sprite)
{
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    DestroyAnimSprite(sprite);
}

void sub_80B68C8(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    task->data[0] = 0;
    task->data[1] = 16;
    task->data[9] = GetBattlerSpriteCoord(gBattleAnimAttacker, 2);
    task->data[10] = GetBattlerYCoordWithElevation(gBattleAnimAttacker);
    task->data[11] = (GetBattlerSpriteCoordAttr(gBattleAnimAttacker, BATTLER_COORD_ATTR_WIDTH) / 2) + 8;
    task->data[7] = 0;
    task->data[5] = GetBattlerSpriteBGPriority(gBattleAnimAttacker);
    task->data[6] = GetBattlerSpriteSubpriority(gBattleAnimAttacker) - 2;
    task->data[3] = 0;
    task->data[4] = 16;
    SetGpuReg(REG_OFFSET_BLDCNT, (BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL));
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 0x10));
    task->data[8] = 0;
    task->func = sub_80B696C;
}

static void sub_80B696C(u8 taskId)
{
    u16 i;
    u8 spriteId;
    struct Task *task = &gTasks[taskId];

    switch (task->data[0])
    {
    case 0:
        for (i = 0; i < 6; ++i)
        {
            spriteId = CreateSprite(&gUnknown_83E76E0, task->data[9], task->data[10], task->data[6]);
            if (spriteId != MAX_SPRITES)
            {
                gSprites[spriteId].data[0] = taskId;
                gSprites[spriteId].data[1] = GetBattlerSide(gBattleAnimAttacker) == B_SIDE_PLAYER;
                gSprites[spriteId].data[2] = (i * 42) & 0xFF;
                gSprites[spriteId].data[3] = task->data[11];
                gSprites[spriteId].data[5] = i * 6;
                ++task->data[7];
            }
        }
        ++task->data[0];
        break;
    case 1:
        if (++task->data[1] & 1)
        {
            if (task->data[3] < 14)
                ++task->data[3];
        }
        else if (task->data[4] > 4)
        {
            --task->data[4];
        }
        if (task->data[3] == 14 && task->data[4] == 4)
        {
            task->data[1] = 0;
            ++task->data[0];
        }
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(task->data[3], task->data[4]));
        break;
    case 2:
        if (++task->data[1] > 30)
        {
            task->data[1] = 0;
            ++task->data[0];
        }
        break;
    case 3:
        if (++task->data[1] & 1)
        {
            if (task->data[3] > 0)
                --task->data[3];
        }
        else if (task->data[4] < 16)
        {
            ++task->data[4];
        }

        if (task->data[3] == 0 && task->data[4] == 16)
        {
            task->data[8] = 1;
            ++task->data[0];
        }
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(task->data[3], task->data[4]));
        break;
    case 4:
        if (task->data[7] == 0)
            ++task->data[0];
        break;
    case 5:
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        DestroyAnimVisualTask(taskId);
        break;
    }
}

static void sub_80B6AF8(struct Sprite *sprite)
{
    u16 index;

    if (sprite->data[1] == 0)
        sprite->data[2] += 2;
    else
        sprite->data[2] -= 2;
    sprite->data[2] &= 0xFF;
    sprite->pos2.x = Sin(sprite->data[2], sprite->data[3]);
    index = sprite->data[2] - 65;
    if (index < 127)
        sprite->oam.priority = gTasks[sprite->data[0]].data[5] + 1;
    else
        sprite->oam.priority = gTasks[sprite->data[0]].data[5];
    ++sprite->data[5];
    sprite->data[6] = (sprite->data[5] * 8) & 0xFF;
    sprite->pos2.y = Sin(sprite->data[6], 7);
    if (gTasks[sprite->data[0]].data[8])
    {
        --gTasks[sprite->data[0]].data[7];
        DestroySprite(sprite);
    }
}

void sub_80B6BBC(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    task->data[15] = 0;
    task->func = sub_80B6BE4;
    sub_80B6BE4(taskId);
}

static void sub_80B6BE4(u8 taskId)
{
    s16 y;
    struct BattleAnimBgData animBgData;
    struct Task *task = &gTasks[taskId];
    u8 rank = GetBattlerSpriteBGPriorityRank(gBattleAnimAttacker);

    switch (task->data[15])
    {
    case 0:
        SetAnimBgAttribute(1, BG_ANIM_PRIORITY, 2);
        SetAnimBgAttribute(2, BG_ANIM_PRIORITY, 1);
        task->data[1] = 0;
        task->data[2] = 0;
        task->data[3] = 16;
        task->data[4] = GetAnimBattlerSpriteId(0);
        task->data[5] = gSprites[task->data[4]].oam.priority;
        task->data[6] = (gSprites[task->data[4]].oam.paletteNum + 16) << 4;
        gSprites[task->data[4]].oam.objMode = ST_OAM_OBJ_BLEND;
        gSprites[task->data[4]].oam.priority = 3;
        task->data[7] = 128;
        break;
    case 1:
        ++task->data[1];
        if (task->data[1] & 1)
            return;
        BlendPalette(task->data[6], 0x10, task->data[2], RGB(0, 23, 25));
        BlendPalette(task->data[7], 0x10, task->data[2], RGB(0, 23, 25));
        if (task->data[2] <= 11)
        {
            ++task->data[2];
            return;
        }
        task->data[1] = 0;
        task->data[2] = 0;
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL);
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 0x10));
        break;
    case 2:
        SetAnimBgAttribute(2, BG_ANIM_CHAR_BASE_BLOCK, 1);
        SetAnimBgAttribute(2, BG_ANIM_SCREEN_SIZE, 0);
        gBattle_BG2_X = 0;
        gBattle_BG2_Y = 0;
        SetGpuReg(REG_OFFSET_BG2HOFS, gBattle_BG2_X);
        SetGpuReg(REG_OFFSET_BG2VOFS, gBattle_BG2_Y);
        sub_80752C8(&animBgData, 2);
        AnimLoadCompressedBgGfx(animBgData.bgId, gFile_graphics_battle_anims_backgrounds_scary_face_sheet, animBgData.tilesOffset);
        LoadCompressedPalette(gFile_graphics_battle_anims_backgrounds_scary_face_palette, 16 * animBgData.paletteId, 0x20);
        break;
    case 3:
        sub_80752C8(&animBgData, 2);
        gMonSpritesGfxPtr->field_17C = AllocZeroed(0x2000);
        LZDecompressWram(gFile_graphics_battle_anims_backgrounds_scary_face_player_tilemap, gMonSpritesGfxPtr->field_17C);
        sub_80730C0(animBgData.paletteId, gMonSpritesGfxPtr->field_17C, 256, 0);
        CopyToBgTilemapBufferRect_ChangePalette(animBgData.bgId, gMonSpritesGfxPtr->field_17C, 0, 0, 0x20, 0x20, 0x11);
        CopyBgTilemapBufferToVram(2);
        FREE_AND_SET_NULL(gMonSpritesGfxPtr->field_17C);
        break;
    case 4:
        ++task->data[1];
        if (task->data[1] & 1)
            return;
        ++task->data[2];
        --task->data[3];
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(task->data[2], task->data[3]));
        if (task->data[3])
            return;
        task->data[1] = 0;
        task->data[2] = 0;
        task->data[3] = 16;
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG1 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL);
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 0x10));
        SetAnimBgAttribute(1, BG_ANIM_PRIORITY, 1);
        SetAnimBgAttribute(2, BG_ANIM_PRIORITY, 2);
        break;
    case 5:
        if (rank == 1)
            ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_BG1_ON);
        else
            ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_BG2_ON);
        break;
    case 6:
        y = gSprites[task->data[4]].pos1.y + gSprites[task->data[4]].pos2.y - 0x20;
        if (y < 0)
            y = 0;
        if (rank == 1)
            task->data[10] = ScanlineEffect_InitWave(y, y + 0x40, 4, 8, 0, 4, 1);
        else
            task->data[10] = ScanlineEffect_InitWave(y, y + 0x40, 4, 8, 0, 8, 1);
        break;
    case 7:
        BlendPalette(task->data[7], 0x10, 0xC, RGB(31, 31, 29));
        if (rank == 1)
            SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_BG1_ON);
        else
            SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_BG2_ON);
        task->func = sub_80B6F30;
        task->data[15] = 0;
        break;
    }
    ++task->data[15];
}

static void sub_80B6F30(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    ++task->data[1];
    task->data[8] = task->data[1] & 1;
    if (!task->data[8])
        task->data[2] = gSineTable[task->data[1]] / 18;
    if (task->data[8] == 1)
        task->data[3] = 16 - gSineTable[task->data[1]] / 18;
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(task->data[2], task->data[3]));
    if (task->data[1] == 128)
    {
        task->data[15] = 0;
        task->func = sub_80B6FC4;
        sub_80B6FC4(taskId);
    }
}

static void sub_80B6FC4(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    switch (task->data[15])
    {
    case 0:
        gScanlineEffect.state = 3;
        BlendPalette(task->data[7], 0x10, 0xC, RGB(0, 23, 25));
        break;
    case 1:
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL);
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0x10, 0));
        task->data[2] = 16;
        task->data[3] = 0;
        break;
    case 2:
        --task->data[2];
        ++task->data[3];
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(task->data[2], task->data[3]));
        if (task->data[3] <= 15)
            return;
        SetAnimBgAttribute(1, BG_ANIM_PRIORITY, 2);
        SetAnimBgAttribute(2, BG_ANIM_PRIORITY, 2);
        break;
    case 3:
        sub_8075358(2);
        FillPalette(0, 0x90, 0x20);
        SetAnimBgAttribute(2, BG_ANIM_CHAR_BASE_BLOCK, 0);
        task->data[1] = 12;
        break;
    case 4:
        BlendPalette(task->data[6], 0x10, task->data[1], RGB(0, 23, 25));
        BlendPalette(task->data[7], 0x10, task->data[1], RGB(0, 23, 25));
        if ( task->data[1] )
        {
            --task->data[1];
            return;
        }
        task->data[1] = 0;
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL);
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 0x10));
        break;
    case 5:
        gSprites[task->data[4]].oam.priority = task->data[5];
        gSprites[task->data[4]].oam.objMode = ST_OAM_OBJ_NORMAL;
        SetAnimBgAttribute(1, BG_ANIM_PRIORITY, 1);
        SetAnimBgAttribute(2, BG_ANIM_PRIORITY, 1);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_EFFECT_NONE);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        DestroyAnimVisualTask(taskId);
        break;
    }
    ++task->data[15];
}

static void sub_80B7158(struct Sprite *sprite)
{
    sprite->invisible = TRUE;
    sprite->data[5] = gBattlerSpriteIds[gBattleAnimAttacker];
    sprite->data[0] = 128;
    sprite->data[1] = 10;
    sprite->data[2] = gBattleAnimArgs[0];
    sprite->data[3] = gBattleAnimArgs[1];
    sprite->callback = sub_80B71B0;
    gSprites[sprite->data[5]].pos1.y += 8;
}

static void sub_80B71B0(struct Sprite *sprite)
{
    if (sprite->data[3])
    {
        --sprite->data[3];
        gSprites[sprite->data[5]].pos2.x = Sin(sprite->data[0], sprite->data[1]);
        gSprites[sprite->data[5]].pos2.y = Cos(sprite->data[0], sprite->data[1]);
        sprite->data[0] += sprite->data[2];
        if (sprite->data[0] > 255)
            sprite->data[0] -= 256;
    }
    else
    {
        gSprites[sprite->data[5]].pos2.x = 0;
        gSprites[sprite->data[5]].pos2.y = 0;
        gSprites[sprite->data[5]].pos1.y -= 8;
        sprite->callback = DestroySpriteAndMatrix;
    }
}

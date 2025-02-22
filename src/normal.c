#include "global.h"
#include "battle_anim.h"
#include "palette.h"
#include "random.h"
#include "task.h"
#include "trig.h"

static void AnimConfusionDuck(struct Sprite *sprite);
static void AnimSimplePaletteBlend(struct Sprite *sprite);
static void sub_80B9A7C(struct Sprite *sprite);
static void sub_80B9B8C(struct Sprite *sprite);
static void sub_80BA27C(struct Sprite *sprite);
static void sub_80BA560(struct Sprite *sprite);
static void sub_80BA5F8(struct Sprite *sprite);
static void sub_80BA630(struct Sprite *sprite);
static void sub_80BA6C8(struct Sprite *sprite);
static void sub_80BA738(struct Sprite *sprite);
static void sub_80BA780(struct Sprite *sprite);
static void sub_80BA5A8(struct Sprite *sprite);
static void AnimConfusionDuckStep(struct Sprite *sprite);
static void AnimSimplePaletteBlendStep(struct Sprite *sprite);
static void sub_80B9AD0(struct Sprite *sprite);
static void sub_80B9B5C(struct Sprite *sprite);
static void sub_80B9C2C(u8 taskId, u8 initialBlendAmount, u8 targetBlendAmount);
static void sub_80B9C7C(u8 taskId);
static void sub_80B9DA0(u8 taskId, u8 initialBlendAmount, u8 targetBlendAmount);
static void sub_80B9DF0(u8 taskId);
static void sub_80B9EA8(u8 taskId, u8 initialBlendAmount, u8 targetBlendAmount);
static void sub_80B9F04(u8 taskId);
static void sub_80B9FD8(u8 taskId);
static void sub_80BA090(u8 taskId);
static void sub_80BA3CC(void);
static void sub_80BA320(struct Sprite *sprite);
static void sub_80BA4D0(u8 taskId);
static void sub_80BA7BC(struct Sprite *sprite);


static const union AnimCmd gUnknown_83E7ADC[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_FRAME(0, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd gUnknown_83E7AF0[] =
{
    ANIMCMD_FRAME(0, 8, .hFlip = TRUE),
    ANIMCMD_FRAME(4, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(8, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gUnknown_83E7B04[] =
{
    gUnknown_83E7ADC,
    gUnknown_83E7AF0,
};

const struct SpriteTemplate gConfusionDuckSpriteTemplate =
{
    .tileTag = ANIM_TAG_DUCK,
    .paletteTag = ANIM_TAG_DUCK,
    .oam = &gOamData_83AC9D0,
    .anims = gUnknown_83E7B04,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = AnimConfusionDuck,
};

const struct SpriteTemplate gSimplePaletteBlendSpriteTemplate =
{
    .tileTag = 0,
    .paletteTag = 0,
    .oam = &gDummyOamData,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = AnimSimplePaletteBlend,
};

const struct SpriteTemplate gComplexPaletteBlendSpriteTemplate =
{
    .tileTag = 0,
    .paletteTag = 0,
    .oam = &gDummyOamData,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B9A7C,
};

static const union AnimCmd gUnknown_83E7B54[] =
{
    ANIMCMD_FRAME(0, 3),
    ANIMCMD_FRAME(16, 3),
    ANIMCMD_FRAME(32, 3),
    ANIMCMD_FRAME(48, 3),
    ANIMCMD_FRAME(64, 3),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const gUnknown_83E7B6C[] =
{
    gUnknown_83E7B54,
};

const struct SpriteTemplate gUnknown_83E7B70 =
{
    .tileTag = ANIM_TAG_SPARKLE_4,
    .paletteTag = ANIM_TAG_SPARKLE_4,
    .oam = &gOamData_83AC9D8,
    .anims = gUnknown_83E7B6C,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B9B8C,
};

const struct SpriteTemplate gUnknown_83E7B88 =
{
    .tileTag = 0,
    .paletteTag = 0,
    .oam = &gDummyOamData,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80BA27C,
};

static const union AffineAnimCmd gUnknown_83E7BA0[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, 0, 8),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E7BB0[] =
{
    AFFINEANIMCMD_FRAME(0xD8, 0xD8, 0, 0),
    AFFINEANIMCMD_FRAME(0x0, 0x0, 0, 8),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E7BC8[] =
{
    AFFINEANIMCMD_FRAME(0xB0, 0xB0, 0, 0),
    AFFINEANIMCMD_FRAME(0x0, 0x0, 0, 8),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E7BE0[] =
{
    AFFINEANIMCMD_FRAME(0x80, 0x80, 0, 0),
    AFFINEANIMCMD_FRAME(0x0, 0x0, 0, 8),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd *const gUnknown_83E7BF8[] =
{
    gUnknown_83E7BA0,
    gUnknown_83E7BB0,
    gUnknown_83E7BC8,
    gUnknown_83E7BE0,
};

const struct SpriteTemplate gBasicHitSplatSpriteTemplate =
{
    .tileTag = ANIM_TAG_IMPACT,
    .paletteTag = ANIM_TAG_IMPACT,
    .oam = &gOamData_83ACB58,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E7BF8,
    .callback = sub_80BA560,
};

const struct SpriteTemplate gUnknown_83E7C20 =
{
    .tileTag = ANIM_TAG_IMPACT,
    .paletteTag = ANIM_TAG_IMPACT,
    .oam = &gOamData_83ACB58,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E7BF8,
    .callback = sub_80BA5F8,
};

const struct SpriteTemplate gUnknown_83E7C38 =
{
    .tileTag = ANIM_TAG_WATER_IMPACT,
    .paletteTag = ANIM_TAG_WATER_IMPACT,
    .oam = &gOamData_83ACB58,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E7BF8,
    .callback = sub_80BA560,
};

const struct SpriteTemplate gUnknown_83E7C50 =
{
    .tileTag = ANIM_TAG_IMPACT,
    .paletteTag = ANIM_TAG_IMPACT,
    .oam = &gOamData_83ACB58,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E7BF8,
    .callback = sub_80BA630,
};

const struct SpriteTemplate gUnknown_83E7C68 =
{
    .tileTag = ANIM_TAG_IMPACT,
    .paletteTag = ANIM_TAG_IMPACT,
    .oam = &gOamData_83ACB58,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E7BF8,
    .callback = sub_80BA6C8,
};

const struct SpriteTemplate gUnknown_83E7C80 =
{
    .tileTag = ANIM_TAG_CROSS_IMPACT,
    .paletteTag = ANIM_TAG_CROSS_IMPACT,
    .oam = &gOamData_83ACAF8,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80BA738,
};

const struct SpriteTemplate gUnknown_83E7C98 =
{
    .tileTag = ANIM_TAG_IMPACT,
    .paletteTag = ANIM_TAG_IMPACT,
    .oam = &gOamData_83ACA38,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E7BF8,
    .callback = sub_80BA780,
};

const struct SpriteTemplate gUnknown_83E7CB0 =
{
    .tileTag = ANIM_TAG_IMPACT,
    .paletteTag = ANIM_TAG_IMPACT,
    .oam = &gOamData_83ACB58,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E7BF8,
    .callback = sub_80BA5A8,
};

// Moves a spinning duck around the mon's head.
// arg 0: initial x pixel offset
// arg 1: initial y pixel offset
// arg 2: initial wave offset
// arg 3: wave period (higher means faster wave)
// arg 4: duration
static void AnimConfusionDuck(struct Sprite *sprite)
{
    sprite->pos1.x += gBattleAnimArgs[0];
    sprite->pos1.y += gBattleAnimArgs[1];
    sprite->data[0] = gBattleAnimArgs[2];
    if (GetBattlerSide(gBattleAnimAttacker) != B_SIDE_PLAYER)
    {
        sprite->data[1] = -gBattleAnimArgs[3];
        sprite->data[4] = 1;
    }
    else
    {
        sprite->data[1] = gBattleAnimArgs[3];
        sprite->data[4] = 0;
        StartSpriteAnim(sprite, 1);
    }
    sprite->data[3] = gBattleAnimArgs[4];
    sprite->callback = AnimConfusionDuckStep;
    sprite->callback(sprite);
}

static void AnimConfusionDuckStep(struct Sprite *sprite)
{
    sprite->pos2.x = Cos(sprite->data[0], 30);
    sprite->pos2.y = Sin(sprite->data[0], 10);
    if ((u16)sprite->data[0] < 128)
        sprite->oam.priority = 1;
    else
        sprite->oam.priority = 3;
    sprite->data[0] = (sprite->data[0] + sprite->data[1]) & 0xFF;
    if (++sprite->data[2] == sprite->data[3])
        DestroyAnimSprite(sprite);
}

// Performs a simple color blend on a specified sprite.
// arg 0: palette selector
// arg 1: delay
// arg 2: start blend amount
// arg 3: end blend amount
// arg 4: blend color
static void AnimSimplePaletteBlend(struct Sprite *sprite)
{
    u32 selectedPalettes = UnpackSelectedBattleAnimPalettes(gBattleAnimArgs[0]);
    
    BeginNormalPaletteFade(selectedPalettes, gBattleAnimArgs[1], gBattleAnimArgs[2], gBattleAnimArgs[3], gBattleAnimArgs[4]);
    sprite->invisible = TRUE;
    sprite->callback = AnimSimplePaletteBlendStep;
}

// Unpacks a bitfield and returns a bitmask of its selected palettes.
// Bits 0-6 of the selector parameter result in the following palettes being selected:
//   0: battle background palettes (BG palettes 1, 2, and 3)
//   1: gBattleAnimAttacker OBJ palette
//   2: gBattleAnimTarget OBJ palette
//   3: gBattleAnimAttacker partner OBJ palette
//   4: gBattleAnimTarget partner OBJ palette
//   5: BG palette 4
//   6: BG palette 5
u32 UnpackSelectedBattleAnimPalettes(s16 selector)
{
    u8 battleBackground = selector & 1;
    u8 attacker = (selector >> 1) & 1;
    u8 target = (selector >> 2) & 1;
    u8 attackerPartner = (selector >> 3) & 1;
    u8 targetPartner = (selector >> 4) & 1;
    u8 arg5 = (selector >> 5) & 1;
    u8 arg6 = (selector >> 6) & 1;

    return sub_8075BE8(battleBackground, attacker, target, attackerPartner, targetPartner, arg5, arg6);
}

static void AnimSimplePaletteBlendStep(struct Sprite *sprite)
{
    if (!gPaletteFade.active)
        DestroyAnimSprite(sprite);
}

static void sub_80B9A7C(struct Sprite *sprite)
{
    u32 selectedPalettes;

    sprite->data[0] = gBattleAnimArgs[1];
    sprite->data[1] = gBattleAnimArgs[1];
    sprite->data[2] = gBattleAnimArgs[2];
    sprite->data[3] = gBattleAnimArgs[3];
    sprite->data[4] = gBattleAnimArgs[4];
    sprite->data[5] = gBattleAnimArgs[5];
    sprite->data[6] = gBattleAnimArgs[6];
    sprite->data[7] = gBattleAnimArgs[0];
    selectedPalettes = UnpackSelectedBattleAnimPalettes(sprite->data[7]);
    BlendPalettes(selectedPalettes, gBattleAnimArgs[4], gBattleAnimArgs[3]);
    sprite->invisible = TRUE;
    sprite->callback = sub_80B9AD0;
}

static void sub_80B9AD0(struct Sprite *sprite)
{
    u32 selectedPalettes;

    if (sprite->data[0] > 0)
    {
        --sprite->data[0];
        return;
    }
    if (gPaletteFade.active)
        return;
    if (sprite->data[2] == 0)
    {
        sprite->callback = sub_80B9B5C;
        return;
    }
    selectedPalettes = UnpackSelectedBattleAnimPalettes(sprite->data[7]);
    if (sprite->data[1] & 0x100)
        BlendPalettes(selectedPalettes, sprite->data[4], sprite->data[3]);
    else
        BlendPalettes(selectedPalettes, sprite->data[6], sprite->data[5]);
    sprite->data[1] ^= 0x100;
    sprite->data[0] = sprite->data[1] & 0xFF;
    --sprite->data[2];
}

static void sub_80B9B5C(struct Sprite *sprite)
{
    u32 selectedPalettes;

    if (!gPaletteFade.active)
    {
        selectedPalettes = UnpackSelectedBattleAnimPalettes(sprite->data[7]);
        BlendPalettes(selectedPalettes, 0, 0);
        DestroyAnimSprite(sprite);
    }
}

static void sub_80B9B8C(struct Sprite *sprite)
{
    sprite->pos1.x += gBattleAnimArgs[0];
    sprite->pos1.y += gBattleAnimArgs[1];
    sprite->data[0] = 0;
    sprite->data[1] = 10;
    sprite->data[2] = 8;
    sprite->data[3] = 40;
    sprite->data[4] = 112;
    sprite->data[5] = 0;
    StoreSpriteCallbackInData6(sprite, DestroySpriteAndMatrix);
    sprite->callback = TranslateSpriteInGrowingCircleOverDuration;
    sprite->callback(sprite);
}

void sub_80B9BDC(u8 taskId)
{
    gTasks[taskId].data[0] = gBattleAnimArgs[0];
    gTasks[taskId].data[1] = gBattleAnimArgs[1];
    gTasks[taskId].data[2] = gBattleAnimArgs[2];
    gTasks[taskId].data[3] = gBattleAnimArgs[3];
    gTasks[taskId].data[4] = gBattleAnimArgs[4];
    gTasks[taskId].data[5] = gBattleAnimArgs[5];
    gTasks[taskId].data[8] = 0;
    sub_80B9C2C(taskId, 0, gTasks[taskId].data[4]);
    gTasks[taskId].func = sub_80B9C7C;
}

static void sub_80B9C2C(u8 taskId, u8 initialBlendAmount, u8 targetBlendAmount)
{
    u32 selectedPalettes = UnpackSelectedBattleAnimPalettes(gTasks[taskId].data[0]);
    
    BeginNormalPaletteFade(selectedPalettes,
                           gTasks[taskId].data[1],
                           initialBlendAmount,
                           targetBlendAmount,
                           gTasks[taskId].data[5]);
    --gTasks[taskId].data[2];
    gTasks[taskId].data[8] ^= 1;
}

static void sub_80B9C7C(u8 taskId)
{
    u8 initialBlendAmount, targetBlendAmount;

    if (!gPaletteFade.active)
    {
        if (gTasks[taskId].data[2] > 0)
        {
            if (gTasks[taskId].data[8] == 0)
            {
                initialBlendAmount = gTasks[taskId].data[3];
                targetBlendAmount = gTasks[taskId].data[4];
            }
            else
            {
                initialBlendAmount = gTasks[taskId].data[4];
                targetBlendAmount = gTasks[taskId].data[3];
            }
            if (gTasks[taskId].data[2] == 1)
                targetBlendAmount = 0;
            sub_80B9C2C(taskId, initialBlendAmount, targetBlendAmount);
        }
        else
        {
            DestroyAnimVisualTask(taskId);
        }
    }
}

void sub_80B9CE4(u8 taskId)
{
    s32 battler;
    u32 selectedPalettes = 0;

    gTasks[taskId].data[0] = gBattleAnimArgs[0];
    gTasks[taskId].data[1] = gBattleAnimArgs[1];
    gTasks[taskId].data[2] = gBattleAnimArgs[2];
    gTasks[taskId].data[3] = gBattleAnimArgs[3];
    gTasks[taskId].data[4] = gBattleAnimArgs[4];
    gTasks[taskId].data[5] = gBattleAnimArgs[5];
    gTasks[taskId].data[8] = 0;
    for (battler = 0; battler < gBattlersCount; ++battler)
        if (battler != gBattleAnimAttacker && battler != gBattleAnimTarget)
            selectedPalettes |= 1 << (battler + 16);
    if (gBattleAnimArgs[0] == 1)
        selectedPalettes |= 0xE;
    gTasks[taskId].data[9] = selectedPalettes >> 16;
    gTasks[taskId].data[10] = selectedPalettes & 0xFF;
    sub_80B9DA0(taskId, 0, gTasks[taskId].data[4]);
    gTasks[taskId].func = sub_80B9DF0;
}

static void sub_80B9DA0(u8 taskId, u8 initialBlendAmount, u8 targetBlendAmount)
{
    u32 selectedPalettes = ((u16)gTasks[taskId].data[9] << 16) | (u16)gTasks[taskId].data[10];
    
    BeginNormalPaletteFade(selectedPalettes,
                           gTasks[taskId].data[1],
                           initialBlendAmount,
                           targetBlendAmount,
                           gTasks[taskId].data[5]);
    --gTasks[taskId].data[2];
    gTasks[taskId].data[8] ^= 1;
}

static void sub_80B9DF0(u8 taskId)
{
    u8 initialBlendAmount, targetBlendAmount;

    if (!gPaletteFade.active)
    {
        if (gTasks[taskId].data[2] > 0)
        {
            if (gTasks[taskId].data[8] == 0)
            {
                initialBlendAmount = gTasks[taskId].data[3];
                targetBlendAmount = gTasks[taskId].data[4];
            }
            else
            {
                initialBlendAmount = gTasks[taskId].data[4];
                targetBlendAmount = gTasks[taskId].data[3];
            }

            if (gTasks[taskId].data[2] == 1)
                targetBlendAmount = 0;
            sub_80B9DA0(taskId, initialBlendAmount, targetBlendAmount);
        }
        else
        {
            DestroyAnimVisualTask(taskId);
        }
    }
}

void sub_80B9E58(u8 taskId)
{
    u8 paletteIndex;

    gTasks[taskId].data[0] = gBattleAnimArgs[0];
    gTasks[taskId].data[1] = gBattleAnimArgs[1];
    gTasks[taskId].data[2] = gBattleAnimArgs[2];
    gTasks[taskId].data[3] = gBattleAnimArgs[3];
    gTasks[taskId].data[4] = gBattleAnimArgs[4];
    gTasks[taskId].data[5] = gBattleAnimArgs[5];
    gTasks[taskId].data[8] = 0;
    sub_80B9EA8(taskId, 0, gTasks[taskId].data[4]);
    gTasks[taskId].func = sub_80B9F04;
}

static void sub_80B9EA8(u8 taskId, u8 initialBlendAmount, u8 targetBlendAmount)
{
    u8 paletteIndex = IndexOfSpritePaletteTag(gTasks[taskId].data[0]);
    
    BeginNormalPaletteFade(1 << (paletteIndex + 16),
                           gTasks[taskId].data[1],
                           initialBlendAmount,
                           targetBlendAmount,
                           gTasks[taskId].data[5]);
    --gTasks[taskId].data[2];
    gTasks[taskId].data[8] ^= 1;
}

static void sub_80B9F04(u8 taskId)
{
    u8 initialBlendAmount, targetBlendAmount;

    if (!gPaletteFade.active)
    {
        if (gTasks[taskId].data[2] > 0)
        {
            if (gTasks[taskId].data[8] == 0)
            {
                initialBlendAmount = gTasks[taskId].data[3];
                targetBlendAmount = gTasks[taskId].data[4];
            }
            else
            {
                initialBlendAmount = gTasks[taskId].data[4];
                targetBlendAmount = gTasks[taskId].data[3];
            }

            if (gTasks[taskId].data[2] == 1)
                targetBlendAmount = 0;
            sub_80B9EA8(taskId, initialBlendAmount, targetBlendAmount);
        }
        else
        {
            DestroyAnimVisualTask(taskId);
        }
    }
}

void sub_80B9F6C(u8 taskId)
{
    u8 paletteIndex;

    gTasks[taskId].data[0] = gBattleAnimArgs[1];
    gTasks[taskId].data[1] = gBattleAnimArgs[1];
    gTasks[taskId].data[2] = gBattleAnimArgs[2];
    gTasks[taskId].data[3] = gBattleAnimArgs[3];
    gTasks[taskId].data[4] = gBattleAnimArgs[4];
    gTasks[taskId].data[5] = gBattleAnimArgs[5];
    gTasks[taskId].data[6] = gBattleAnimArgs[6];
    gTasks[taskId].data[7] = gBattleAnimArgs[0];
    paletteIndex = IndexOfSpritePaletteTag(gBattleAnimArgs[0]);
    BeginNormalPaletteFade(1 << (paletteIndex + 16),
                           0,
                           gBattleAnimArgs[4],
                           gBattleAnimArgs[4],
                           gBattleAnimArgs[3]);
    gTasks[taskId].func = sub_80B9FD8;
}

static void sub_80B9FD8(u8 taskId)
{
    u32 selectedPalettes;

    if (gTasks[taskId].data[0] > 0)
    {
        --gTasks[taskId].data[0];
        return;
    }
    if (gPaletteFade.active)
        return;
    if (gTasks[taskId].data[2] == 0)
    {
        gTasks[taskId].func = sub_80BA090;
        return;
    }
    selectedPalettes = 1 << (IndexOfSpritePaletteTag(gTasks[taskId].data[7]) + 16);
    if (gTasks[taskId].data[1] & 0x100)
        BeginNormalPaletteFade(selectedPalettes,
                               0,
                               gTasks[taskId].data[4],
                               gTasks[taskId].data[4],
                               gTasks[taskId].data[3]);
    else
        BeginNormalPaletteFade(selectedPalettes,
                               0,
                               gTasks[taskId].data[6],
                               gTasks[taskId].data[6],
                               gTasks[taskId].data[5]);
    gTasks[taskId].data[1] ^= 0x100;
    gTasks[taskId].data[0] = gTasks[taskId].data[1] & 0xFF;
    --gTasks[taskId].data[2];
}

static void sub_80BA090(u8 taskId)
{
    u32 selectedPalettes;

    if (!gPaletteFade.active)
    {
        selectedPalettes = 1 << (IndexOfSpritePaletteTag(gTasks[taskId].data[7]) + 16);
        BeginNormalPaletteFade(selectedPalettes, 0, 0, 0, RGB(0, 0, 0));
        DestroyAnimVisualTask(taskId);
    }
}

void sub_80BA0E8(u8 taskId)
{
    u32 selectedPalettes = 0;
    u8 attackerBattler = gBattleAnimAttacker;
    u8 targetBattler = gBattleAnimTarget;

    if (gBattleAnimArgs[0] & 0x100)
        selectedPalettes = sub_8075BE8(1, 0, 0, 0, 0, 0, 0);
    if (gBattleAnimArgs[1] & 0x100)
        selectedPalettes |= (0x10000 << attackerBattler);
    if (gBattleAnimArgs[2] & 0x100)
        selectedPalettes |= (0x10000 << targetBattler);
    InvertPlttBuffer(selectedPalettes);
    DestroyAnimVisualTask(taskId);
}

// not used
static void sub_80BA16C(u8 taskId)
{
    u8 attackerBattler;
    u8 targetBattler;
    u8 paletteIndex;
    u32 selectedPalettes = 0;

    if (gTasks[taskId].data[0] == 0)
    {
        gTasks[taskId].data[2] = gBattleAnimArgs[0];
        gTasks[taskId].data[3] = gBattleAnimArgs[1];
        gTasks[taskId].data[4] = gBattleAnimArgs[2];
        gTasks[taskId].data[1] = gBattleAnimArgs[3];
        gTasks[taskId].data[5] = gBattleAnimArgs[4];
        gTasks[taskId].data[6] = gBattleAnimArgs[5];
        gTasks[taskId].data[7] = gBattleAnimArgs[6];
    }
    ++gTasks[taskId].data[0];
    attackerBattler = gBattleAnimAttacker;
    targetBattler = gBattleAnimTarget;
    if (gTasks[taskId].data[2] & 0x100)
        selectedPalettes = 0x0000FFFF;
    if (gTasks[taskId].data[2] & 0x1)
    {
        paletteIndex = IndexOfSpritePaletteTag(gSprites[gHealthboxSpriteIds[attackerBattler]].template->paletteTag);
        selectedPalettes |= (1 << paletteIndex) << 16;
    }
    if (gTasks[taskId].data[3] & 0x100)
        selectedPalettes |= (1 << attackerBattler) << 16;
    if (gTasks[taskId].data[4] & 0x100)
        selectedPalettes |= (1 << targetBattler) << 16;
    TintPlttBuffer(selectedPalettes, gTasks[taskId].data[5], gTasks[taskId].data[6], gTasks[taskId].data[7]);
    if (gTasks[taskId].data[0] == gTasks[taskId].data[1])
    {
        UnfadePlttBuffer(selectedPalettes);
        DestroyAnimVisualTask(taskId);
    }
}

static void sub_80BA27C(struct Sprite *sprite)
{
    u16 var0;

    sprite->invisible = TRUE;
    sprite->data[0] = -gBattleAnimArgs[0];
    sprite->data[1] = gBattleAnimArgs[1];
    sprite->data[2] = gBattleAnimArgs[1];
    sprite->data[3] = gBattleAnimArgs[2];

    switch (gBattleAnimArgs[3])
    {
    case 0:
        StoreSpriteCallbackInData6(sprite, (void *)&gBattle_BG3_X);
        break;
    case 1:
        StoreSpriteCallbackInData6(sprite, (void *)&gBattle_BG3_Y);
        break;
    case 2:
        StoreSpriteCallbackInData6(sprite, (void *)&gSpriteCoordOffsetX);
        break;
    default:
        StoreSpriteCallbackInData6(sprite, (void *)&gSpriteCoordOffsetY);
        break;
    }
    sprite->data[4] = *(u16 *)(sprite->data[6] | (sprite->data[7] << 16));
    sprite->data[5] = gBattleAnimArgs[3];
    var0 = sprite->data[5] - 2;
    if (var0 < 2)
        sub_80BA3CC();
    sprite->callback = sub_80BA320;
}

static void sub_80BA320(struct Sprite *sprite)
{
    u8 i;
    u16 var0;

    if (sprite->data[3] > 0)
    {
        --sprite->data[3];
        if (sprite->data[1] > 0)
        {
            --sprite->data[1];
        }
        else
        {
            sprite->data[1] = sprite->data[2];
            *(u16 *)(sprite->data[6] | (sprite->data[7] << 16)) += sprite->data[0];
            sprite->data[0] = -sprite->data[0];
        }
    }
    else
    {
        *(u16 *)(sprite->data[6] | (sprite->data[7] << 16)) = sprite->data[4];
        var0 = sprite->data[5] - 2;
        if (var0 < 2)
            for (i = 0; i < gBattlersCount; ++i)
                gSprites[gBattlerSpriteIds[i]].coordOffsetEnabled = 0;
        DestroyAnimSprite(sprite);
    }
}

static void sub_80BA3CC(void)
{
    gSprites[gBattlerSpriteIds[gBattleAnimAttacker]].coordOffsetEnabled = 0;
    gSprites[gBattlerSpriteIds[gBattleAnimTarget]].coordOffsetEnabled = 0;
    if (gBattleAnimArgs[4] == 2)
    {
        gSprites[gBattlerSpriteIds[gBattleAnimAttacker]].coordOffsetEnabled = 1;
        gSprites[gBattlerSpriteIds[gBattleAnimTarget]].coordOffsetEnabled = 1;
    }
    else
    {
        if (gBattleAnimArgs[4] == 0)
            gSprites[gBattlerSpriteIds[gBattleAnimAttacker]].coordOffsetEnabled = 1;
        else
            gSprites[gBattlerSpriteIds[gBattleAnimTarget]].coordOffsetEnabled = 1;
    }
}

void sub_80BA47C(u8 taskId)
{
    gTasks[taskId].data[0] = gBattleAnimArgs[0];
    gTasks[taskId].data[1] = gBattleAnimArgs[1];
    gTasks[taskId].data[2] = gBattleAnimArgs[2];
    gTasks[taskId].data[3] = gBattleAnimArgs[3];
    gTasks[taskId].data[8] = gBattleAnimArgs[3];
    gBattle_BG3_X = gBattleAnimArgs[0];
    gBattle_BG3_Y = gBattleAnimArgs[1];
    gTasks[taskId].func = sub_80BA4D0;
    gTasks[taskId].func(taskId);
}

static void sub_80BA4D0(u8 taskId)
{
    if (gTasks[taskId].data[3] == 0)
    {
        if (gBattle_BG3_X == gTasks[taskId].data[0])
            gBattle_BG3_X = -gTasks[taskId].data[0];
        else
            gBattle_BG3_X = gTasks[taskId].data[0];

        if (gBattle_BG3_Y == -gTasks[taskId].data[1])
            gBattle_BG3_Y = 0;
        else
            gBattle_BG3_Y = -gTasks[taskId].data[1];

        gTasks[taskId].data[3] = gTasks[taskId].data[8];
        if (--gTasks[taskId].data[2] == 0)
        {
            gBattle_BG3_X = 0;
            gBattle_BG3_Y = 0;
            DestroyAnimVisualTask(taskId);
        }
    }
    else
    {
        --gTasks[taskId].data[3];
    }
}

static void sub_80BA560(struct Sprite *sprite)
{
    StartSpriteAffineAnim(sprite, gBattleAnimArgs[3]);
    if (gBattleAnimArgs[2] == 0)
        InitSpritePosToAnimAttacker(sprite, 1);
    else
        InitSpritePosToAnimTarget(sprite, TRUE);
    sprite->callback = RunStoredCallbackWhenAffineAnimEnds;
    StoreSpriteCallbackInData6(sprite, DestroyAnimSprite);
}

static void sub_80BA5A8(struct Sprite *sprite)
{
    StartSpriteAffineAnim(sprite, gBattleAnimArgs[3]);
    if (gBattleAnimArgs[2] == 0)
        InitSpritePosToAnimAttacker(sprite, 1);
    else
        InitSpritePosToAnimTarget(sprite, TRUE);
    sprite->data[0] = gBattleAnimArgs[4];
    sprite->callback = RunStoredCallbackWhenAffineAnimEnds;
    StoreSpriteCallbackInData6(sprite, sub_80B1D3C);
}

static void sub_80BA5F8(struct Sprite *sprite)
{
    if (GetBattlerSide(gBattleAnimAttacker) != B_SIDE_PLAYER && !IsContest())
        gBattleAnimArgs[1] = -gBattleAnimArgs[1];
    sub_80BA560(sprite);
}

static void sub_80BA630(struct Sprite *sprite)
{
    if (gBattleAnimArgs[1] == -1)
        gBattleAnimArgs[1] = Random() & 3;
    StartSpriteAffineAnim(sprite, gBattleAnimArgs[1]);
    if (gBattleAnimArgs[0] == 0)
        InitSpritePosToAnimAttacker(sprite, 0);
    else
        InitSpritePosToAnimTarget(sprite, FALSE);
    sprite->pos2.x += (Random() % 48) - 24;
    sprite->pos2.y += (Random() % 24) - 12;
    StoreSpriteCallbackInData6(sprite, DestroySpriteAndMatrix);
    sprite->callback = RunStoredCallbackWhenAffineAnimEnds;
}

static void sub_80BA6C8(struct Sprite *sprite)
{
    sprite->data[0] = GetAnimBattlerSpriteId(gBattleAnimArgs[0]);
    sprite->pos1.x = gSprites[sprite->data[0]].pos1.x + gSprites[sprite->data[0]].pos2.x;
    sprite->pos1.y = gSprites[sprite->data[0]].pos1.y + gSprites[sprite->data[0]].pos2.y;
    sprite->pos2.x = gBattleAnimArgs[1];
    sprite->pos2.y = gBattleAnimArgs[2];
    StartSpriteAffineAnim(sprite, gBattleAnimArgs[3]);
    StoreSpriteCallbackInData6(sprite, DestroySpriteAndMatrix);
    sprite->callback = RunStoredCallbackWhenAffineAnimEnds;
}

static void sub_80BA738(struct Sprite *sprite)
{
    if (gBattleAnimArgs[2] == 0)
        InitSpritePosToAnimAttacker(sprite, 1);
    else
        InitSpritePosToAnimTarget(sprite, TRUE);
    sprite->data[0] = gBattleAnimArgs[3];
    StoreSpriteCallbackInData6(sprite, DestroyAnimSprite);
    sprite->callback = WaitAnimForDuration;
}

static void sub_80BA780(struct Sprite *sprite)
{
    StartSpriteAffineAnim(sprite, gBattleAnimArgs[3]);
    if (gBattleAnimArgs[2] == 0)
        InitSpritePosToAnimAttacker(sprite, 1);
    else
        InitSpritePosToAnimTarget(sprite, TRUE);
    sprite->callback = sub_80BA7BC;
}

static void sub_80BA7BC(struct Sprite *sprite)
{
    sprite->invisible ^= 1;
    if (sprite->data[0]++ > 12)
        DestroyAnimSprite(sprite);
}

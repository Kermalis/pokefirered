#include "global.h"
#include "battle_anim.h"
#include "gpu_regs.h"
#include "trig.h"

static void sub_80B3FAC(struct Sprite *sprite);
static void sub_80B407C(struct Sprite *sprite);
static void AnimTranslateWebThread(struct Sprite *sprite);
static void sub_80B41F8(struct Sprite *sprite);
static void sub_80B42C0(struct Sprite *sprite);
static void AnimTranslateStinger(struct Sprite *sprite);
static void AnimMissileArc(struct Sprite *sprite);
static void sub_80B45D8(struct Sprite *sprite);
static void sub_80B41C0(struct Sprite *sprite);
static void sub_80B4274(struct Sprite *sprite);
static void sub_80B42E8(struct Sprite *sprite);
static void sub_80B4344(struct Sprite *sprite);
static void AnimMissileArcStep(struct Sprite *sprite);

static const union AffineAnimCmd gUnknown_83E71E8[] =
{
    AFFINEANIMCMD_FRAME(0x100, 0x100, 30, 0),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E71F8[] =
{
    AFFINEANIMCMD_FRAME(0x100, 0x100, -99, 0),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E7208[] =
{
    AFFINEANIMCMD_FRAME(0x100, 0x100, 94, 0),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd *const gUnknown_83E7218[] =
{
    gUnknown_83E71E8,
    gUnknown_83E71F8,
    gUnknown_83E7208,
};

const struct SpriteTemplate gUnknown_83E7224 =
{
    .tileTag = ANIM_TAG_HORN_HIT_2,
    .paletteTag = ANIM_TAG_HORN_HIT_2,
    .oam = &gOamData_83ACAB8,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E7218,
    .callback = sub_80B3FAC,
};

static const union AffineAnimCmd gUnknown_83E723C[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, -33, 1),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E724C[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, 96, 1),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E725C[] =
{
    AFFINEANIMCMD_FRAME(0x0, 0x0, -96, 1),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd *const gUnknown_83E726C[] =
{
    gUnknown_83E723C,
    gUnknown_83E724C,
    gUnknown_83E725C,
};

const struct SpriteTemplate gUnknown_83E7278 =
{
    .tileTag = ANIM_TAG_NEEDLE,
    .paletteTag = ANIM_TAG_NEEDLE,
    .oam = &gOamData_83ACA30,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E726C,
    .callback = sub_80B407C,
};

const struct SpriteTemplate gWebThreadSpriteTemplate =
{
    .tileTag = ANIM_TAG_WEB_THREAD,
    .paletteTag = ANIM_TAG_WEB_THREAD,
    .oam = &gOamData_83AC9C8,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = AnimTranslateWebThread,
};

const struct SpriteTemplate gUnknown_83E72A8 =
{
    .tileTag = ANIM_TAG_STRING,
    .paletteTag = ANIM_TAG_STRING,
    .oam = &gOamData_83ACA00,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B41F8,
};

static const union AffineAnimCmd gUnknown_83E72C0[] =
{
    AFFINEANIMCMD_FRAME(0x10, 0x10, 0, 0),
    AFFINEANIMCMD_FRAME(0x6, 0x6, 0, 1),
    AFFINEANIMCMD_JUMP(1),
};

static const union AffineAnimCmd *const gUnknown_83E72D8[] =
{
    gUnknown_83E72C0,
};

const struct SpriteTemplate gSpiderWebSpriteTemplate =
{
    .tileTag = ANIM_TAG_SPIDER_WEB,
    .paletteTag = ANIM_TAG_SPIDER_WEB,
    .oam = &gOamData_83ACBC0,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E72D8,
    .callback = sub_80B42C0,
};

const struct SpriteTemplate gLinearStingerSpriteTemplate =
{
    .tileTag = ANIM_TAG_NEEDLE,
    .paletteTag = ANIM_TAG_NEEDLE,
    .oam = &gOamData_83ACA30,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = AnimTranslateStinger,
};

const struct SpriteTemplate gPinMissileSpriteTemplate =
{
    .tileTag = ANIM_TAG_NEEDLE,
    .paletteTag = ANIM_TAG_NEEDLE,
    .oam = &gOamData_83ACA30,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = AnimMissileArc,
};

const struct SpriteTemplate gIcicleSpearSpriteTemplate =
{
    .tileTag = ANIM_TAG_ICICLE_SPEAR,
    .paletteTag = ANIM_TAG_ICICLE_SPEAR,
    .oam = &gOamData_83ACA38,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = AnimMissileArc,
};

static const union AffineAnimCmd gUnknown_83E733C[] =
{
    AFFINEANIMCMD_FRAME(0x10, 0x10, 0, 0),
    AFFINEANIMCMD_FRAME(0x8, 0x8, 0, 18),
    AFFINEANIMCMD_LOOP(0),
    AFFINEANIMCMD_FRAME(0xFFFB, 0xFFFB, 0, 8),
    AFFINEANIMCMD_FRAME(0x5, 0x5, 0, 8),
    AFFINEANIMCMD_LOOP(5),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd *const gUnknown_83E7374[] =
{
    gUnknown_83E733C,
};

const struct SpriteTemplate gUnknown_83E7378 =
{
    .tileTag = ANIM_TAG_CIRCLE_OF_LIGHT,
    .paletteTag = ANIM_TAG_CIRCLE_OF_LIGHT,
    .oam = &gOamData_83ACB60,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E7374,
    .callback = sub_80B45D8,
};

static void sub_80B3FAC(struct Sprite *sprite)
{
    if (IsContest())
    {
        StartSpriteAffineAnim(sprite, 2);
        gBattleAnimArgs[2] = -gBattleAnimArgs[2];
        gBattleAnimArgs[0] = -gBattleAnimArgs[0];
    }
    else if (!GetBattlerSide(gBattleAnimTarget))
    {
        StartSpriteAffineAnim(sprite, 1);
        gBattleAnimArgs[1] = -gBattleAnimArgs[1];
        gBattleAnimArgs[2] = -gBattleAnimArgs[2];
        gBattleAnimArgs[3] = -gBattleAnimArgs[3];
        gBattleAnimArgs[0] = -gBattleAnimArgs[0];
    }
    sprite->pos1.x = GetBattlerSpriteCoord2(gBattleAnimTarget, 2) + gBattleAnimArgs[0];
    sprite->pos1.y = GetBattlerSpriteCoord2(gBattleAnimTarget, 3) + gBattleAnimArgs[1];
    sprite->data[0] = gBattleAnimArgs[4];
    sprite->data[2] = GetBattlerSpriteCoord(gBattleAnimTarget, 2) + gBattleAnimArgs[2];
    sprite->data[4] = GetBattlerSpriteCoord(gBattleAnimTarget, 3) + gBattleAnimArgs[3];
    sprite->callback = StartAnimLinearTranslation;
    StoreSpriteCallbackInData6(sprite, DestroyAnimSprite);
}

static void sub_80B407C(struct Sprite *sprite)
{
    if (IsContest())
    {
        gBattleAnimArgs[0] = -gBattleAnimArgs[0];
        StartSpriteAffineAnim(sprite, 2);
    }
    else if (!GetBattlerSide(gBattleAnimTarget))
    {
        gBattleAnimArgs[1] = -gBattleAnimArgs[1];
        gBattleAnimArgs[0] = -gBattleAnimArgs[0];
    }
    sprite->pos1.x = GetBattlerSpriteCoord2(gBattleAnimTarget, 2) + gBattleAnimArgs[0];
    sprite->pos1.y = GetBattlerSpriteCoord2(gBattleAnimTarget, 3) + gBattleAnimArgs[1];
    sprite->data[0] = gBattleAnimArgs[2];
    sprite->data[2] = GetBattlerSpriteCoord(gBattleAnimTarget, 2);
    sprite->data[4] = GetBattlerSpriteCoord(gBattleAnimTarget, 3);
    sprite->callback = StartAnimLinearTranslation;
    StoreSpriteCallbackInData6(sprite, DestroyAnimSprite);
}

// Creates a single web thread that travels from attacker to target.
// Used by MOVE_STRING_SHOT and MOVE_SPIDER_WEB in their first move phase.
// arg 0: x
// arg 1: y
// arg 2: controls the left-to-right movement
// arg 3: amplitude
// arg 4: if targets both opponents
static void AnimTranslateWebThread(struct Sprite *sprite)
{
    if (IsContest())
        gBattleAnimArgs[2] /= 2;
    InitSpritePosToAnimAttacker(sprite, TRUE);
    sprite->data[0] = gBattleAnimArgs[2];
    sprite->data[1] = sprite->pos1.x;
    sprite->data[3] = sprite->pos1.y;
    if (!gBattleAnimArgs[4])
    {
        sprite->data[2] = GetBattlerSpriteCoord(gBattleAnimTarget, 2);
        sprite->data[4] = GetBattlerSpriteCoord(gBattleAnimTarget, 3);
    }
    else
    {
        SetAverageBattlerPositions(gBattleAnimTarget, 1, &sprite->data[2], &sprite->data[4]);
    }
    sub_8075678(sprite);
    sprite->data[5] = gBattleAnimArgs[3];
    sprite->callback = sub_80B41C0;
}

static void sub_80B41C0(struct Sprite *sprite)
{
    if (AnimTranslateLinear(sprite))
    {
        DestroyAnimSprite(sprite);
        return;
    }
    sprite->pos2.x += Sin(sprite->data[6], sprite->data[5]);
    sprite->data[6] = (sprite->data[6] + 13) & 0xFF;
}

static void sub_80B41F8(struct Sprite *sprite)
{
    SetAverageBattlerPositions(gBattleAnimTarget, 0, &sprite->pos1.x, &sprite->pos1.y);
    if (GetBattlerSide(gBattleAnimAttacker))
        sprite->pos1.x -= gBattleAnimArgs[0];
    else
        sprite->pos1.x += gBattleAnimArgs[0];
    sprite->pos1.y += gBattleAnimArgs[1];
    if (!GetBattlerSide(gBattleAnimTarget))
        sprite->pos1.y += 8;
    sprite->callback = sub_80B4274;
}

static void sub_80B4274(struct Sprite *sprite)
{
    if (++sprite->data[0] == 3)
    {
        sprite->data[0] = 0;
        sprite->invisible ^= 1;
    }
    if (++sprite->data[1] == 51)
    {
        DestroyAnimSprite(sprite);
    }
}

static void sub_80B42C0(struct Sprite *sprite)
{
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(16, 0));
    sprite->data[0] = 16;
    sprite->callback = sub_80B42E8;
}

static void sub_80B42E8(struct Sprite *sprite)
{
    if (sprite->data[2] < 20)
    {
        ++sprite->data[2];
    }
    else if (sprite->data[1]++ & 1)
    {
        --sprite->data[0];
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(sprite->data[0], 16 - sprite->data[0]));

        if (sprite->data[0] == 0)
        {
            sprite->invisible = TRUE;
            sprite->callback = sub_80B4344;
        }
    }
}

static void sub_80B4344(struct Sprite *sprite)
{
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    DestroyAnimSprite(sprite);
}

// Translates a stinger sprite linearly to a destination location. The sprite is
// initially rotated so that it appears to be traveling in a straight line.
// arg 0: initial x pixel offset
// arg 1: initial y pixel offset
// arg 2: target x pixel offset
// arg 3: target y pixel offset
// arg 4: duration
static void AnimTranslateStinger(struct Sprite *sprite)
{
    s16 lVarX, lVarY;
    u16 rot;

    if (IsContest())
    {
        gBattleAnimArgs[2] = -gBattleAnimArgs[2];
    }
    else if (GetBattlerSide(gBattleAnimAttacker))
    {
        gBattleAnimArgs[2] = -gBattleAnimArgs[2];
        gBattleAnimArgs[1] = -gBattleAnimArgs[1];
        gBattleAnimArgs[3] = -gBattleAnimArgs[3];
    }
    if (!IsContest() && GetBattlerSide(gBattleAnimAttacker) == GetBattlerSide(gBattleAnimTarget))
    {
        if (GetBattlerPosition(gBattleAnimTarget) == B_POSITION_PLAYER_LEFT
         || GetBattlerPosition(gBattleAnimTarget) == B_POSITION_OPPONENT_LEFT)
        {
            s16 temp1, temp2;

            temp1 = gBattleAnimArgs[2];
            gBattleAnimArgs[2] = -temp1;

            temp2 = gBattleAnimArgs[0];
            gBattleAnimArgs[0] = -temp2;
        }
    }
    InitSpritePosToAnimAttacker(sprite, 1);
    lVarX = GetBattlerSpriteCoord(gBattleAnimTarget, 2) + gBattleAnimArgs[2];
    lVarY = GetBattlerSpriteCoord(gBattleAnimTarget, 3) + gBattleAnimArgs[3];
    rot = ArcTan2Neg(lVarX - sprite->pos1.x, lVarY - sprite->pos1.y);
    rot += 0xC000;
    TrySetSpriteRotScale(sprite, FALSE, 0x100, 0x100, rot);
    sprite->data[0] = gBattleAnimArgs[4];
    sprite->data[2] = lVarX;
    sprite->data[4] = lVarY;
    sprite->callback = StartAnimLinearTranslation;
    StoreSpriteCallbackInData6(sprite, DestroyAnimSprite);
}

// Rotates sprite and moves it in an arc, so that it appears like a missle or arrow traveling.
// arg 0: initial x pixel offset
// arg 1: initial y pixel offset
// arg 2: target x pixel offset
// arg 3: target y pixel offset
// arg 4: duration
// arg 5: wave amplitude
static void AnimMissileArc(struct Sprite *sprite)
{
    InitSpritePosToAnimAttacker(sprite, 1);
    if (GetBattlerSide(gBattleAnimAttacker))
        gBattleAnimArgs[2] = -gBattleAnimArgs[2];
    sprite->data[0] = gBattleAnimArgs[4];
    sprite->data[2] = GetBattlerSpriteCoord(gBattleAnimTarget, 2) + gBattleAnimArgs[2];
    sprite->data[4] = GetBattlerSpriteCoord(gBattleAnimTarget, 3) + gBattleAnimArgs[3];
    sprite->data[5] = gBattleAnimArgs[5];
    InitAnimArcTranslation(sprite);
    sprite->callback = AnimMissileArcStep;
    sprite->invisible = TRUE;
}

static void AnimMissileArcStep(struct Sprite *sprite)
{
    sprite->invisible = FALSE;

    if (TranslateAnimHorizontalArc(sprite))
    {
        DestroyAnimSprite(sprite);
    }
    else
    {
        s16 tempData[8];
        u16 *data = sprite->data;
        u16 x1 = sprite->pos1.x;
        s16 x2 = sprite->pos2.x;
        u16 y1 = sprite->pos1.y;
        s16 y2 = sprite->pos2.y;
        s32 i;

        for (i = 0; i < 8; ++i)
            tempData[i] = data[i];
        x2 += x1;
        y2 += y1;
        if (!TranslateAnimHorizontalArc(sprite))
        {
            u16 rotation = ArcTan2Neg(sprite->pos1.x + sprite->pos2.x - x2,
                                      sprite->pos1.y + sprite->pos2.y - y2);

            rotation += 0xC000;
            TrySetSpriteRotScale(sprite, FALSE, 0x100, 0x100, rotation);
            for (i = 0; i < 8; ++i)
                data[i] = tempData[i];
        }
    }
}

static void sub_80B45D8(struct Sprite *sprite)
{
    if (gBattleAnimArgs[0] == 0)
    {
        sprite->pos1.x = GetBattlerSpriteCoord(gBattleAnimAttacker, 2);
        sprite->pos1.y = GetBattlerSpriteCoord(gBattleAnimAttacker, 3) + 18;
    }
    else
    {
        sprite->pos1.x = GetBattlerSpriteCoord(gBattleAnimTarget, 2);
        sprite->pos1.y = GetBattlerSpriteCoord(gBattleAnimTarget, 3) + 18;
    }
    StoreSpriteCallbackInData6(sprite, DestroySpriteAndMatrix);
    sprite->callback = RunStoredCallbackWhenAffineAnimEnds;
}

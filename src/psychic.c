#include "global.h"
#include "battle_anim.h"
#include "gpu_regs.h"
#include "palette.h"
#include "sound.h"
#include "scanline_effect.h"
#include "trig.h"
#include "constants/songs.h"

static void sub_80B2ECC(struct Sprite *sprite);
static void sub_80B31D0(struct Sprite *sprite);
static void sub_80B3278(struct Sprite *sprite);
static void sub_80B32F4(struct Sprite *sprite);
static void sub_80B37EC(struct Sprite *sprite);
static void sub_80B3A34(struct Sprite *sprite);
static void sub_80B3E84(struct Sprite *sprite);
static void sub_80B300C(struct Sprite *sprite);
static void sub_80B3044(struct Sprite *sprite);
static void sub_80B30B0(struct Sprite *sprite);
static void sub_80B3168(struct Sprite *sprite);
static void sub_80B3384(struct Sprite *sprite);
static void sub_80B33B8(struct Sprite *sprite);
static void sub_80B3454(u8 taskId);
static void sub_80B34DC(u8 taskId);
static void sub_80B3618(u8 taskId);
static void sub_80B3980(u8 taskId);
static void sub_80B3B78(u8 taskId);
static void sub_80B3D78(u8 taskId);

static const union AffineAnimCmd gUnknown_83E6DDC[] =
{
    AFFINEANIMCMD_FRAME(0x100, 0x100, 0, 0),
    AFFINEANIMCMD_FRAME(0xFFFE, 0xFFFE, -10, 120),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd *const gUnknown_83E6DF4[] =
{
    gUnknown_83E6DDC,
};

const struct SpriteTemplate gUnknown_83E6DF8 =
{
    .tileTag = ANIM_TAG_SPIRAL,
    .paletteTag = ANIM_TAG_SPIRAL,
    .oam = &gOamData_83ACB60,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E6DF4,
    .callback = sub_8075D9C,
};

const struct SpriteTemplate gUnknown_83E6E10 =
{
    .tileTag = ANIM_TAG_GREEN_LIGHT_WALL,
    .paletteTag = ANIM_TAG_GREEN_LIGHT_WALL,
    .oam = &gOamData_83ACB00,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B2ECC,
};

const struct SpriteTemplate gUnknown_83E6E28 =
{
    .tileTag = ANIM_TAG_BLUE_LIGHT_WALL,
    .paletteTag = ANIM_TAG_BLUE_LIGHT_WALL,
    .oam = &gOamData_83ACB00,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B2ECC,
};

const struct SpriteTemplate gUnknown_83E6E40 =
{
    .tileTag = ANIM_TAG_RED_LIGHT_WALL,
    .paletteTag = ANIM_TAG_RED_LIGHT_WALL,
    .oam = &gOamData_83ACB00,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B2ECC,
};

const struct SpriteTemplate gUnknown_83E6E58 =
{
    .tileTag = ANIM_TAG_GRAY_LIGHT_WALL,
    .paletteTag = ANIM_TAG_GRAY_LIGHT_WALL,
    .oam = &gOamData_83ACB00,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B2ECC,
};

const struct SpriteTemplate gUnknown_83E6E70 =
{
    .tileTag = ANIM_TAG_ORANGE_LIGHT_WALL,
    .paletteTag = ANIM_TAG_ORANGE_LIGHT_WALL,
    .oam = &gOamData_83ACB00,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B2ECC,
};

static const union AnimCmd gUnknown_83E6E88[] =
{
    ANIMCMD_FRAME(0, 3),
    ANIMCMD_FRAME(16, 3),
    ANIMCMD_FRAME(32, 3),
    ANIMCMD_FRAME(48, 3),
    ANIMCMD_FRAME(64, 3),
    ANIMCMD_END,
};

static const union AnimCmd *const gUnknown_83E6EA0[] =
{
    gUnknown_83E6E88,
};

const struct SpriteTemplate gUnknown_83E6EA4 =
{
    .tileTag = ANIM_TAG_SPARKLE_4,
    .paletteTag = ANIM_TAG_SPARKLE_4,
    .oam = &gOamData_83AC9D8,
    .anims = gUnknown_83E6EA0,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B31D0,
};

static const union AnimCmd gUnknown_83E6EBC[] =
{
    ANIMCMD_FRAME(0, 5),
    ANIMCMD_FRAME(4, 5),
    ANIMCMD_FRAME(8, 5),
    ANIMCMD_FRAME(12, 5),
    ANIMCMD_END,
};

static const union AnimCmd *const gUnknown_83E6ED0[] =
{
    gUnknown_83E6EBC,
};

const struct SpriteTemplate gUnknown_83E6ED4 =
{
    .tileTag = ANIM_TAG_SPARKLE_3,
    .paletteTag = ANIM_TAG_SPARKLE_3,
    .oam = &gOamData_83AC9D0,
    .anims = gUnknown_83E6ED0,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B31D0,
};

const struct SpriteTemplate gUnknown_83E6EEC =
{
    .tileTag = ANIM_TAG_GOLD_RING,
    .paletteTag = ANIM_TAG_GOLD_RING,
    .oam = &gOamData_83ACA18,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = TranslateAnimSpriteToTargetMonLocation,
};

static const union AnimCmd gUnknown_83E6F04[] =
{
    ANIMCMD_FRAME(8, 60, .hFlip = TRUE),
    ANIMCMD_FRAME(16, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 22, .hFlip = TRUE),
    ANIMCMD_LOOP(0),
    ANIMCMD_FRAME(16, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(0, 5, .hFlip = TRUE),
    ANIMCMD_FRAME(8, 5, .hFlip = TRUE),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(8, 22, .hFlip = TRUE),
    ANIMCMD_FRAME(24, 3, .hFlip = TRUE),
    ANIMCMD_FRAME(32, 3, .hFlip = TRUE),
    ANIMCMD_FRAME(40, 22, .hFlip = TRUE),
    ANIMCMD_END,
};

const union AnimCmd gUnknown_83E6F44[] =
{
    ANIMCMD_FRAME(8, 60),
    ANIMCMD_FRAME(16, 5),
    ANIMCMD_FRAME(8, 5),
    ANIMCMD_FRAME(0, 5),
    ANIMCMD_FRAME(8, 22),
    ANIMCMD_LOOP(0),
    ANIMCMD_FRAME(16, 5),
    ANIMCMD_FRAME(8, 5),
    ANIMCMD_FRAME(0, 5),
    ANIMCMD_FRAME(8, 5),
    ANIMCMD_LOOP(1),
    ANIMCMD_FRAME(8, 22),
    ANIMCMD_FRAME(24, 3),
    ANIMCMD_FRAME(32, 3),
    ANIMCMD_FRAME(40, 22),
    ANIMCMD_END,
};

static const union AnimCmd *const gUnknown_83E6F84[] =
{
    gUnknown_83E6F04,
    gUnknown_83E6F44,
};

const struct SpriteTemplate gUnknown_83E6F8C =
{
    .tileTag = ANIM_TAG_BENT_SPOON,
    .paletteTag = ANIM_TAG_BENT_SPOON,
    .oam = &gOamData_83ACA18,
    .anims = gUnknown_83E6F84,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B3278,
};

static const union AnimCmd gUnknown_83E6FA4[] =
{
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(16, 6),
    ANIMCMD_FRAME(32, 6),
    ANIMCMD_FRAME(48, 6),
    ANIMCMD_FRAME(64, 6),
    ANIMCMD_FRAME(80, 6),
    ANIMCMD_FRAME(96, 18),
    ANIMCMD_END,
};

static const union AnimCmd *const gUnknown_83E6FC4[] =
{
    gUnknown_83E6FA4,
};

static const union AffineAnimCmd gUnknown_83E6FC8[] =
{
    AFFINEANIMCMD_FRAME(0, 0, 4, 4),
    AFFINEANIMCMD_FRAME(0, 0, -4, 8),
    AFFINEANIMCMD_FRAME(0, 0, 4, 4),
    AFFINEANIMCMD_LOOP(2),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd *const gUnknown_83E6FF0[] =
{
    gUnknown_83E6FC8,
};

const struct SpriteTemplate gUnknown_83E6FF4 =
{
    .tileTag = ANIM_TAG_AMNESIA,
    .paletteTag = ANIM_TAG_AMNESIA,
    .oam = &gOamData_83AC9D8,
    .anims = gUnknown_83E6FC4,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B32F4,
};

static const union AffineAnimCmd gUnknown_83E700C[] =
{
    AFFINEANIMCMD_FRAME(-8, 10, 0, 16),
    AFFINEANIMCMD_FRAME(18, -18, 0, 16),
    AFFINEANIMCMD_FRAME(-20, 16, 0, 8),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E702C[] =
{
    AFFINEANIMCMD_FRAME(64, -4, 0, 20),
    AFFINEANIMCMD_FRAME(0, 0, 0, -56),
    AFFINEANIMCMD_END,
};

static const struct SpriteTemplate gUnknown_83E7044 =
{
    .tileTag = ANIM_TAG_HOLLOW_ORB,
    .paletteTag = ANIM_TAG_HOLLOW_ORB,
    .oam = &gOamData_83ACAF0,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

const struct SpriteTemplate gUnknown_83E705C =
{
    .tileTag = 0x280A,
    .paletteTag = 0x280A,
    .oam = &gOamData_83AC9E0,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B37EC,
};

static const union AffineAnimCmd gUnknown_83E7074[] =
{
    AFFINEANIMCMD_FRAME(0xFFF8, 0xFFF8, 0, 8),
    AFFINEANIMCMD_FRAME(0x8, 0x8, 0, 8),
    AFFINEANIMCMD_JUMP(0),
};

static const union AffineAnimCmd gUnknown_83E708C[] =
{
    AFFINEANIMCMD_FRAME(0xF0, 0xF0, 0, 0),
    AFFINEANIMCMD_FRAME(0xFFF8, 0xFFF8, 0, 6),
    AFFINEANIMCMD_FRAME(0x8, 0x8, 0, 8),
    AFFINEANIMCMD_FRAME(0xFFF8, 0xFFF8, 0, 2),
    AFFINEANIMCMD_JUMP(1),
};

static const union AffineAnimCmd gUnknown_83E70B4[] =
{
    AFFINEANIMCMD_FRAME(0xD0, 0xD0, 0, 0),
    AFFINEANIMCMD_FRAME(0xFFF8, 0xFFF8, 0, 4),
    AFFINEANIMCMD_FRAME(0x8, 0x8, 0, 8),
    AFFINEANIMCMD_FRAME(0xFFF8, 0xFFF8, 0, 4),
    AFFINEANIMCMD_JUMP(1),
};

static const union AffineAnimCmd gUnknown_83E70DC[] =
{
    AFFINEANIMCMD_FRAME(0xB0, 0xB0, 0, 0),
    AFFINEANIMCMD_FRAME(0xFFF8, 0xFFF8, 0, 2),
    AFFINEANIMCMD_FRAME(0x8, 0x8, 0, 8),
    AFFINEANIMCMD_FRAME(0xFFF8, 0xFFF8, 0, 6),
    AFFINEANIMCMD_JUMP(1),
};

static const union AffineAnimCmd *const gUnknown_83E7104[] =
{
    gUnknown_83E7074,
    gUnknown_83E708C,
    gUnknown_83E70B4,
    gUnknown_83E70DC,
};

static const struct SpriteTemplate gUnknown_83E7114 =
{
    .tileTag = ANIM_TAG_BLUEGREEN_ORB,
    .paletteTag = ANIM_TAG_BLUEGREEN_ORB,
    .oam = &gOamData_83ACA30,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E7104,
    .callback = sub_80B3A34,
};

static const union AffineAnimCmd gUnknown_83E712C[] =
{
    AFFINEANIMCMD_FRAME(0x20, 0x20, 0, 0),
    AFFINEANIMCMD_FRAME(0x4, 0x4, 0, 120),
    AFFINEANIMCMD_END_ALT(1),
};

static const union AffineAnimCmd *const gUnknown_83E7144[] =
{
    gUnknown_83E712C,
};

const struct SpriteTemplate gUnknown_83E7148 =
{
    .tileTag = ANIM_TAG_WHITE_CIRCLE_OF_LIGHT,
    .paletteTag = ANIM_TAG_WHITE_CIRCLE_OF_LIGHT,
    .oam = &gOamData_83ACBC0,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E7144,
    .callback = sub_8075D9C,
};

static const union AffineAnimCmd gUnknown_83E7160[] =
{
    AFFINEANIMCMD_FRAME(0x20, 0x20, 0, 0),
    AFFINEANIMCMD_FRAME(0x10, 0x10, 0, 17),
    AFFINEANIMCMD_LOOP(0),
    AFFINEANIMCMD_FRAME(0xFFF8, 0xFFF8, 0, 10),
    AFFINEANIMCMD_FRAME(0x8, 0x8, 0, 10),
    AFFINEANIMCMD_LOOP(4),
    AFFINEANIMCMD_LOOP(0),
    AFFINEANIMCMD_FRAME(0xFFF0, 0xFFF0, 0, 5),
    AFFINEANIMCMD_FRAME(0x10, 0x10, 0, 5),
    AFFINEANIMCMD_LOOP(7),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd gUnknown_83E71B8[] =
{
    AFFINEANIMCMD_FRAME(0xFFEC, 0x18, 0, 15),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd *const gUnknown_83E71C8[] =
{
    gUnknown_83E7160,
    gUnknown_83E71B8,
};

const struct SpriteTemplate gUnknown_83E71D0 =
{
    .tileTag = ANIM_TAG_CIRCLE_OF_LIGHT,
    .paletteTag = ANIM_TAG_CIRCLE_OF_LIGHT,
    .oam = &gOamData_83ACBC0,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gUnknown_83E71C8,
    .callback = sub_80B3E84,
};

static void sub_80B2ECC(struct Sprite *sprite)
{
    if (GetBattlerSide(gBattleAnimAttacker) == B_SIDE_PLAYER || IsContest())
    {
        sprite->oam.priority = 2;
        sprite->subpriority = 200;
    }
    if (!IsContest())
    {
        u8 battlerCopy;
        u8 battler = battlerCopy = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        u8 rank = GetBattlerSpriteBGPriorityRank(battler);
        s32 var0 = 1;
        bool8 toBG2 = (rank ^ var0) != 0;

        if (IsBattlerSpriteVisible(battler))
            MoveBattlerSpriteToBG(battler, toBG2);
        battler = BATTLE_PARTNER(battlerCopy);
        if (IsBattlerSpriteVisible(battler))
            MoveBattlerSpriteToBG(battler, toBG2 ^ var0);
    }
    if (!IsContest() && IsDoubleBattle())
    {
        if (GetBattlerSide(gBattleAnimAttacker) == B_SIDE_PLAYER)
        {
            sprite->pos1.x = 72;
            sprite->pos1.y = 80;
        }
        else
        {
            sprite->pos1.x = 176;
            sprite->pos1.y = 40;
        }
    }
    else
    {
        if (GetBattlerSide(gBattleAnimAttacker) != B_SIDE_PLAYER)
            gBattleAnimArgs[0] = -gBattleAnimArgs[0];
        sprite->pos1.x = GetBattlerSpriteCoord(gBattleAnimAttacker, BATTLER_COORD_X) + gBattleAnimArgs[0];
        sprite->pos1.y = GetBattlerSpriteCoord(gBattleAnimAttacker, BATTLER_COORD_Y) + gBattleAnimArgs[1];
    }
    if (IsContest())
        sprite->pos1.y += 9;
    sprite->data[0] = 256 + IndexOfSpritePaletteTag(gBattleAnimArgs[2]) * 16;
    sprite->callback = sub_80B300C;
    sub_80B300C(sprite);
}

static void sub_80B300C(struct Sprite *sprite)
{
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(sprite->data[3], 16 - sprite->data[3]));
    if (sprite->data[3] == 13)
        sprite->callback = sub_80B3044;
    else
        ++sprite->data[3];
}

static void sub_80B3044(struct Sprite *sprite)
{
    u16 color;
    u16 startOffset;
    s32 i;

    if (++sprite->data[1] == 2)
    {
        sprite->data[1] = 0;
        startOffset = sprite->data[0];
        color = gPlttBufferFaded[startOffset + 8];
        for (i = 8; i > 0; --i)
            gPlttBufferFaded[startOffset + i] = gPlttBufferFaded[startOffset + i - 1];
        gPlttBufferFaded[startOffset + 1] = color;
        if (++sprite->data[2] == 16)
            sprite->callback = sub_80B30B0;
    }
}

static void sub_80B30B0(struct Sprite *sprite)
{
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(sprite->data[3], 16 - sprite->data[3]));
    if (--sprite->data[3] == -1)
    {
        if (!IsContest())
        {
            u8 battlerCopy;
            u8 battler = battlerCopy = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);

            if (IsBattlerSpriteVisible(battler))
                gSprites[gBattlerSpriteIds[battler]].invisible = FALSE;
            battler = BATTLE_PARTNER(battlerCopy);
            if (IsBattlerSpriteVisible(battler))
                gSprites[gBattlerSpriteIds[battler]].invisible = FALSE;
        }
        sprite->invisible = TRUE;
        sprite->callback = sub_80B3168;
    }
}

static void sub_80B3168(struct Sprite *sprite)
{
    if (!IsContest())
    {
        u8 battlerCopy;
        u8 battler = battlerCopy = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        u8 rank = GetBattlerSpriteBGPriorityRank(battler);
        s32 var0 = 1;
        bool8 toBG2 = (rank ^ var0) != 0;

        if (IsBattlerSpriteVisible(battler))
            sub_8073128(toBG2);
        battler = battlerCopy ^ 2;
        if (IsBattlerSpriteVisible(battler))
            sub_8073128(toBG2 ^ var0);
    }
    sprite->callback = DestroyAnimSprite;
}

static void sub_80B31D0(struct Sprite *sprite)
{
    if (sprite->data[0] == 0)
    {
        int arg3 = gBattleAnimArgs[3];
        bool8 respectMonPicOffsets = FALSE;
        if (arg3 == 0)
            respectMonPicOffsets = TRUE;
        if (!IsContest() && IsDoubleBattle())
        {
            if (GetBattlerSide(gBattleAnimAttacker) == B_SIDE_PLAYER)
            {
                sprite->pos1.x = 72 - gBattleAnimArgs[0];
                sprite->pos1.y = gBattleAnimArgs[1] + 80;
            }
            else
            {
                sprite->pos1.x = gBattleAnimArgs[0] + 176;
                sprite->pos1.y = gBattleAnimArgs[1] + 40;
            }
        }
        else
        {
            if (gBattleAnimArgs[2] == 0)
                InitSpritePosToAnimAttacker(sprite, respectMonPicOffsets);
            else
                InitSpritePosToAnimTarget(sprite, respectMonPicOffsets);
        }

        ++sprite->data[0];
    }
    else if (sprite->animEnded || sprite->affineAnimEnded)
    {
        DestroySpriteAndMatrix(sprite);
    }
}

static void sub_80B3278(struct Sprite *sprite)
{
    sprite->pos1.x = GetBattlerSpriteCoord(gBattleAnimAttacker, BATTLER_COORD_X_2);
    sprite->pos1.y = GetBattlerSpriteCoord(gBattleAnimAttacker, BATTLER_COORD_Y_PIC_OFFSET);
    if (GetBattlerSide(gBattleAnimAttacker) != B_SIDE_PLAYER)
    {
        StartSpriteAnim(sprite, 1);
        sprite->pos1.x -= 40;
        sprite->pos1.y += 10;
        sprite->data[1] = -1;
    }
    else
    {
        sprite->pos1.x += 40;
        sprite->pos1.y -= 10;
        sprite->data[1] = 1;
    }
    StoreSpriteCallbackInData6(sprite, DestroyAnimSprite);
    sprite->callback = RunStoredCallbackWhenAnimEnds;
}

static void sub_80B32F4(struct Sprite *sprite)
{
    s16 x = GetBattlerSpriteCoordAttr(gBattleAnimAttacker, BATTLER_COORD_ATTR_WIDTH) /  2;
    s16 y = GetBattlerSpriteCoordAttr(gBattleAnimAttacker, BATTLER_COORD_ATTR_HEIGHT) / -2;

    if (GetBattlerSide(gBattleAnimAttacker) == B_SIDE_OPPONENT)
        x = -x;
    sprite->pos1.x = GetBattlerSpriteCoord(gBattleAnimAttacker, 2) + x;
    sprite->pos1.y = GetBattlerSpriteCoord(gBattleAnimAttacker, 3) + y;
    if (sprite->pos1.y < 16)
        sprite->pos1.y = 16;
    StoreSpriteCallbackInData6(sprite, sub_80B3384);
    sprite->callback = RunStoredCallbackWhenAnimEnds;
}

static void sub_80B3384(struct Sprite *sprite)
{
    sprite->oam.affineMode = ST_OAM_AFFINE_NORMAL;
    sprite->affineAnims = gUnknown_83E6FF0;
    sprite->data[0] = 0;
    InitSpriteAffineAnim(sprite);
    sprite->callback = sub_80B33B8;
}

static void sub_80B33B8(struct Sprite *sprite)
{
    switch (sprite->data[0])
    {
    case 0:
        if (sprite->affineAnimEnded)
        {
            FreeOamMatrix(sprite->oam.matrixNum);
            sprite->oam.affineMode = ST_OAM_AFFINE_OFF;
            sprite->data[1] = 18;
            ++sprite->data[0];
        }
        break;
    case 1:
        if (--sprite->data[1] == -1)
            DestroyAnimSprite(sprite);
        break;
    }
}

void sub_80B3418(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    u8 spriteId = GetAnimBattlerSpriteId(ANIM_ATTACKER);

    task->data[0] = spriteId;
    PrepareAffineAnimInTaskData(task, spriteId, gUnknown_83E700C);
    task->func = sub_80B3454;
}

static void sub_80B3454(u8 taskId)
{
    if (!RunAffineAnimFromTaskData(&gTasks[taskId]))
        DestroyAnimVisualTask(taskId);
}

void sub_80B3480(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    u8 spriteId = GetAnimBattlerSpriteId(ANIM_ATTACKER);

    task->data[0] = spriteId;
    task->data[1] = 0;
    task->data[2] = 0;
    task->data[3] = GetBattlerSide(gBattleAnimAttacker) != B_SIDE_PLAYER ? 4 : 8;
    PrepareAffineAnimInTaskData(task, task->data[0], gUnknown_83E702C);
    task->func = sub_80B34DC;
}

static void sub_80B34DC(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    switch (task->data[1])
    {
    case 0:
        RunAffineAnimFromTaskData(task);
        if (++task->data[2] > 19)
            ++task->data[1];
        break;
    case 1:
        if (task->data[3] != 0)
        {
            gSprites[task->data[0]].pos2.y -= 8;
            --task->data[3];
        }
        else
        {
            gSprites[task->data[0]].invisible = TRUE;
            gSprites[task->data[0]].pos1.x = 272;
            ResetSpriteRotScale(task->data[0]);
            DestroyAnimVisualTask(taskId);
        }
        break;
    }
}

void sub_80B3584(u8 taskId)
{
    u16 var0, var1;
    struct Task *task = &gTasks[taskId];

    task->data[3] = 16;
    task->data[4] = 0;
    task->data[13] = GetBattlerSpriteCoord(gBattleAnimAttacker, BATTLER_COORD_X_2);
    task->data[14] = GetBattlerSpriteCoord(gBattleAnimAttacker, BATTLER_COORD_Y_PIC_OFFSET);
    var0 = GetBattlerSpriteCoordAttr(gBattleAnimAttacker, BATTLER_COORD_ATTR_WIDTH) / 3;
    var1 = GetBattlerSpriteCoordAttr(gBattleAnimAttacker, BATTLER_COORD_ATTR_HEIGHT) / 3;
    task->data[12] = var0 > var1 ? var0 : var1;
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(16, 0));
    task->func = sub_80B3618;
}

static void sub_80B3618(u8 taskId)
{
    u16 i;
    u8 spriteId;
    struct Task *task = &gTasks[taskId];

    switch (task->data[0])
    {
    case 0:
        if (++task->data[1] > 8)
        {
            task->data[1] = 0;
            spriteId = CreateSprite(&gUnknown_83E7044, task->data[13], task->data[14], 0);
            task->data[task->data[2] + 8] = spriteId;
            if (spriteId != MAX_SPRITES)
            {
                switch (task->data[2])
                {
                case 0:
                    gSprites[spriteId].pos2.x = task->data[12];
                    gSprites[spriteId].pos2.y = -task->data[12];
                    break;
                case 1:
                    gSprites[spriteId].pos2.x = -task->data[12];
                    gSprites[spriteId].pos2.y = task->data[12];
                    break;
                case 2:
                    gSprites[spriteId].pos2.x = task->data[12];
                    gSprites[spriteId].pos2.y = task->data[12];
                    break;
                case 3:
                    gSprites[spriteId].pos2.x = -task->data[12];
                    gSprites[spriteId].pos2.y = -task->data[12];
                    break;
                }
            }

            if (++task->data[2] == 5)
                ++task->data[0];
        }
        break;
    case 1:
        if (task->data[1] & 1)
            --task->data[3];
        else
            ++task->data[4];
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(task->data[3], task->data[4]));
        if (++task->data[1] == 32)
        {
            for (i = 8; i < 13; ++i)
                if (task->data[i] != 64)
                    DestroySprite(&gSprites[task->data[i]]);
            ++task->data[0];
        }
        break;
    case 2:
        ++task->data[0];
        break;
    case 3:
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        DestroyAnimVisualTask(taskId);
        break;
    }
}

static void sub_80B37A4(struct Sprite *sprite)
{
    if (sprite->data[1] > sprite->data[0] - 10)
        sprite->invisible = sprite->data[1] & 1;
    if (sprite->data[1] == sprite->data[0])
        DestroyAnimSprite(sprite);
    ++sprite->data[1];
}

static void sub_80B37EC(struct Sprite *sprite)
{
    if (gBattleAnimArgs[0] == 0)
    {
        sprite->pos1.x = GetBattlerSpriteCoord(gBattleAnimAttacker, BATTLER_COORD_X_2);
        sprite->pos1.y = GetBattlerSpriteCoord(gBattleAnimAttacker, BATTLER_COORD_Y_PIC_OFFSET);
    }
    sprite->data[0] = gBattleAnimArgs[1];
    sprite->callback = sub_80B37A4;
}

void sub_80B3834(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    if (IsContest())
    {
        if (gBattleAnimArgs[0] == 1)
        {
            task->data[10] = -10;
            task->data[11] = GetBattlerSpriteCoordAttr(gBattleAnimTarget, BATTLER_COORD_ATTR_RIGHT) - 8;
            task->data[12] = GetBattlerSpriteCoordAttr(gBattleAnimTarget, BATTLER_COORD_ATTR_TOP) + 8;
            task->data[13] = GetBattlerSpriteCoordAttr(gBattleAnimAttacker, BATTLER_COORD_ATTR_RIGHT) - 8;
            task->data[14] = GetBattlerSpriteCoordAttr(gBattleAnimAttacker, BATTLER_COORD_ATTR_TOP) + 8;
        }
        else
        {
            task->data[10] = 10;
            task->data[11] = GetBattlerSpriteCoordAttr(gBattleAnimAttacker, BATTLER_COORD_ATTR_LEFT) + 8;
            task->data[12] = GetBattlerSpriteCoordAttr(gBattleAnimAttacker, BATTLER_COORD_ATTR_BOTTOM) - 8;
            task->data[13] = GetBattlerSpriteCoordAttr(gBattleAnimTarget, BATTLER_COORD_ATTR_LEFT) + 8;
            task->data[14] = GetBattlerSpriteCoordAttr(gBattleAnimTarget, BATTLER_COORD_ATTR_BOTTOM) - 8;
        }
    }
    else
    {
        if (gBattleAnimArgs[0] == 1)
        {
            task->data[10] = -10;
            task->data[11] = GetBattlerSpriteCoordAttr(gBattleAnimTarget, BATTLER_COORD_ATTR_LEFT) + 8;
            task->data[12] = GetBattlerSpriteCoordAttr(gBattleAnimTarget, BATTLER_COORD_ATTR_TOP) + 8;
            task->data[13] = GetBattlerSpriteCoordAttr(gBattleAnimAttacker, BATTLER_COORD_ATTR_LEFT) + 8;
            task->data[14] = GetBattlerSpriteCoordAttr(gBattleAnimAttacker, BATTLER_COORD_ATTR_TOP) + 8;
        }
        else
        {
            task->data[10] = 10;
            task->data[11] = GetBattlerSpriteCoordAttr(gBattleAnimAttacker, BATTLER_COORD_ATTR_RIGHT) - 8;
            task->data[12] = GetBattlerSpriteCoordAttr(gBattleAnimAttacker, BATTLER_COORD_ATTR_BOTTOM) - 8;
            task->data[13] = GetBattlerSpriteCoordAttr(gBattleAnimTarget, BATTLER_COORD_ATTR_RIGHT) - 8;
            task->data[14] = GetBattlerSpriteCoordAttr(gBattleAnimTarget, BATTLER_COORD_ATTR_BOTTOM) - 8;
        }
    }
    task->data[1] = 6;
    task->func = sub_80B3980;
}

static void sub_80B3980(u8 taskId)
{
    u8 spriteId;
    struct Task *task = &gTasks[taskId];

    switch (task->data[0])
    {
    case 0:
        if (++task->data[1] > 6)
        {
            task->data[1] = 0;
            spriteId = CreateSprite(&gUnknown_83E7114, task->data[11], task->data[12], 0);
            if (spriteId != 64)
            {
                gSprites[spriteId].data[0] = 16;
                gSprites[spriteId].data[2] = task->data[13];
                gSprites[spriteId].data[4] = task->data[14];
                gSprites[spriteId].data[5] = task->data[10];
                InitAnimArcTranslation(&gSprites[spriteId]);
                StartSpriteAffineAnim(&gSprites[spriteId], task->data[2] & 3);
            }

            if (++task->data[2] == 12)
                ++task->data[0];
        }
        break;
    case 1:
        if (++task->data[1] > 17)
            DestroyAnimVisualTask(taskId);
        break;
    }
}

static void sub_80B3A34(struct Sprite *sprite)
{
    if (TranslateAnimHorizontalArc(sprite))
    {
        FreeOamMatrix(sprite->oam.matrixNum);
        DestroySprite(sprite);
    }
}

void sub_80B3A58(u8 taskId)
{
    s16 i;
    u8 yOffset;
    struct ScanlineEffectParams scanlineParams;
    struct Task *task = &gTasks[taskId];
    
    yOffset = GetBattlerYCoordWithElevation(gBattleAnimTarget);
    task->data[14] = yOffset - 32;
    switch (gBattleAnimArgs[0])
    {
    case 0:
        task->data[11] = 2;
        task->data[12] = 5;
        task->data[13] = 64;
        task->data[15] = yOffset + 32;
        break;
    case 1:
        task->data[11] = 2;
        task->data[12] = 5;
        task->data[13] = 192;
        task->data[15] = yOffset + 32;
        break;
    case 2:
        task->data[11] = 4;
        task->data[12] = 4;
        task->data[13] = 0;
        task->data[15] = yOffset + 32;
        break;
    }
    if (task->data[14] < 0)
        task->data[14] = 0;
    if (GetBattlerSpriteBGPriorityRank(gBattleAnimTarget) == 1)
    {
        task->data[10] = gBattle_BG1_X;
        scanlineParams.dmaDest = &REG_BG1HOFS;
    }
    else
    {
        task->data[10] = gBattle_BG2_X;
        scanlineParams.dmaDest = &REG_BG2HOFS;
    }
    for (i = task->data[14]; i <= task->data[14] + 64; ++i)
    {
        gScanlineEffectRegBuffers[0][i] = task->data[10];
        gScanlineEffectRegBuffers[1][i] = task->data[10];
    }
    scanlineParams.dmaControl = SCANLINE_EFFECT_DMACNT_16BIT;
    scanlineParams.initState = 1;
    scanlineParams.unused9 = 0;
    ScanlineEffect_SetParams(scanlineParams);
    task->func = sub_80B3B78;
}

static void sub_80B3B78(u8 taskId)
{
    s16 sineIndex, i;
    struct Task *task = &gTasks[taskId];

    switch (task->data[0])
    {
    case 0:
        sineIndex = task->data[13];
        for (i = task->data[14]; i <= task->data[15]; ++i)
        {
            s16 var2 = (gSineTable[sineIndex] >> task->data[12]);

            if (var2 > 0)
                var2 += (task->data[1] & 3);
            else if (var2 < 0)
                var2 -= (task->data[1] & 3);
            gScanlineEffectRegBuffers[0][i] = task->data[10] + var2;
            gScanlineEffectRegBuffers[1][i] = task->data[10] + var2;
            sineIndex += task->data[11];
        }
        if (++task->data[1] > 23)
            ++task->data[0];
        break;
    case 1:
        gScanlineEffect.state = 3;
        ++task->data[0];
        break;
    case 2:
        DestroyAnimVisualTask(taskId);
        break;
    }
}

void sub_80B3C78(u8 taskId)
{
    s16 spriteId;
    s16 matrixNum;
    struct Task *task = &gTasks[taskId];
    
    matrixNum = AllocOamMatrix();
    if (matrixNum == 0xFF)
    {
        DestroyAnimVisualTask(taskId);
        return;
    }
    spriteId = CloneBattlerSpriteWithBlend(gBattleAnimArgs[0]);
    if (spriteId < 0)
    {
        FreeOamMatrix(matrixNum);
        DestroyAnimVisualTask(taskId);
        return;
    }
    gSprites[spriteId].callback = SpriteCallbackDummy;
    gSprites[spriteId].oam.affineMode = ST_OAM_AFFINE_DOUBLE;
    gSprites[spriteId].oam.matrixNum = matrixNum;
    gSprites[spriteId].affineAnimPaused = TRUE;
    ++gSprites[spriteId].subpriority;
    SetSpriteRotScale(spriteId, 256, 256, 0);
    CalcCenterToCornerVec(&gSprites[spriteId], gSprites[spriteId].oam.shape, gSprites[spriteId].oam.size, gSprites[spriteId].oam.affineMode);
    task->data[13] = GetAnimBattlerSpriteId(gBattleAnimArgs[0]);
    task->data[14] = matrixNum;
    task->data[15] = spriteId;
    task->func = sub_80B3D78;
}

static void sub_80B3D78(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    switch (task->data[0])
    {
    case 0:
        task->data[1] += 4;
        task->data[2] = 256 - (gSineTable[task->data[1]] >> 1);
        SetSpriteRotScale(task->data[15], task->data[2], task->data[2], 0);
        SetBattlerSpriteYOffsetFromOtherYScale(task->data[15], task->data[13]);
        if (task->data[1] == 48)
            ++task->data[0];
        break;
    case 1:
        task->data[1] -= 4;
        task->data[2] = 256 - (gSineTable[task->data[1]] >> 1);;
        SetSpriteRotScale(task->data[15], task->data[2], task->data[2], 0);
        SetBattlerSpriteYOffsetFromOtherYScale(task->data[15], task->data[13]);
        if (task->data[1] == 0)
            ++task->data[0];
        break;
    case 2:
        obj_delete_but_dont_free_vram(&gSprites[task->data[15]]);
        ++task->data[0];
        break;
    case 3:
        FreeOamMatrix(task->data[14]);
        DestroyAnimVisualTask(taskId);
        break;
    }
}

static void sub_80B3E84(struct Sprite *sprite)
{
    switch (sprite->data[0])
    {
    case 0:
        sprite->pos1.x = GetBattlerSpriteCoord(gBattleAnimAttacker, BATTLER_COORD_X);
        sprite->pos1.y = GetBattlerSpriteCoord(gBattleAnimAttacker, BATTLER_COORD_Y);
        if (IsContest())
            sprite->pos1.y += 12;
        sprite->data[1] = 8;
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_ALL | BLDCNT_EFFECT_BLEND);
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(sprite->data[1], 16 - sprite->data[1]));
        ++sprite->data[0];
        break;
    case 1:
        if (sprite->affineAnimEnded)
        {
            PlaySE12WithPanning(SE_W100, BattleAnimAdjustPanning(-64));
            ChangeSpriteAffineAnim(sprite, 1);
            ++sprite->data[0];
        }
        break;
    case 2:
        if (sprite->data[2]++ > 1)
        {
            sprite->data[2] = 0;
            --sprite->data[1];
            SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(sprite->data[1], 16 - sprite->data[1]));
            if (sprite->data[1] == 0)
            {
                ++sprite->data[0];
                sprite->invisible = TRUE;
            }
        }
        sprite->data[3] += 0x380;
        sprite->pos2.y -= sprite->data[3] >> 8;
        sprite->data[3] &= 0xFF;
        break;
    case 3:
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        DestroyAnimSprite(sprite);
        break;
    }
}

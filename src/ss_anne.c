#include "global.h"
#include "task.h"
#include "sound.h"
#include "field_map_obj.h"
#include "script.h"
#include "constants/songs.h"

// Tasks governing the ship's departure after you've gotten HM01 CUT

#define SPRITE_TAG_WAKE  4000
#define SPRITE_TAG_SMOKE 4001

static void Task_SSAnneInit(u8 taskId);
static void Task_SSAnneRun(u8 taskId);
static void Task_SSAnneFinish(u8 taskId);
static void CreateWakeBehindBoat(void);
static void WakeSpriteCallback(struct Sprite * sprite);
static void CreateSmokeSprite(void);
static void SmokeSpriteCallback(struct Sprite * sprite);

static const u16 sWakeTiles[] = INCBIN_U16("graphics/ss_anne/unk_8479838.4bpp");
static const u16 sSmokeTiles[] = INCBIN_U16("graphics/ss_anne/unk_8479A38.4bpp");

static const struct SpriteSheet sSpriteSheets[] = {
    {(const void *)sWakeTiles, sizeof(sWakeTiles), SPRITE_TAG_WAKE},
    {(const void *)sSmokeTiles, sizeof(sSmokeTiles), SPRITE_TAG_SMOKE},
    {0}
};

static const union AnimCmd sWakeAnim[] = {
    ANIMCMD_FRAME(0, 12),
    ANIMCMD_FRAME(8, 12),
    ANIMCMD_JUMP(0)
};

static const union AnimCmd *const sWakeAnimTable[] = {
    sWakeAnim
};

static const struct OamData sWakeOamData = {
    .shape = ST_OAM_V_RECTANGLE,
    .size = 2
};

static const struct SpriteTemplate sWakeSpriteTemplate = {
    SPRITE_TAG_WAKE,
    0xFFFF,
    &sWakeOamData,
    sWakeAnimTable,
    NULL,
    gDummySpriteAffineAnimTable,
    WakeSpriteCallback
};

static const union AnimCmd sSmokeAnim[] = {
    ANIMCMD_FRAME( 0, 10),
    ANIMCMD_FRAME( 4, 20),
    ANIMCMD_FRAME( 8, 20),
    ANIMCMD_FRAME(12, 30),
    ANIMCMD_END
};

static const union AnimCmd *const sSmokeAnimTable[] = {
    sSmokeAnim
};

static const struct OamData sSmokeOamData = {
    .shape = ST_OAM_SQUARE,
    .size = 1
};

static const struct SpriteTemplate sSmokeSpriteTemplate = {
    SPRITE_TAG_SMOKE,
    0xFFFF,
    &sSmokeOamData,
    sSmokeAnimTable,
    NULL,
    gDummySpriteAffineAnimTable,
    SmokeSpriteCallback
};

void Special_SSAnneDepartureCutscene(void)
{
    u8 taskId;

    PlaySE(SE_KITEKI);
    taskId = CreateTask(Task_SSAnneInit, 8);
    gTasks[taskId].data[0] = 50;
}

static void Task_SSAnneInit(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (--data[0] == 0)
    {
        LoadSpriteSheets(sSpriteSheets);
        CreateWakeBehindBoat();
        gTasks[taskId].func = Task_SSAnneRun;
    }
}

static void Task_SSAnneRun(u8 taskId)
{
    s16 * data = gTasks[taskId].data;
    u8 mapObjectId;
    struct MapObject * boatObject;
    s16 x;

    data[1]++;
    data[2]++;
    if (data[1] == 70)
    {
        data[1] = 0;
        CreateSmokeSprite();
    }
    TryGetFieldObjectIdByLocalIdAndMap(1, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, &mapObjectId);
    boatObject = &gMapObjects[mapObjectId];
    if (gSprites[boatObject->spriteId].pos1.x + gSprites[boatObject->spriteId].pos2.x < -120)
    {
        PlaySE(SE_KITEKI);
        gTasks[taskId].func = Task_SSAnneFinish;
    }
    else
    {
        x = data[2] / 5;
        gSprites[boatObject->spriteId].pos2.x = -x;
    }
}

static void Task_SSAnneFinish(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    if (++data[3] == 40)
    {
        FreeSpriteTilesByTag(SPRITE_TAG_WAKE);
        FreeSpriteTilesByTag(SPRITE_TAG_SMOKE);
        DestroyTask(taskId);
        EnableBothScriptContexts();
    }
}

static void CreateWakeBehindBoat(void)
{
    u8 mapObjectId;
    struct MapObject * boatObject;
    u16 x;
    u8 spriteId;

    TryGetFieldObjectIdByLocalIdAndMap(1, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, &mapObjectId);
    boatObject = &gMapObjects[mapObjectId];
    x = gSprites[boatObject->spriteId].pos1.x + gSprites[boatObject->spriteId].pos2.x + 80;
    spriteId = CreateSprite(&sWakeSpriteTemplate, x, 109, 0xFF);
    gSprites[spriteId].oam.priority = 2;
    gSprites[spriteId].oam.paletteNum = 10;
}

static void WakeSpriteCallback(struct Sprite * sprite)
{
    u8 mapObjectId;
    struct MapObject * boatObject;
    u16 x;

    TryGetFieldObjectIdByLocalIdAndMap(1, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, &mapObjectId);
    boatObject = &gMapObjects[mapObjectId];
    x = gSprites[boatObject->spriteId].pos1.x + gSprites[boatObject->spriteId].pos2.x + 80;
    sprite->pos1.x = x;
    if (sprite->data[0] / 6 < 22)
        sprite->data[0]++;
    sprite->pos2.x = sprite->data[0] / 6;
    if (sprite->pos1.x + sprite->pos2.x < -18)
        DestroySprite(sprite);
}

static void CreateSmokeSprite(void)
{
    u8 mapObjectId;
    struct MapObject * boatObject;
    u16 x;
    u8 spriteId;

    TryGetFieldObjectIdByLocalIdAndMap(1, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, &mapObjectId);
    boatObject = &gMapObjects[mapObjectId];
    x = gSprites[boatObject->spriteId].pos1.x + gSprites[boatObject->spriteId].pos2.x + 49;
    if ((s16)x >= -32)
    {
        spriteId = CreateSprite(&sSmokeSpriteTemplate, x, 78, 8);
        if (spriteId != MAX_SPRITES)
            gSprites[spriteId].oam.paletteNum = 10;
    }
}

static void SmokeSpriteCallback(struct Sprite * sprite)
{
    sprite->data[0]++;
    sprite->pos2.x = sprite->data[0] / 4;
    if (sprite->animEnded)
        DestroySprite(sprite);
}

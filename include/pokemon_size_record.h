#ifndef GUARD_POKEMON_SIZE_RECORD_H
#define GUARD_POKEMON_SIZE_RECORD_H

#include "global.h"

void InitSeedotSizeRecord(void);
void GetSeedotSizeRecordInfo(void);
void CompareSeedotSize(void);

void InitLotadSizeRecord(void);
void GetLotadSizeRecordInfo(void);
void CompareLotadSize(void);

void sub_80A0904(void);
void sub_80A0958(void);

void GiveGiftRibbonToParty(u8 index, u8 ribbonId);

#endif // GUARD_POKEMON_SIZE_RECORD_H

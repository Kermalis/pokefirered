#include "constants/region_map.h"
#include "constants/trainer_classes.h"
#include "constants/songs.h"
#include "constants/region_map.h"
	.include "asm/macros.inc"
	.include "constants/constants.inc"

	.section .rodata

gUnknown_8238E8C:: @ 8238E8C
	.incbin "baserom.gba", 0x238E8C, 0x250

gTrainerFrontAnimsPtrTable:: @ 82390DC
	.incbin "baserom.gba", 0x2390DC, 0x250

gTrainerFrontPicCoords:: @ 823932C
	.incbin "baserom.gba", 0x23932C, 0x250

gTrainerFrontPicTable:: @ 823957C
	.incbin "baserom.gba", 0x23957C, 0x4A0

gTrainerFrontPicPaletteTable:: @ 8239A1C
	.incbin "baserom.gba", 0x239A1C, 0x558

gTrainerBackAnimsPtrTable:: @ 8239F74
	.incbin "baserom.gba", 0x239F74, 0x18

gTrainerBackPicCoords:: @ 8239F8C
	.incbin "baserom.gba", 0x239F8C, 0x18

gTrainerBackPicTable:: @ 8239FA4
	.incbin "baserom.gba", 0x239FA4, 0x30

gTrainerBackPicPaletteTable:: @ 8239FD4
	.incbin "baserom.gba", 0x239FD4, 0x30

gEnemyMonElevation:: @ 823A004
	.incbin "baserom.gba", 0x23A004, 0x4554

gTrainerClassNames:: @ 823E558
	.include "data/text/trainer_class_names.inc"

	.align 2, 0
gTrainers:: @ 823EAD8
	.incbin "baserom.gba", 0x23EAC8, 0x7418

gSpeciesNames:: @ 8245EE0
	.include "data/text/species_names.inc"

gMoveNames:: @ 8247094
	.incbin "baserom.gba", 0x247094, 0xF97

gUnknown_824802B:: @ 824802B
	.incbin "baserom.gba", 0x24802B, 0xD

gUnknown_8248038:: @ 8248038
	.incbin "baserom.gba", 0x248038, 0x186

gUnknown_82481BE:: @ 82481BE
	.incbin "baserom.gba", 0x2481BE, 0x12A

gUnknown_82482E8:: @ 82482E8
	.incbin "baserom.gba", 0x2482E8, 0x18

gUnknown_8248300:: @ 8248300
	.incbin "baserom.gba", 0x248300, 0x18

gUnknown_8248318:: @ 8248318
	.incbin "baserom.gba", 0x248318, 0x8

gUnknown_8248320:: @ 8248320
	.incbin "baserom.gba", 0x248320, 0x10

gUnknown_8248330:: @ 8248330
	.incbin "baserom.gba", 0x248330, 0x6B04

gUnknown_824EE34:: @ 824EE34
	.incbin "baserom.gba", 0x24EE34, 0x190

gUnknown_824EFC4:: @ 824EFC4
	.incbin "baserom.gba", 0x24EFC4, 0x20

gUnknown_824EFE4:: @ 824EFE4
	.incbin "baserom.gba", 0x24EFE4, 0xC

gUnknown_824EFF0:: @ 824EFF0
	.incbin "baserom.gba", 0x24EFF0, 0x18

gUnknown_824F008:: @ 824F008
	.incbin "baserom.gba", 0x24F008, 0x8

gUnknown_824F010:: @ 824F010
	.incbin "baserom.gba", 0x24F010, 0x8

gUnknown_824F018:: @ 824F018
	.incbin "baserom.gba", 0x24F018, 0x8

gUnknown_824F020:: @ 824F020
	.incbin "baserom.gba", 0x24F020, 0x28

gUnknown_824F048:: @ 824F048
	.incbin "baserom.gba", 0x24F048, 0x8

gTypeEffectiveness:: @ 824F050
	.incbin "baserom.gba", 0x24F050, 0x150

gTypeNames:: @ 824F1A0
	.incbin "baserom.gba", 0x24F1A0, 0x80

gTrainerMoneyTable:: @ 824F220
	.incbin "baserom.gba", 0x24F220, 0x8E8

gUnknown_824FB08:: @ 824FB08
	.incbin "baserom.gba", 0x24FB08, 0x138

gUnknown_824FC40:: @ 824FC40
	.incbin "baserom.gba", 0x24FC40, 0x3F8

gUnknown_8250038:: @ 8250038
	.incbin "baserom.gba", 0x250038, 0x38

gUnknown_8250070:: @ 8250070
	.incbin "baserom.gba", 0x250070, 0x24

gStatusConditionString_PoisonJpn:: @ 8250094
	.incbin "baserom.gba", 0x250094, 0x8

gStatusConditionString_SleepJpn:: @ 825009C
	.incbin "baserom.gba", 0x25009C, 0x8

gStatusConditionString_ParalysisJpn:: @ 82500A4
	.incbin "baserom.gba", 0x2500A4, 0x8

gStatusConditionString_BurnJpn:: @ 82500AC
	.incbin "baserom.gba", 0x2500AC, 0x8

gStatusConditionString_IceJpn:: @ 82500B4
	.incbin "baserom.gba", 0x2500B4, 0x8

gStatusConditionString_ConfusionJpn:: @ 82500BC
	.incbin "baserom.gba", 0x2500BC, 0x8

gStatusConditionString_LoveJpn:: @ 82500C4
	.incbin "baserom.gba", 0x2500C4, 0x8

gUnknown_82500CC:: @ 82500CC
	.incbin "baserom.gba", 0x2500CC, 0x38

	.section .rodata.8260270

gUnknown_8260270:: @ 8260270
	.incbin "baserom.gba", 0x260270, 0x8

gUnknown_8260278:: @ 8260278
	.incbin "baserom.gba", 0x260278, 0x30

gUnknown_82602A8:: @ 82602A8
	.incbin "baserom.gba", 0x2602A8, 0x30

gUnknown_82602D8:: @ 82602D8
	.incbin "baserom.gba", 0x2602D8, 0x20

gUnknown_82602F8:: @ 82602F8
	.incbin "baserom.gba", 0x2602F8, 0xCC

gUnknown_82603C4:: @ 82603C4
	.incbin "baserom.gba", 0x2603C4, 0x38

gUnknown_82603FC:: @ 82603FC
	.incbin "baserom.gba", 0x2603FC, 0x8

gUnknown_8260404:: @ 8260404
	.incbin "baserom.gba", 0x260404, 0x68

gUnknown_826046C:: @ 826046C
	.incbin "baserom.gba", 0x26046C, 0x10

gUnknown_826047C:: @ 826047C
	.incbin "baserom.gba", 0x26047C, 0x10

gUnknown_826048C:: @ 826048C
	.incbin "baserom.gba", 0x26048C, 0x10

gUnknown_826049C:: @ 826049C
	.incbin "baserom.gba", 0x26049C, 0x20

gUnknown_82604BC:: @ 82604BC
	.incbin "baserom.gba", 0x2604BC, 0x30

gUnknown_82604EC:: @ 82604EC
	.incbin "baserom.gba", 0x2604EC, 0x30

gUnknown_826051C:: @ 826051C
	.incbin "baserom.gba", 0x26051C, 0x10

gUnknown_826052C:: @ 826052C
	.incbin "baserom.gba", 0x26052C, 0x14

gUnknown_8260540:: @ 8260540
	.incbin "baserom.gba", 0x260540, 0x2

gUnknown_8260542:: @ 8260542
	.incbin "baserom.gba", 0x260542, 0x14

gUnknown_8260556:: @ 8260556
	.incbin "baserom.gba", 0x260556, 0x4

gUnknown_826055A:: @ 826055A
	.incbin "baserom.gba", 0x26055A, 0xA

gUnknown_8260564:: @ 8260564
	.incbin "baserom.gba", 0x260564, 0x8

gUnknown_826056C:: @ 826056C
	.incbin "baserom.gba", 0x26056C, 0x60

gUnknown_82605CC:: @ 82605CC
	.incbin "baserom.gba", 0x2605CC, 0x128

gUnknown_82606F4:: @ 82606F4
	.incbin "baserom.gba", 0x2606F4, 0x140

gUnknown_8260834:: @ 8260834
	.incbin "baserom.gba", 0x260834, 0x1FE

gUnknown_8260A32:: @ 8260A32
	.incbin "baserom.gba", 0x260A32, 0x1FE

gUnknown_8260C30:: @ 8260C30
	.incbin "baserom.gba", 0x260C30, 0x800

gUnknown_8261430:: @ 8261430
	.incbin "baserom.gba", 0x261430, 0x828

gUnknown_8261C58:: @ 8261C58
	.incbin "baserom.gba", 0x261C58, 0x8

gUnknown_8261C60:: @ 8261C60
	.incbin "baserom.gba", 0x261C60, 0x50

gUnknown_8261CB0:: @ 8261CB0
	.incbin "baserom.gba", 0x261CB0, 0x18

gUnknown_8261CC8:: @ 8261CC8
	.incbin "baserom.gba", 0x261CC8, 0x38

gUnknown_8261D00:: @ 8261D00
	.incbin "baserom.gba", 0x261D00, 0x8

gUnknown_8261D08:: @ 8261D08
	.incbin "baserom.gba", 0x261D08, 0x138

gUnknown_8261E40:: @ 8261E40
	.incbin "baserom.gba", 0x261E40, 0x1A

gUnknown_8261E5A:: @ 8261E5A
	.incbin "baserom.gba", 0x261E5A, 0x18

gUnknown_8261E72:: @ 8261E72
	.incbin "baserom.gba", 0x261E72, 0x18

gUnknown_8261E8A:: @ 8261E8A
	.incbin "baserom.gba", 0x261E8A, 0x2C

gUnknown_8261EB6:: @ 8261EB6
	.incbin "baserom.gba", 0x261EB6, 0xB

gText_MaleSymbol4:: @ 8261EC1
	.incbin "baserom.gba", 0x261EC1, 0x2

gText_FemaleSymbol4:: @ 8261EC3
	.incbin "baserom.gba", 0x261EC3, 0x2

gText_GenderlessSymbol:: @ 8261EC5
	.incbin "baserom.gba", 0x261EC5, 0x2

gUnknown_8261EC7:: @ 8261EC7
	.incbin "baserom.gba", 0x261EC7, 0x5

gUnknown_8261ECC:: @ 8261ECC
	.incbin "baserom.gba", 0x261ECC, 0x18

gUnknown_8261EE4:: @ 8261EE4
	.incbin "baserom.gba", 0x261EE4, 0x10

gUnknown_8261EF4:: @ 8261EF4
	.incbin "baserom.gba", 0x261EF4, 0x24

gUnknown_8261F18:: @ 8261F18
	.incbin "baserom.gba", 0x261F18, 0x4

gUnknown_8261F1C:: @ 8261F1C
	.incbin "baserom.gba", 0x261F1C, 0x10

gUnknown_8261F2C:: @ 8261F2C
	.incbin "baserom.gba", 0x261F2C, 0x98

gUnknown_8261FC4:: @ 8261FC4
	.incbin "baserom.gba", 0x261FC4, 0x70

gUnknown_8262034:: @ 8262034
	.incbin "baserom.gba", 0x262034, 0x21

gUnknown_8262055:: @ 8262055
	.incbin "baserom.gba", 0x262055, 0x2027

gUnknown_826407C:: @ 826407C
	.incbin "baserom.gba", 0x26407C, 0x1FA0

gUnknown_08331F60:: @ 826601C
	.incbin "baserom.gba", 0x26601C, 0x1000

gUnknown_826701C:: @ 826701C
	.incbin "baserom.gba", 0x26701C, 0x2840

gUnknown_826985C:: @ 826985C
	.incbin "baserom.gba", 0x26985C, 0x100

gUnknown_826995C:: @ 826995C
	.incbin "baserom.gba", 0x26995C, 0x100

gUnknown_8269A5C:: @ 8269A5C
	.incbin "baserom.gba", 0x269A5C, 0x1000

gUnknown_826AA5C:: @ 826AA5C
	.incbin "baserom.gba", 0x26AA5C, 0x1000

	.align 2
gUnknown_3379A0Bin:: @ 826BA5C
	.incbin "graphics/trade/unknown_3379A0.bin.lz"

gUnknown_826BB5C:: @ 826BB5C
	.incbin "baserom.gba", 0x26BB5C, 0x200

gUnknown_826BD5C:: @ 826BD5C
	.incbin "baserom.gba", 0x26BD5C, 0x200

gUnknown_826BF5C:: @ 826BF5C
	.incbin "baserom.gba", 0x26BF5C, 0x20

gWirelessSignal4bpp:: @ 826BF7C
	.incbin "graphics/trade/wireless_signal.4bpp.lz"

gUnknown_826C60C:: @ 826C60C
	.incbin "baserom.gba", 0x26C60C, 0x7C8

gUnknown_826CDD4:: @ 826CDD4
	.incbin "baserom.gba", 0x26CDD4, 0x8

gUnknown_826CDDC:: @ 826CDDC
	.incbin "baserom.gba", 0x26CDDC, 0x8

gUnknown_826CDE4:: @ 826CDE4
	.incbin "baserom.gba", 0x26CDE4, 0x48

gUnknown_826CE2C:: @ 826CE2C
	.incbin "baserom.gba", 0x26CE2C, 0x8

gUnknown_826CE34:: @ 826CE34
	.incbin "baserom.gba", 0x26CE34, 0x8

gUnknown_826CE3C:: @ 826CE3C
	.incbin "baserom.gba", 0x26CE3C, 0x8

gUnknown_826CE44:: @ 826CE44
	.incbin "baserom.gba", 0x26CE44, 0x38

gUnknown_826CE7C:: @ 826CE7C
	.incbin "baserom.gba", 0x26CE7C, 0x8

gUnknown_826CE84:: @ 826CE84
	.incbin "baserom.gba", 0x26CE84, 0x2C

gUnknown_826CEB0:: @ 826CEB0
	.incbin "baserom.gba", 0x26CEB0, 0x8

gUnknown_826CEB8:: @ 826CEB8
	.incbin "baserom.gba", 0x26CEB8, 0x70

gUnknown_826CF28:: @ 826CF28
	.incbin "baserom.gba", 0x26CF28, 0x8

gUnknown_826CF30:: @ 826CF30
	.incbin "baserom.gba", 0x26CF30, 0x18

gUnknown_826CF48:: @ 826CF48
	.incbin "baserom.gba", 0x26CF48, 0x18

gUnknown_826CF60:: @ 826CF60
	.incbin "baserom.gba", 0x26CF60, 0x28

gUnknown_826CF88:: @ 826CF88
	.incbin "baserom.gba", 0x26CF88, 0x4

gUnknown_826CF8C:: @ 826CF8C
	.incbin "baserom.gba", 0x26CF8C, 0x21C

gUnknown_826D1A8:: @ 826D1A8
	.incbin "baserom.gba", 0x26D1A8, 0x14

gUnknown_826D1BC:: @ 826D1BC
	.incbin "baserom.gba", 0x26D1BC, 0x10

gUnknown_826D1CC:: @ 826D1CC
	.incbin "baserom.gba", 0x26D1CC, 0x8

gUnknown_826D1D4:: @ 826D1D4
	.incbin "baserom.gba", 0x26D1D4, 0x10

gUnknown_826D1E4:: @ 826D1E4
	.incbin "baserom.gba", 0x26D1E4, 0x6C

gUnknown_826D250:: @ 826D250
	.incbin "baserom.gba", 0x26D250, 0x44

gUnknown_826D294:: @ 826D294
	.incbin "baserom.gba", 0x26D294, 0xA

gUnknown_826D29E:: @ 826D29E
	.incbin "baserom.gba", 0x26D29E, 0x12

gUnknown_826D2B0:: @ 826D2B0
	.incbin "baserom.gba", 0x26D2B0, 0x28

gDirectionToVectors:: @ 826D2D8
	.4byte  0,  0
	.4byte  0,  1
	.4byte  0, -1
	.4byte -1,  0
	.4byte  1,  0
	.4byte -1,  1
	.4byte  1,  1
	.4byte -1, -1
	.4byte  1, -1

gUnknown_826D320:: @ 826D320
	.incbin "baserom.gba", 0x26D320, 0x10

gUnknown_826D330:: @ 826D330
	.incbin "baserom.gba", 0x26D330, 0xC

gUnknown_826D33C:: @ 826D33C
	.4byte sub_8058684
	.4byte sub_80586A4
	.4byte sub_80586A8

gUnknown_826D348:: @ 826D348
	.4byte sub_80586C8
	.4byte sub_80586CC
	.4byte sub_80586CC
	.4byte sub_80586CC
	.4byte sub_80586CC
	.4byte sub_80586C8
	.4byte sub_80586C8
	.4byte sub_8058734
	.4byte sub_8058734
	.4byte sub_8058734
	.4byte sub_8058734

gUnknown_826D374:: @ 826D374
	.4byte sub_805874C
	.4byte sub_8058754


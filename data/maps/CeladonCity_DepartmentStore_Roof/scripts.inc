CeladonCity_DepartmentStore_Roof_MapScripts:: @ 816BCCC
	.byte 0

CeladonCity_DepartmentStore_Roof_EventScript_16BCCD:: @ 816BCCD
	special sub_8110AB4
	compare_var_to_value VAR_RESULT, 2
	goto_if_eq EventScript_1A7AE0
	special sub_8112364
	lock
	faceplayer
	call EventScript_16BCF6
	compare_var_to_value VAR_0x4001, 0
	goto_if_eq EventScript_16C00E
	goto EventScript_16BD3E
	end

EventScript_16BCF6:: @ 816BCF6
	setvar VAR_0x4001, 0
	checkitem ITEM_FRESH_WATER, 1
	compare_var_to_value VAR_RESULT, 1
	call_if 1, EventScript_16BD2C
	checkitem ITEM_SODA_POP, 1
	compare_var_to_value VAR_RESULT, 1
	call_if 1, EventScript_16BD32
	checkitem ITEM_LEMONADE, 1
	compare_var_to_value VAR_RESULT, 1
	call_if 1, EventScript_16BD38
	return

EventScript_16BD2C:: @ 816BD2C
	addvar VAR_0x4001, 1
	return

EventScript_16BD32:: @ 816BD32
	addvar VAR_0x4001, 2
	return

EventScript_16BD38:: @ 816BD38
	addvar VAR_0x4001, 4
	return

EventScript_16BD3E:: @ 816BD3E
	msgbox gUnknown_8195D22, MSGBOX_YESNO
	compare_var_to_value VAR_RESULT, 0
	goto_if_eq EventScript_16C00C
	textcolor 3
	message Text_195D5F
	waitmessage
	textcolor 1
	switch VAR_0x4001
	case 1, EventScript_16BDAE
	case 2, EventScript_16BDDA
	case 3, EventScript_16BE06
	case 4, EventScript_16BE3D
	case 5, EventScript_16BE69
	case 6, EventScript_16BEA0
	case 7, EventScript_16BED7
	end

EventScript_16BDAE:: @ 816BDAE
	multichoice 0, 0, 32, 0
	switch VAR_RESULT
	case 0, EventScript_16BF19
	case 1, EventScript_16C00C
	case 127, EventScript_16C00C
	end

EventScript_16BDDA:: @ 816BDDA
	multichoice 0, 0, 33, 0
	switch VAR_RESULT
	case 0, EventScript_16BF3A
	case 1, EventScript_16C00C
	case 127, EventScript_16C00C
	end

EventScript_16BE06:: @ 816BE06
	multichoice 0, 0, 34, 0
	switch VAR_RESULT
	case 0, EventScript_16BF19
	case 1, EventScript_16BF3A
	case 2, EventScript_16C00C
	case 127, EventScript_16C00C
	end

EventScript_16BE3D:: @ 816BE3D
	multichoice 0, 0, 35, 0
	switch VAR_RESULT
	case 0, EventScript_16BF5B
	case 1, EventScript_16C00C
	case 127, EventScript_16C00C
	end

EventScript_16BE69:: @ 816BE69
	multichoice 0, 0, 36, 0
	switch VAR_RESULT
	case 0, EventScript_16BF19
	case 1, EventScript_16BF5B
	case 2, EventScript_16C00C
	case 127, EventScript_16C00C
	end

EventScript_16BEA0:: @ 816BEA0
	multichoice 0, 0, 37, 0
	switch VAR_RESULT
	case 0, EventScript_16BF3A
	case 1, EventScript_16BF5B
	case 2, EventScript_16C00C
	case 127, EventScript_16C00C
	end

EventScript_16BED7:: @ 816BED7
	multichoice 0, 0, 38, 0
	switch VAR_RESULT
	case 0, EventScript_16BF19
	case 1, EventScript_16BF3A
	case 2, EventScript_16BF5B
	case 3, EventScript_16C00C
	case 127, EventScript_16C00C
	end

EventScript_16BF19:: @ 816BF19
	setvar VAR_0x8008, ITEM_FRESH_WATER
	setvar VAR_0x8009, ITEM_TM16
	checkflag FLAG_0x296
	goto_if_eq EventScript_16C018
	msgbox gUnknown_8195D75
	goto EventScript_16BF7C
	end

EventScript_16BF3A:: @ 816BF3A
	setvar VAR_0x8008, ITEM_SODA_POP
	setvar VAR_0x8009, ITEM_TM20
	checkflag FLAG_0x295
	goto_if_eq EventScript_16C018
	msgbox gUnknown_8195E33
	goto EventScript_16BF7C
	end

EventScript_16BF5B:: @ 816BF5B
	setvar VAR_0x8008, ITEM_LEMONADE
	setvar VAR_0x8009, ITEM_TM33
	checkflag FLAG_0x294
	goto_if_eq EventScript_16C018
	msgbox gUnknown_8195EBF
	goto EventScript_16BF7C
	end

EventScript_16BF7C:: @ 816BF7C
	getitemname 0, VAR_0x8008
	getitemname 1, VAR_0x8009
	removeitem VAR_0x8008, 1
	checkitemspace VAR_0x8009, 1
	compare_var_to_value VAR_RESULT, 0
	goto_if_eq EventScript_16C002
	additem VAR_0x8009, 1
	textcolor 3
	playfanfare MUS_FANFA1
	message Text_195DAD
	waitmessage
	waitfanfare
	giveitem VAR_0x8009, 1, 8
	call EventScript_1A6675
	compare_var_to_value VAR_0x8008, ITEM_FRESH_WATER
	call_if 1, EventScript_16BFDE
	compare_var_to_value VAR_0x8008, ITEM_SODA_POP
	call_if 1, EventScript_16BFEA
	compare_var_to_value VAR_0x8008, ITEM_LEMONADE
	call_if 1, EventScript_16BFF6
	release
	end

EventScript_16BFDE:: @ 816BFDE
	setflag FLAG_0x296
	msgbox gUnknown_8195DD4
	return

EventScript_16BFEA:: @ 816BFEA
	setflag FLAG_0x295
	msgbox gUnknown_8195E68
	return

EventScript_16BFF6:: @ 816BFF6
	setflag FLAG_0x294
	msgbox gUnknown_8195EF4
	return

EventScript_16C002:: @ 816C002
	msgbox gUnknown_8195F4F
	release
	end

EventScript_16C00C:: @ 816C00C
	release
	end

EventScript_16C00E:: @ 816C00E
	msgbox gUnknown_8195FEF
	release
	end

EventScript_16C018:: @ 816C018
	msgbox gUnknown_8195F6E
	release
	end

CeladonCity_DepartmentStore_Roof_EventScript_16C022:: @ 816C022
	msgbox gUnknown_8195F98, 2
	end

CeladonCity_DepartmentStore_Roof_EventScript_16C02B:: @ 816C02B
	msgbox gUnknown_8196017, 3
	end

CeladonCity_DepartmentStore_Roof_EventScript_16C034:: @ 816C034
	lockall
	message Text_196038
	waitmessage
	showmoneybox 0, 0, 0
	goto EventScript_16C045
	end

EventScript_16C045:: @ 816C045
	multichoice 12, 0, 26, 0
	copyvar VAR_0x4001, VAR_RESULT
	switch VAR_0x4001
	case 0, EventScript_16C083
	case 1, EventScript_16C094
	case 2, EventScript_16C0A5
	msgbox gUnknown_81960AE
	goto EventScript_16C14D
	end

EventScript_16C083:: @ 816C083
	setvar VAR_0x4000, ITEM_FRESH_WATER
	checkmoney 200, 0
	goto EventScript_16C0CB
	end

EventScript_16C094:: @ 816C094
	setvar VAR_0x4000, ITEM_SODA_POP
	checkmoney 300, 0
	goto EventScript_16C0CB
	end

EventScript_16C0A5:: @ 816C0A5
	setvar VAR_0x4000, ITEM_LEMONADE
	checkmoney 350, 0
	goto EventScript_16C0CB
	end

EventScript_16C0B6:: @ 816C0B6
	takemoney 200, 0
	return

EventScript_16C0BD:: @ 816C0BD
	takemoney 300, 0
	return

EventScript_16C0C4:: @ 816C0C4
	takemoney 350, 0
	return

EventScript_16C0CB:: @ 816C0CB
	compare_var_to_value VAR_RESULT, 0
	goto_if_eq EventScript_16C131
	checkitemspace VAR_0x4000, 1
	compare_var_to_value VAR_RESULT, 0
	goto_if_eq EventScript_16C13F
	compare_var_to_value VAR_0x4001, 0
	call_if 1, EventScript_16C0B6
	compare_var_to_value VAR_0x4001, 1
	call_if 1, EventScript_16C0BD
	compare_var_to_value VAR_0x4001, 2
	call_if 1, EventScript_16C0C4
	updatemoneybox 0, 0, 0
	getitemname 0, VAR_0x4000
	playse SE_JIHANKI
	msgbox gUnknown_8196076
	additem VAR_0x4000, 1
	goto EventScript_16C125
	end

EventScript_16C125:: @ 816C125
	message Text_196038
	waitmessage
	goto EventScript_16C045
	end

EventScript_16C131:: @ 816C131
	msgbox gUnknown_819605E
	goto EventScript_16C14D
	end

EventScript_16C13F:: @ 816C13F
	msgbox gUnknown_819608E
	goto EventScript_16C14D
	end

EventScript_16C14D:: @ 816C14D
	hidemoneybox
	.byte 0
	.byte 0
	releaseall
	end

PokemonMansion_2F_MapScripts:: @ 8162254
	map_script 1, PokemonMansion_2F_MapScript1_16225A
	.byte 0

PokemonMansion_2F_MapScript1_16225A:: @ 816225A
	checkflag FLAG_0x26C
	call_if 1, EventScript_1A7D3E
	end

PokemonMansion_2F_EventScript_162264:: @ 8162264
	lockall
	setvar VAR_0x8004, 1
	call EventScript_1A7AE2
	playse SE_KI_GASYAN
	special DrawWholeMapView
	waitse
	releaseall
	end

PokemonMansion_2F_EventScript_162278:: @ 8162278
	msgbox gUnknown_817751F, 3
	end

PokemonMansion_2F_EventScript_162281:: @ 8162281
	msgbox gUnknown_8177574, 3
	end

PokemonMansion_2F_EventScript_16228A:: @ 816228A
	trainerbattle 0, 216, 0, Text_177498, Text_1774CB
	msgbox gUnknown_81774E3, 6
	end

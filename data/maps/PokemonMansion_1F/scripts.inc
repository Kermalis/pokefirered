PokemonMansion_1F_MapScripts:: @ 81621F9
	map_script 1, PokemonMansion_1F_MapScript1_162204
	map_script 3, PokemonMansion_1F_MapScript2_16220E
	.byte 0

PokemonMansion_1F_MapScript1_162204:: @ 8162204
	checkflag FLAG_0x26C
	call_if 1, EventScript_1A7B7A
	end

PokemonMansion_1F_MapScript2_16220E:: @ 816220E
	setworldmapflag FLAG_WORLD_MAP_POKEMON_MANSION_1F
	end

PokemonMansion_1F_EventScript_162212:: @ 8162212
	lockall
	setvar VAR_0x8004, 0
	call EventScript_1A7AE2
	playse SE_KI_GASYAN
	special DrawWholeMapView
	waitse
	releaseall
	end

PokemonMansion_1F_EventScript_162226:: @ 8162226
	trainerbattle 0, 335, 0, Text_177364, Text_177391
	msgbox gUnknown_8177397, 6
	end

PokemonMansion_1F_EventScript_16223D:: @ 816223D
	trainerbattle 0, 534, 0, Text_1773C6, Text_1773FD
	msgbox gUnknown_8177418, 6
	end

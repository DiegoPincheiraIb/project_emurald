#define TEAM_MON_SPECIES(speciesId) \
    { .overrideMask = TRAINER_TEAM_OVERRIDE_SPECIES, .species = speciesId }

#define TEAM_MON_ITEM(itemId) \
    { .overrideMask = TRAINER_TEAM_OVERRIDE_HELD_ITEM, .heldItem = itemId }

#define TEAM_MON_IV(ivValue) \
    { .overrideMask = TRAINER_TEAM_OVERRIDE_IV, .iv = ivValue }

#define TEAM_MON_EV(evPtr) \
    { .overrideMask = TRAINER_TEAM_OVERRIDE_EVS, .ev = evPtr }

#define TEAM_MON_ABILITY(abilityId) \
    { .overrideMask = TRAINER_TEAM_OVERRIDE_ABILITY, .ability = abilityId }

#define TEAM_MON_NATURE(natureId) \
    { .overrideMask = TRAINER_TEAM_OVERRIDE_NATURE, .nature = natureId }

#define TEAM_MON_MOVES(movesPtr) \
    { .overrideMask = TRAINER_TEAM_OVERRIDE_MOVES, .moves = movesPtr }

#define TEAM_MON_LEVEL(levelValue) \
    { .overrideMask = TRAINER_TEAM_OVERRIDE_LEVEL, .lvl = levelValue }

#define TEAM_MON_FULL(speciesId, itemId, ivValue, evPtr) \
    { \
        .overrideMask = TRAINER_TEAM_OVERRIDE_SPECIES | TRAINER_TEAM_OVERRIDE_HELD_ITEM | TRAINER_TEAM_OVERRIDE_IV | TRAINER_TEAM_OVERRIDE_EVS, \
        .species = speciesId, \
        .heldItem = itemId, \
        .iv = ivValue, \
        .ev = evPtr, \
    }

#define TEAM_MON_FULL_PLUS(speciesId, itemId, ivValue, evPtr, abilityId, natureId, movesPtr, levelValue) \
    { \
        .overrideMask = TRAINER_TEAM_OVERRIDE_SPECIES | TRAINER_TEAM_OVERRIDE_HELD_ITEM | TRAINER_TEAM_OVERRIDE_IV | TRAINER_TEAM_OVERRIDE_EVS \
                      | TRAINER_TEAM_OVERRIDE_ABILITY | TRAINER_TEAM_OVERRIDE_NATURE | TRAINER_TEAM_OVERRIDE_MOVES | TRAINER_TEAM_OVERRIDE_LEVEL, \
        .species = speciesId, \
        .heldItem = itemId, \
        .iv = ivValue, \
        .ev = evPtr, \
        .ability = abilityId, \
        .nature = natureId, \
        .moves = movesPtr, \
        .lvl = levelValue, \
    }

#define TEAM_EV_SPREAD(name, hp, atk, def, spatk, spdef, speed) \
    static const u8 name[6] = { hp, atk, def, spatk, spdef, speed }

#define TEAM_MOVESET(name, move1, move2, move3, move4) \
    static const u16 name[MAX_MON_MOVES] = { move1, move2, move3, move4 }

// Common presets to keep team declarations compact.
#define TEAM_MON_COMP(speciesId, itemId, evPtr, abilityId, natureId, movesPtr, levelValue) \
    TEAM_MON_FULL_PLUS(speciesId, itemId, 31, evPtr, abilityId, natureId, movesPtr, levelValue)

#define TEAM_MON_COMP_IV(speciesId, itemId, ivValue, evPtr, abilityId, natureId, movesPtr, levelValue) \
    TEAM_MON_FULL_PLUS(speciesId, itemId, ivValue, evPtr, abilityId, natureId, movesPtr, levelValue)

TEAM_EV_SPREAD(sTeamPresetEvPhysicalSweeper, 0, 252, 0, 0, 4, 252);
TEAM_EV_SPREAD(sTeamPresetEvSpecialSweeper, 0, 0, 4, 252, 0, 252);
TEAM_EV_SPREAD(sTeamPresetEvPhysicalBulky, 252, 4, 252, 0, 0, 0);
TEAM_EV_SPREAD(sTeamPresetEvSpecialBulky, 252, 0, 4, 0, 252, 0);
TEAM_EV_SPREAD(sTeamPresetEvSupport, 252, 0, 128, 0, 128, 0);

#define TEAM_MON_PRESET_PHYSICAL_SWEEPER(speciesId, itemId, abilityId, movesPtr, levelValue) \
    TEAM_MON_COMP(speciesId, itemId, sTeamPresetEvPhysicalSweeper, abilityId, NATURE_JOLLY, movesPtr, levelValue)

#define TEAM_MON_PRESET_SPECIAL_SWEEPER(speciesId, itemId, abilityId, movesPtr, levelValue) \
    TEAM_MON_COMP(speciesId, itemId, sTeamPresetEvSpecialSweeper, abilityId, NATURE_TIMID, movesPtr, levelValue)

#define TEAM_MON_PRESET_PHYSICAL_BULKY(speciesId, itemId, abilityId, movesPtr, levelValue) \
    TEAM_MON_COMP(speciesId, itemId, sTeamPresetEvPhysicalBulky, abilityId, NATURE_IMPISH, movesPtr, levelValue)

#define TEAM_MON_PRESET_SPECIAL_BULKY(speciesId, itemId, abilityId, movesPtr, levelValue) \
    TEAM_MON_COMP(speciesId, itemId, sTeamPresetEvSpecialBulky, abilityId, NATURE_CALM, movesPtr, levelValue)

#define TEAM_MON_PRESET_SUPPORT(speciesId, itemId, abilityId, movesPtr, levelValue) \
    TEAM_MON_COMP(speciesId, itemId, sTeamPresetEvSupport, abilityId, NATURE_BOLD, movesPtr, levelValue)

TEAM_EV_SPREAD(sRoxanneTeamAEvAtkDef, 4, 252, 252, 0, 0, 0);
TEAM_EV_SPREAD(sRoxanneTeamAEvBulky, 252, 0, 0, 0, 252, 4);
TEAM_EV_SPREAD(sRoxanneTeamBEvSpDef, 252, 0, 4, 0, 252, 0);
TEAM_EV_SPREAD(sRoxanneTeamBEvAtkSpeed, 0, 252, 0, 0, 4, 252);

TEAM_MOVESET(sRoxanneTeamAMovesGeodude, MOVE_ROCK_THROW, MOVE_MUD_SPORT, MOVE_TACKLE, MOVE_NONE);
TEAM_MOVESET(sRoxanneTeamAMovesNosepass, MOVE_ROCK_TOMB, MOVE_HARDEN, MOVE_TACKLE, MOVE_NONE);
TEAM_MOVESET(sRoxanneTeamBMovesNosepass, MOVE_ROCK_TOMB, MOVE_THUNDER_WAVE, MOVE_TACKLE, MOVE_NONE);
TEAM_MOVESET(sRoxanneTeamBMovesGeodude, MOVE_ROCK_THROW, MOVE_DEFENSE_CURL, MOVE_TACKLE, MOVE_NONE);

static const struct TrainerTeamMon sRoxanneTeamA[] =
{
    TEAM_MON_COMP(SPECIES_GEODUDE, ITEM_HARD_STONE, sRoxanneTeamAEvAtkDef, ABILITY_ROCK_HEAD, NATURE_ADAMANT, sRoxanneTeamAMovesGeodude, 15),
    TEAM_MON_COMP_IV(SPECIES_NOSEPASS, ITEM_ORAN_BERRY, 28, sRoxanneTeamAEvBulky, ABILITY_STURDY, NATURE_BOLD, sRoxanneTeamAMovesNosepass, 15),
};

static const struct TrainerTeamMon sRoxanneTeamB[] =
{
    TEAM_MON_COMP(SPECIES_NOSEPASS, ITEM_SITRUS_BERRY, sRoxanneTeamBEvSpDef, ABILITY_MAGNET_PULL, NATURE_CALM, sRoxanneTeamBMovesNosepass, 16),
    TEAM_MON_COMP_IV(SPECIES_GEODUDE, ITEM_CHOICE_BAND, 30, sRoxanneTeamBEvAtkSpeed, ABILITY_ROCK_HEAD, NATURE_JOLLY, sRoxanneTeamBMovesGeodude, 16),
};

static const struct TrainerSpeciesTeam sRoxanneTeams[] =
{
    { sRoxanneTeamA, ARRAY_COUNT(sRoxanneTeamA) },
    { sRoxanneTeamB, ARRAY_COUNT(sRoxanneTeamB) },
};

#undef TEAM_MON_SPECIES
#undef TEAM_MON_ITEM
#undef TEAM_MON_IV
#undef TEAM_MON_EV
#undef TEAM_MON_ABILITY
#undef TEAM_MON_NATURE
#undef TEAM_MON_MOVES
#undef TEAM_MON_LEVEL
#undef TEAM_MON_FULL
#undef TEAM_MON_FULL_PLUS
#undef TEAM_EV_SPREAD
#undef TEAM_MOVESET
#undef TEAM_MON_COMP
#undef TEAM_MON_COMP_IV
#undef TEAM_MON_PRESET_PHYSICAL_SWEEPER
#undef TEAM_MON_PRESET_SPECIAL_SWEEPER
#undef TEAM_MON_PRESET_PHYSICAL_BULKY
#undef TEAM_MON_PRESET_SPECIAL_BULKY
#undef TEAM_MON_PRESET_SUPPORT

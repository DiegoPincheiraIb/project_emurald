#define CLASS_POOL_MON_SPECIES(speciesId) \
    { .overrideMask = TRAINER_TEAM_OVERRIDE_SPECIES, .species = speciesId }

#define CLASS_POOL_MON_FULL(speciesId, itemId, ivValue, evPtr, abilityId, natureId, movesPtr, levelValue) \
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

#define CLASS_POOL_EV_SPREAD(name, hp, atk, def, spatk, spdef, speed) \
    static const u8 name[6] = { hp, atk, def, spatk, spdef, speed }

#define CLASS_POOL_MOVESET(name, move1, move2, move3, move4) \
    static const u16 name[MAX_MON_MOVES] = { move1, move2, move3, move4 }

CLASS_POOL_EV_SPREAD(sHikerEvAtkDef, 4, 252, 252, 0, 0, 0);
CLASS_POOL_EV_SPREAD(sHikerEvBulky, 252, 0, 4, 0, 252, 0);
CLASS_POOL_MOVESET(sHikerMovesGeodude, MOVE_ROCK_THROW, MOVE_TACKLE, MOVE_DEFENSE_CURL, MOVE_NONE);
CLASS_POOL_MOVESET(sHikerMovesOnix, MOVE_ROCK_THROW, MOVE_BIND, MOVE_HARDEN, MOVE_NONE);
CLASS_POOL_MOVESET(sHikerMovesMachop, MOVE_LOW_KICK, MOVE_LEER, MOVE_FOCUS_ENERGY, MOVE_NONE);

static const struct TrainerTeamMon sHikerMonPool[] =
{
    CLASS_POOL_MON_FULL(SPECIES_GEODUDE, ITEM_HARD_STONE, 31, sHikerEvAtkDef, ABILITY_ROCK_HEAD, NATURE_ADAMANT, sHikerMovesGeodude, 16),
    CLASS_POOL_MON_FULL(SPECIES_ONIX, ITEM_ORAN_BERRY, 31, sHikerEvBulky, ABILITY_STURDY, NATURE_IMPISH, sHikerMovesOnix, 16),
    CLASS_POOL_MON_FULL(SPECIES_MACHOP, ITEM_BLACK_BELT, 31, sHikerEvAtkDef, ABILITY_GUTS, NATURE_ADAMANT, sHikerMovesMachop, 16),
};

static const struct TrainerTeamMon sYoungsterMonPool[] =
{
    CLASS_POOL_MON_SPECIES(SPECIES_BIDOOF),
    CLASS_POOL_MON_SPECIES(SPECIES_SMOLIV),
    CLASS_POOL_MON_SPECIES(SPECIES_CHIKORITA),
};

#undef CLASS_POOL_MON_SPECIES
#undef CLASS_POOL_MON_FULL
#undef CLASS_POOL_EV_SPREAD
#undef CLASS_POOL_MOVESET
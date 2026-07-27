#include "global.h"
#include "trainer_class_pools.h"
#include "constants/abilities.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/trainers.h"

enum TrainerTeamMonOverrideMask
{
    TRAINER_TEAM_OVERRIDE_SPECIES = (1 << 0),
    TRAINER_TEAM_OVERRIDE_HELD_ITEM = (1 << 1),
    TRAINER_TEAM_OVERRIDE_IV = (1 << 2),
    TRAINER_TEAM_OVERRIDE_EVS = (1 << 3),
    TRAINER_TEAM_OVERRIDE_ABILITY = (1 << 4),
    TRAINER_TEAM_OVERRIDE_NATURE = (1 << 5),
    TRAINER_TEAM_OVERRIDE_MOVES = (1 << 6),
    TRAINER_TEAM_OVERRIDE_LEVEL = (1 << 7),
    TRAINER_TEAM_OVERRIDE_FIXED_LEVEL = (1 << 8),
};

struct TrainerTeamMon
{
    u16 overrideMask;
    u16 species;
    u16 heldItem;
    u32 iv;
    const u8 *ev;
    enum Ability ability;
    u8 nature;
    const u16 *moves;
    u8 lvl;
    bool8 isLevelFixed;
};

struct TrainerClassMonPool
{
    enum TrainerClassID trainerClass;
    const struct TrainerTeamMon *monPool;
    u32 monPoolCount;
};

struct TrainerSpeciesTeam
{
    const struct TrainerTeamMon *mons;
    u32 monsCount;
};

struct TrainerTeamPool
{
    u16 trainerId;
    const struct TrainerSpeciesTeam *teams;
    u32 teamsCount;
};

#include "data/trainer_class_pools_data.h"
#include "data/trainer_team_pools_data.h"

#define TRAINER_CLASS_MON_POOL(trainerClass, monPool) \
    { trainerClass, monPool, ARRAY_COUNT(monPool) },

#define TRAINER_TEAM_POOL(trainerId, teams) \
    { trainerId, teams, ARRAY_COUNT(teams) },

static const struct TrainerClassMonPool sTrainerClassMonPools[] =
{
#include "data/trainer_class_pools_manager.h"
};

static const struct TrainerTeamPool sTrainerTeamPools[] =
{
#include "data/trainer_team_pools_manager.h"
};

#undef TRAINER_CLASS_MON_POOL
#undef TRAINER_TEAM_POOL

static void ApplyTrainerMonOverrides(const struct TrainerTeamMon *poolMon, struct TrainerMon *partyEntry, u16 *speciesOut)
{
    if (poolMon->overrideMask & TRAINER_TEAM_OVERRIDE_SPECIES)
        *speciesOut = poolMon->species;
    if (poolMon->overrideMask & TRAINER_TEAM_OVERRIDE_HELD_ITEM)
        partyEntry->heldItem = poolMon->heldItem;
    if (poolMon->overrideMask & TRAINER_TEAM_OVERRIDE_IV)
        partyEntry->iv = poolMon->iv;
    if (poolMon->overrideMask & TRAINER_TEAM_OVERRIDE_EVS)
        partyEntry->ev = poolMon->ev;
    if (poolMon->overrideMask & TRAINER_TEAM_OVERRIDE_ABILITY)
        partyEntry->ability = poolMon->ability;
    if (poolMon->overrideMask & TRAINER_TEAM_OVERRIDE_NATURE)
        partyEntry->nature = poolMon->nature;
    if (poolMon->overrideMask & TRAINER_TEAM_OVERRIDE_MOVES)
    {
        u32 moveIndex;

        for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
            partyEntry->moves[moveIndex] = poolMon->moves[moveIndex];
    }
    if (poolMon->overrideMask & TRAINER_TEAM_OVERRIDE_LEVEL)
        partyEntry->lvl = poolMon->lvl;
    if (poolMon->overrideMask & TRAINER_TEAM_OVERRIDE_FIXED_LEVEL)
        partyEntry->isLevelFixed = poolMon->isLevelFixed;
}

// Returns TRUE when a class pool exists and applies one random mon override entry.
// Returns FALSE if no pool exists, arguments are invalid, or the mon is a core member.
bool32 TryApplyTrainerClassPoolMon(enum TrainerClassID trainerClass, u32 randomSeed, struct TrainerMon *partyEntry, u16 *speciesOut)
{
    u32 i;

    if (speciesOut == NULL || partyEntry == NULL)
        return FALSE;

    if (partyEntry->isCoreMember == TRUE)
        return FALSE;

    for (i = 0; i < ARRAY_COUNT(sTrainerClassMonPools); i++)
    {
        if (sTrainerClassMonPools[i].trainerClass == trainerClass)
        {
            const struct TrainerTeamMon *poolMon = &sTrainerClassMonPools[i].monPool[randomSeed % sTrainerClassMonPools[i].monPoolCount];

            // Class pools must at least define a replacement species.
            if (!(poolMon->overrideMask & TRAINER_TEAM_OVERRIDE_SPECIES))
                return FALSE;

            ApplyTrainerMonOverrides(poolMon, partyEntry, speciesOut);
            return TRUE;
        }
    }

    return FALSE;
}

// Returns TRUE and sets *speciesOut to a species from the pool for the given trainer class and slot,
// or FALSE if the trainer class has no pool or the mon is a core member.
bool32 TryGetTrainerClassPoolSpecies(enum TrainerClassID trainerClass, u32 slot, bool32 isCoreMember, u16 *speciesOut)
{
    struct TrainerMon tempMon = { 0 };

    tempMon.isCoreMember = isCoreMember;
    return TryApplyTrainerClassPoolMon(trainerClass, slot, &tempMon, speciesOut);
}

// Returns TRUE when a predefined team exists for this trainer and slot, and applies overrides.
// Returns FALSE if no team pool exists, slot is out of bounds, or arguments are invalid.
bool32 TryApplyTrainerTeamPoolMon(u16 trainerId, u32 teamSeed, u32 slot, struct TrainerMon *partyEntry, u16 *speciesOut)
{
    u32 i;

    if (speciesOut == NULL || partyEntry == NULL)
        return FALSE;

    if (partyEntry->isCoreMember == TRUE)
        return FALSE;

    for (i = 0; i < ARRAY_COUNT(sTrainerTeamPools); i++)
    {
        if (sTrainerTeamPools[i].trainerId == trainerId)
        {
            const struct TrainerSpeciesTeam *team = &sTrainerTeamPools[i].teams[teamSeed % sTrainerTeamPools[i].teamsCount];
            const struct TrainerTeamMon *teamMon;

            if (slot >= team->monsCount)
                return FALSE;

            teamMon = &team->mons[slot];

            ApplyTrainerMonOverrides(teamMon, partyEntry, speciesOut);

            return TRUE;
        }
    }

    return FALSE;
}
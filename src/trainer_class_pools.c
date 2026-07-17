#include "global.h"
#include "trainer_class_pools.h"
#include "constants/species.h"
#include "constants/trainers.h"

struct TrainerClassSpeciesPool
{
    enum TrainerClassID trainerClass;
    const u16 *speciesPool;
    u32 speciesPoolCount;
};

#include "data/trainer_class_pools_data.h"

#define TRAINER_CLASS_SPECIES_POOL(trainerClass, speciesPool) \
    { trainerClass, speciesPool, ARRAY_COUNT(speciesPool) },

static const struct TrainerClassSpeciesPool sTrainerClassSpeciesPools[] =
{
#include "data/trainer_class_pools_manager.h"
};

#undef TRAINER_CLASS_SPECIES_POOL

// Returns TRUE and sets *speciesOut to a species from the pool for the given trainer class and slot,
// or FALSE if the trainer class has no pool.
bool32 TryGetTrainerClassPoolSpecies(enum TrainerClassID trainerClass, u32 slot, u16 *speciesOut)
{
    u32 i;

    if (speciesOut == NULL)
        return FALSE;

    for (i = 0; i < ARRAY_COUNT(sTrainerClassSpeciesPools); i++)
    {
        if (sTrainerClassSpeciesPools[i].trainerClass == trainerClass)
        {
            *speciesOut = sTrainerClassSpeciesPools[i].speciesPool[slot % sTrainerClassSpeciesPools[i].speciesPoolCount];
            return TRUE;
        }
    }

    return FALSE;
}
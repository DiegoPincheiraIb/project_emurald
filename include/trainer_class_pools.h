#ifndef GUARD_TRAINER_CLASS_POOLS_H
#define GUARD_TRAINER_CLASS_POOLS_H

#include "global.h"
#include "data.h"

bool32 TryApplyTrainerClassPoolMon(enum TrainerClassID trainerClass, u32 randomSeed, struct TrainerMon *partyEntry, u16 *speciesOut);
bool32 TryGetTrainerClassPoolSpecies(enum TrainerClassID trainerClass, u32 slot, bool32 isCoreMember, u16 *speciesOut);
bool32 TryApplyTrainerTeamPoolMon(u16 trainerId, u32 teamSeed, u32 slot, struct TrainerMon *partyEntry, u16 *speciesOut);

#endif // GUARD_TRAINER_CLASS_POOLS_H

// copyright @¹ÎÁö

#pragma once

#include "ForestMagus.h"

UENUM(BlueprintType)
enum class EFMPlayerState : uint8
{
	None,
	Attacking,
	Teleportation,
	Death
};
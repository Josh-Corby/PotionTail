#pragma once

#include "ObjectiveType.generated.h"

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{
	None		UMETA(DisplayName = "None"),
	Collect		UMETA(DisplayName = "Collect"),
	Return		UMETA(DisplayName = "Return"),
	Location	UMETA(DisplayName = "Location")
};
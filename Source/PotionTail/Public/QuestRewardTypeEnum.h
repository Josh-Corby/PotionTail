#pragma once

#include "QuestRewardTypeEnum.generated.h"

UENUM(BlueprintType)
enum class EQuestRewardType : uint8
{
	Item		UMETA(DisplayName = "Item"),
	Recipe		UMETA(DisplayName = "Recipe"),
	Other		UMETA(DisplayName = "Other")
};

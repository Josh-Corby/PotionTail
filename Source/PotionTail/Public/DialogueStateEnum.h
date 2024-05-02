#pragma once

#include "DialogueStateEnum.generated.h"

UENUM(BlueprintType)
enum class EDialogueState : uint8
{
	PassThrough		UMETA(DisplayName = "PassThrough"),
	Updated			UMETA(DisplayName = "Updated")
};

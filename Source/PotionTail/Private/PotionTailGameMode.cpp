// Copyright Epic Games, Inc. All Rights Reserved.

#include "PotionTailGameMode.h"
#include "PotionTailCharacter.h"
#include "UObject/ConstructorHelpers.h"

APotionTailGameMode::APotionTailGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

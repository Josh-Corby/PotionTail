// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestRewardTypeEnum.h"
#include "QuestRewardsStruct.generated.h"

USTRUCT(BlueprintType)
struct POTIONTAIL_API FQuestReward
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EQuestRewardType Type;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	struct FDataTableRowHandle ItemDataHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Amount;

	FQuestReward();
	~FQuestReward();
};

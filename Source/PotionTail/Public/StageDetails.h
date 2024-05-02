#pragma once

#include "CoreMinimal.h"
#include "ObjectiveDetails.h"
#include "QuestRewardsStruct.h"
#include "StageDetails.generated.h"

USTRUCT(BlueprintType)
struct POTIONTAIL_API FStageDetails
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FObjectiveDetails> Objectives;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FQuestReward> OtherRewards;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MoneyReward;

	FStageDetails();
	~FStageDetails();
};

#pragma once

#include "CoreMinimal.h"
#include "StageDetails.h"
#include "Engine/DataTable.h"

#include "QuestDetails.generated.h"

USTRUCT(BlueprintType)
struct POTIONTAIL_API FQuestDetails : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText TrackingDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsMainQuest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bAutoComplete;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FStageDetails> Stages;

	FQuestDetails();
	~FQuestDetails();
};

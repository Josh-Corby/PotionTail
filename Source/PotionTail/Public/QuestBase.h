#pragma once

#include "CoreMinimal.h"
#include "QuestDetails.h"
#include "Containers/Map.h"
#include "QuestRewardsStruct.h"
#include "QuestRewardTypeEnum.h"
#include "QuestBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectiveUpdated, FName, ObjectiveID, int, NewProgress);

UCLASS(BlueprintType)
class POTIONTAIL_API UQuestBase : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	FName ID;

	UPROPERTY(BlueprintReadOnly)
	int CurrentStageIndex = 0;

	UPROPERTY(BlueprintReadOnly)
	FQuestDetails Details;

	UPROPERTY(BlueprintReadOnly)
	FStageDetails CurrentStageDetails;

	UPROPERTY(BlueprintReadOnly)
	TMap<FName, int> ObjectiveProgress;

	UPROPERTY(BlueprintReadOnly)
	bool bIsComplete;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnObjectiveUpdated OnObjectiveUpdated;

public:

	void InitQuestBase(FQuestDetails InDetails);

	void BindToPlayerObjectiveIDHeardDelegate(UWorld* InWorld);

	void FindItemsAlreadyInPlayerInventory(class UInventoryComponent* PlayerInventory);

	UFUNCTION()
	void OnObjectiveIDHeard(FName InID, int InAmount);

	UFUNCTION(BlueprintPure)
	FObjectiveDetails GetObjectiveDataByID(FName InID) const;

	template<typename RewardType>
	TArray<RewardType> GetRewardsOfType(EQuestRewardType InType) const;

	UFUNCTION(BlueprintPure)
	int GetMoneyReward() const;

	void IsObjectiveComplete(FName InID);

	bool AreObjectivesComplete() const;

	UQuestBase();

	~UQuestBase();
};

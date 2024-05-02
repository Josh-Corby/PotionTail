#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestRewardsStruct.h"
#include "QuestLogComponent.generated.h"

class UQuestBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestCompleted, UQuestBase*, CompletedQuest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRewardGiven, TArray<FQuestReward>, ItemRewards);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRecipeRewardGiven, TArray<FDataTableRowHandle>, RecipeData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoneyRewardGiven, int, MoneyReward);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestTracked);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTIONTAIL_API UQuestLogComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, UQuestBase*> CurrentActiveQuests;

	UPROPERTY(BlueprintReadOnly)
	FName CurrentTrackedQuest;

	UPROPERTY(BlueprintReadOnly)
	TMap<FName, UQuestBase*> CompletedQuests;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnQuestCompleted OnQuestCompleted;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnItemRewardGiven OnItemRewardGiven;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnRecipeRewardGiven OnRecipeRewardGiven;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnMoneyRewardGiven OnMoneyRewardGiven;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnQuestTracked OnQuestTracked;

public:

	// Sets default values for this component's properties
	UQuestLogComponent();

	void CompleteQuest(FName InQuestID);

	UFUNCTION(BlueprintPure)
	bool QueryActiveQuest(FName InQuestID) const;

	UFUNCTION(BlueprintPure)
	bool QueryCompletedQuest(FName InQuestID) const;

	UFUNCTION(BlueprintCallable)
	void TrackQuest();

	UFUNCTION(BlueprintCallable)
	class UQuestBase* AddNewQuest(struct FDataTableRowHandle InQuestData);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	const UQuestBase* GetActiveQuestFromID(FName InQuestID) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	bool bIsQuestBeingCreated;

};
#include "QuestLogComponent.h"
#include "Engine/DataTable.h"
#include "QuestDetails.h"
#include "QuestRewardsStruct.h"
#include "QuestBase.h"
#include "InventoryComponent.h"
#include "RecipeStruct.h"
#include "QuestRewardTypeEnum.h"

// Sets default values for this component's properties
UQuestLogComponent::UQuestLogComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UQuestLogComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


UQuestBase* UQuestLogComponent::AddNewQuest(FDataTableRowHandle InQuestData)
{
	if (!InQuestData.IsNull())
	{
		TObjectPtr<const UDataTable> QuestTable = InQuestData.DataTable;

		FName RowName = InQuestData.RowName;

		const UScriptStruct* RowStruct = QuestTable->GetRowStruct();

		if (RowStruct)
		{
			FQuestDetails* RowData = QuestTable->FindRow<FQuestDetails>(RowName, "FoundQuest");

			if (RowData)
			{
				UQuestBase* newQuest = NewObject<UQuestBase>();
				newQuest->InitQuestBase(*RowData);
				newQuest->BindToPlayerObjectiveIDHeardDelegate(GetWorld());
				newQuest->FindItemsAlreadyInPlayerInventory(GetOwner()->GetComponentByClass<UInventoryComponent>());

				UE_LOG(LogTemp, Warning, TEXT("%s"), *newQuest->ID.ToString());
				CurrentActiveQuests.Add(RowName, newQuest);
				return newQuest;
			}
		}	

		UE_LOG(LogTemp, Warning, TEXT("Quest data table row not found"));
		return nullptr;
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Quest id is not valid"));
		return nullptr;
	}
}

const UQuestBase* UQuestLogComponent::GetActiveQuestFromID(FName InQuestID) const
{
	const UQuestBase* foundQuest = *CurrentActiveQuests.Find(InQuestID);
	if (foundQuest)
	{
		return foundQuest;
	}

	return nullptr;
}

void UQuestLogComponent::CompleteQuest(FName InQuestID)
{
	UQuestBase* completedQuest = *CurrentActiveQuests.Find(InQuestID);
	CurrentActiveQuests.Remove(InQuestID);
	CompletedQuests.Add(InQuestID, completedQuest);

	TArray<FQuestReward> itemRewards = completedQuest->GetRewardsOfType<FQuestReward>(EQuestRewardType::Item);
	OnItemRewardGiven.Broadcast(itemRewards);

	TArray<FDataTableRowHandle> recipeRewards = completedQuest->GetRewardsOfType<FDataTableRowHandle>(EQuestRewardType::Recipe);
	OnRecipeRewardGiven.Broadcast(recipeRewards);

	int moneyReward = completedQuest->GetMoneyReward();
	OnMoneyRewardGiven.Broadcast(moneyReward);

	OnQuestCompleted.Broadcast(completedQuest);
}

void UQuestLogComponent::TrackQuest()
{
	OnQuestTracked.Broadcast();
}

bool UQuestLogComponent::QueryActiveQuest(FName InQuestID) const
{
	if (CurrentActiveQuests.IsEmpty())
	{
		return false;
	}

	return CurrentActiveQuests.Contains(InQuestID);
}

bool UQuestLogComponent::QueryCompletedQuest(FName InQuestID) const
{
	return CompletedQuests.Contains(InQuestID);
}

#include "QuestBase.h"
#include "PotionTailCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "QuestDetails.h"
#include "RecipeStruct.h"
#include "QuestRewardsStruct.h"
#include "ObjectiveType.h"
#include "InventoryComponent.h"

UQuestBase::UQuestBase()
{
	
}

UQuestBase::~UQuestBase()
{
}

void UQuestBase::InitQuestBase(FQuestDetails InDetails)
{
	Details = InDetails;
	ID = FName(InDetails.Name.ToString());
	CurrentStageDetails = Details.Stages[0];
	TArray<FObjectiveDetails> InitialObjectives = CurrentStageDetails.Objectives;
	ObjectiveProgress.Empty();

	for (int i = 0; i < InitialObjectives.Num(); i++)
	{
		FName ObjectiveName = FName(InitialObjectives[i].Name.ToString());
		ObjectiveProgress.Add(ObjectiveName, 0);
	}
}

void UQuestBase::BindToPlayerObjectiveIDHeardDelegate(UWorld* InWorld)
{
	APotionTailCharacter* PlayerCharacter = Cast<APotionTailCharacter>(UGameplayStatics::GetPlayerCharacter(InWorld, 0));

	if (PlayerCharacter)
	{
		PlayerCharacter->OnIDCalled.AddDynamic(this, &UQuestBase::OnObjectiveIDHeard);
	}
}

void UQuestBase::FindItemsAlreadyInPlayerInventory(UInventoryComponent* PlayerInventory)
{
	TArray<FObjectiveDetails> InitialObjectives = CurrentStageDetails.Objectives;
	for (int i = 0; i < InitialObjectives.Num(); i++)
	{
		if (InitialObjectives[i].Type == EObjectiveType::Collect || InitialObjectives[i].Type == EObjectiveType::Return)
		{
			FName rowID = InitialObjectives[i].DataHandle.RowName;
			int amountAlreadyInInventory = PlayerInventory->QueryInventory(rowID);
			OnObjectiveIDHeard(rowID, amountAlreadyInInventory);
		}
	}

	bIsComplete = AreObjectivesComplete();
}

void UQuestBase::OnObjectiveIDHeard(FName InID, int InAmount = 1)
{
	if (ObjectiveProgress.Find(InID))
	{
		int currentProgress = *ObjectiveProgress.Find(InID);
		int newProgress = currentProgress + InAmount;
		ObjectiveProgress.Add(InID, newProgress);
		OnObjectiveUpdated.Broadcast(InID, newProgress);
		IsObjectiveComplete(InID);
	}
}

template<typename RewardType>
TArray<RewardType> UQuestBase::GetRewardsOfType(EQuestRewardType inType) const
{
	TArray<RewardType> foundRewards;
	return foundRewards;
}

// for inventory item rewards at the moment
template<>
TArray<FQuestReward>UQuestBase::GetRewardsOfType<FQuestReward>(EQuestRewardType inType) const
{
	TArray<FQuestReward> foundRewards;
	for (int i = 0; i < Details.Stages.Num(); i++)
	{
		TArray<FQuestReward> rewards = Details.Stages[i].OtherRewards;
		for (int j = 0; j < rewards.Num(); j++)
		{
			FQuestReward reward = rewards[j];

			if (reward.Type != inType)
			{
				continue;
			}

			foundRewards.Add(reward);
		}
	}

	return foundRewards;
}

// for inventory recipe rewards
template<>
TArray<FDataTableRowHandle>UQuestBase::GetRewardsOfType<FDataTableRowHandle>(EQuestRewardType inType) const
{
	TArray<FDataTableRowHandle> foundRewards;
	for (int i = 0; i < Details.Stages.Num(); i++)
	{
		TArray<FQuestReward> rewards = Details.Stages[i].OtherRewards;
		for (int j = 0; j < rewards.Num(); j++)
		{
			FQuestReward reward = rewards[j];

			if (reward.Type != inType)
			{
				continue;
			}

			foundRewards.Add(reward.ItemDataHandle);
		}
	}

	return foundRewards;
}

FObjectiveDetails UQuestBase::GetObjectiveDataByID(FName InID) const
{
	for (int i = 0; i < CurrentStageDetails.Objectives.Num(); i++)
	{

		if (InID == CurrentStageDetails.Objectives[i].DataHandle.RowName)
		{
			return CurrentStageDetails.Objectives[i];
		}
	}

	return FObjectiveDetails();
}

int UQuestBase::GetMoneyReward() const
{
	int totalMoneyReward = 0;
	for (int i = 0; i < Details.Stages.Num(); i++)
	{
		totalMoneyReward += Details.Stages[i].MoneyReward;
	}

	return totalMoneyReward;
}

void UQuestBase::IsObjectiveComplete(FName InID)
{
	FObjectiveDetails desiredDetails = GetObjectiveDataByID(InID);

	int currentProgress = *ObjectiveProgress.Find(InID);

	if (currentProgress >= desiredDetails.Quantity)
	{
		bIsComplete = AreObjectivesComplete();
	}
}

bool UQuestBase::AreObjectivesComplete() const
{
	for (int i = 0; i < CurrentStageDetails.Objectives.Num(); i++)
	{
		FObjectiveDetails details = CurrentStageDetails.Objectives[i];

		int requiredProgress = details.Quantity;
		int currentProgress = *ObjectiveProgress.Find(details.DataHandle.RowName);

		if (currentProgress < requiredProgress && !details.bIsOptional)
		{
			return false;
		}
	}

	return true;
}

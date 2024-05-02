#include "QuestGiverComponent.h"
#include "QuestLogComponent.h"
#include "QuestDetails.h"
#include "QuestBase.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UQuestGiverComponent::UQuestGiverComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UQuestGiverComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UQuestGiverComponent::OnInteract(AActor* InActor)
{
	if(const AActor* playerActor = InActor)
	{
		if (UQuestLogComponent* playerQuestLog = playerActor->GetComponentByClass<UQuestLogComponent>())
		{
			if (!QuestData.IsNull())
			{
				const FName questID = QuestData.RowName;

				if (playerQuestLog->QueryCompletedQuest(questID))
				{
					DisplayQuestAlreadyCompleted();
				}

				else if (playerQuestLog->QueryActiveQuest(questID))
				{
					const UQuestBase* ActiveQuest = playerQuestLog->GetActiveQuestFromID(questID);
					if (ActiveQuest->bIsComplete)
					{
						DisplayQuestReadyToComplete();
						playerQuestLog->CompleteQuest(questID);
					}

					else
					{
						DisplayQuestInProgress();
					}
				}			

				else
				{
					DisplayGiveQuest();
				}
			}
		}
	}

}

void UQuestGiverComponent::DisplayGiveQuest_Implementation()
{
}

void UQuestGiverComponent::DisplayQuestInProgress_Implementation()
{
}

void UQuestGiverComponent::DisplayQuestReadyToComplete_Implementation()
{
}

void UQuestGiverComponent::DisplayQuestAlreadyCompleted_Implementation()
{
}
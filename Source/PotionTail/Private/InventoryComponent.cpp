#include "InventoryComponent.h"
#include "PotionTailCharacter.h"
#include "QuestLogComponent.h"
#include "QuestBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OwningPlayer = Cast<APotionTailCharacter>(GetOwner());
	UQuestLogComponent* playerQuestLog = OwningPlayer->GetQuestLog();

	playerQuestLog->OnItemRewardGiven.AddDynamic(this, &UInventoryComponent::AddQuestRewards);
	playerQuestLog->OnMoneyRewardGiven.AddDynamic(this, &UInventoryComponent::GiveMoney);
}


void UInventoryComponent::AddToInventory(FName InID, int InAmount)
{
	int newTotal = InAmount;
	int* foundAmountPtr = InventoryContents.Find(InID);

	if (foundAmountPtr)
	{
		newTotal += *foundAmountPtr;
	}

	InventoryContents.Add(InID, newTotal);
	OwningPlayer->OnIDCalled.Broadcast(InID, InAmount);
	OnInventoryUpdated.Broadcast(InID, newTotal);
}

int UInventoryComponent::QueryInventory(FName InID)
{
	int* foundAmountPtr = InventoryContents.Find(InID);
	if (foundAmountPtr)
	{
		return *foundAmountPtr;
	}

	return 0;
}

void UInventoryComponent::TakeFromStack(FName InID, int InAmount)
{
	int amountInInventory = *InventoryContents.Find(InID);
	int newAmount = amountInInventory - InAmount;

	InventoryContents.Add(InID, newAmount);
	OwningPlayer->OnIDCalled.Broadcast(InID, -InAmount);
	OnInventoryUpdated.Broadcast(InID, newAmount);
}

void UInventoryComponent::AddQuestRewards(TArray<FQuestReward> InItemRewards)
{
	if (InItemRewards.Num() == 0)
	{
		return;
	}

	for (int i = 0; i < InItemRewards.Num(); i++)
	{
		FName itemID = InItemRewards[i].ItemDataHandle.RowName;
		int amount = InItemRewards[i].Amount;
		AddToInventory(itemID, amount);
	}
}

void UInventoryComponent::GiveMoney(int inMoney)
{
	Money += inMoney;
}

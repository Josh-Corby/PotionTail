// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryUpdated, FName, ItemID, int, ItemTotal);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTIONTAIL_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(BlueprintReadOnly)
	TMap<FName, int> InventoryContents;

	UPROPERTY(BlueprintReadOnly)
	int Money;

	class APotionTailCharacter* OwningPlayer;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnInventoryUpdated OnInventoryUpdated;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	void AddToInventory(FName InID, int InAmount);

	UFUNCTION(BlueprintPure)
	int QueryInventory(FName InID);

	UFUNCTION(BlueprintCallable)
	void TakeFromStack(FName InItemID, int InQuantity);

	UFUNCTION(BlueprintCallable)
	void AddQuestRewards(TArray<FQuestReward> InItemRewards);

	UFUNCTION(BlueprintCallable)
	void GiveMoney(int inMoney);
};

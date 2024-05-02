// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RecipeStruct.h"
#include "QuestRewardsStruct.h"
#include "CraftingComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTIONTAIL_API UCraftingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCraftingComponent();

	UPROPERTY(BlueprintReadOnly)
	class UInventoryComponent* LinkedInventory;

	class APotionTailCharacter* OwningPlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FDataTableRowHandle> InitialRecipes;

	UPROPERTY(BlueprintReadOnly)
	TArray<FDataTableRowHandle> KnownRecipes;

	UFUNCTION(BlueprintCallable)
	bool CraftRecipe(FRecipe InRecipe);

	UFUNCTION()
	void AddRecipies(TArray<FDataTableRowHandle> InRecipes);

	UFUNCTION(BlueprintCallable)
	void AddRecipe(FDataTableRowHandle InRecipe);

	UFUNCTION(BlueprintPure)
	FRecipe GetRecipeFromRowHandle(FDataTableRowHandle InRowHandle) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};

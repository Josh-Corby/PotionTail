#include "CraftingComponent.h"
#include "QuestLogComponent.h"
#include "Engine/DataTable.h"
#include "IngredientStruct.h"
#include "RecipeStruct.h"
#include "InventoryComponent.h"

UCraftingComponent::UCraftingComponent()
{
}

// Called when the game starts
void UCraftingComponent::BeginPlay()
{
	Super::BeginPlay();
	AddRecipies(InitialRecipes);

	LinkedInventory = GetOwner()->GetComponentByClass<UInventoryComponent>();
	UQuestLogComponent* playerQuestLog = GetOwner()->GetComponentByClass<UQuestLogComponent>();

	playerQuestLog->OnRecipeRewardGiven.AddDynamic(this, &UCraftingComponent::AddRecipies);
}

FRecipe UCraftingComponent::GetRecipeFromRowHandle(FDataTableRowHandle InRowHandle) const
{
	TObjectPtr<const UDataTable> RecipeTable = InRowHandle.DataTable;
	FName RowName = InRowHandle.RowName;
	FRecipe* RecipeData = RecipeTable->FindRow<FRecipe>(RowName, "FoundRecipe");
	return *RecipeData;
}

bool UCraftingComponent::CraftRecipe(FRecipe InRecipe)
{
	TArray<FIngredientStruct> ingredients = InRecipe.Ingredients;
	for (int i = 0; i < ingredients.Num(); i++)
	{
		FIngredientStruct ingredient = InRecipe.Ingredients[i];
		if (LinkedInventory->QueryInventory(ingredient.ItemData.RowName) < ingredient.AmountRequired)
		{
			return false;
		}
	}

	for (int i = 0; i < ingredients.Num(); i++)
	{
		FIngredientStruct ingredient = InRecipe.Ingredients[i];
		LinkedInventory->TakeFromStack(ingredient.ItemData.RowName, ingredient.AmountRequired);
		LinkedInventory->AddToInventory(InRecipe.ItemCreated.RowName, InRecipe.AmountMade);
	}	

	return true;
}

void UCraftingComponent::AddRecipies(TArray<FDataTableRowHandle> InRowHandles)
{
	for (int i = 0; i < InRowHandles.Num(); i++)
	{
		AddRecipe(InRowHandles[i]);
	}
}

void UCraftingComponent::AddRecipe(FDataTableRowHandle InRowHandle)
{
	KnownRecipes.Add(InRowHandle);
}

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "IngredientStruct.h"

#include "RecipeStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct POTIONTAIL_API FRecipe : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FIngredientStruct> Ingredients;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FDataTableRowHandle ItemCreated;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int AmountMade;

	FRecipe();
	~FRecipe();
};

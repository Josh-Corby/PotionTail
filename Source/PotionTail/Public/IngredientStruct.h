#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "IngredientStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct POTIONTAIL_API FIngredientStruct : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FDataTableRowHandle ItemData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int AmountRequired;

	FIngredientStruct();
	~FIngredientStruct();
};

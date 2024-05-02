#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "ItemStruct.generated.h"

USTRUCT(BlueprintType)
struct POTIONTAIL_API FItemStruct : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> ItemClass;

	FItemStruct();
	~FItemStruct();
};

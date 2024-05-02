#pragma once

#include "CoreMinimal.h"
#include "ObjectiveType.h"
#include "ObjectiveDetails.generated.h"

USTRUCT(BlueprintType)
struct POTIONTAIL_API FObjectiveDetails
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Quantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsOptional;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EObjectiveType Type;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	struct FDataTableRowHandle DataHandle;

	FObjectiveDetails();
	~FObjectiveDetails();
};

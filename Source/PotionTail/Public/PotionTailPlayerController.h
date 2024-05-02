#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PotionTailPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class POTIONTAIL_API APotionTailPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APotionTailPlayerController();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MenuAction;

protected:

	class APotionTailCharacter* PlayerCharacter;

	virtual void BeginPlay();

	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& InValue);

	void Interact(const FInputActionValue& Invalue);

	void Menu(const FInputActionValue& InValue);

};

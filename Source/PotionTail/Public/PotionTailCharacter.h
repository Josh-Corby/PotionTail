// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PlayerInterface.h"
#include "PotionTailCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectiveIDCalled, FName, ObjectiveID, int, Amount);

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class POTIONTAIL_API APotionTailCharacter : public ACharacter, public IPlayerInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quests, meta = (AllowPrivateAccess = "true"))
	class UQuestLogComponent* QuestLog;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* Inventory;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crafting, meta = (AllowPrivateAccess = "true"))
	class UCraftingComponent* Crafting;

public:

	APotionTailCharacter();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnObjectiveIDCalled OnIDCalled;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void OnInteractInput();

	void InteractTrace();	

protected:
	UPROPERTY(EditDefaultsOnly)
	float InteractDistance = 100.f;

	UPROPERTY(EditDefaultsOnly)
	float InteractRadius = 40.f;

	UPROPERTY(BlueprintReadOnly)
	AActor* InteractActor;

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns QuestLog component**/
	FORCEINLINE class UQuestLogComponent* GetQuestLog() const { return QuestLog; }
};
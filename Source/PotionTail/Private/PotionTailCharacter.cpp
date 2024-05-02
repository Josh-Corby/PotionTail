// Copyright Epic Games, Inc. All Rights Reserved.

#include "PotionTailCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Interactable.h"
#include "QuestLogComponent.h"
#include "InventoryComponent.h"
#include "CraftingComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APotionTailCharacter

APotionTailCharacter::APotionTailCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	QuestLog = CreateDefaultSubobject<UQuestLogComponent>(TEXT("QuestLog"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	Crafting = CreateDefaultSubobject<UCraftingComponent>(TEXT("Crafting"));
}

void APotionTailCharacter::Tick(float DeltaSeconds)
{
	InteractTrace();
}


void APotionTailCharacter::OnInteractInput()
{
	if (InteractActor)
	{
		 IInteractable* interacted = Cast<IInteractable>(InteractActor);
		 interacted->Execute_InteractWith(InteractActor, this);
	}
}

void APotionTailCharacter::InteractTrace()
{
	FVector TraceStart = GetActorLocation() - FVector(0.f, 0.f, 50.f);
	FVector TraceDistance = GetActorForwardVector() * InteractDistance;
	FVector TraceEnd = TraceStart + TraceDistance;

	FHitResult HitResult;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FCollisionResponseParams ResponseParams;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_GameTraceChannel1, QueryParams, ResponseParams))
	{
		AActor* HitActor = HitResult.GetActor();
		
		if (HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			if (InteractActor != HitActor)
			{
				InteractActor = HitActor;
				FName InteractText = Cast<IInteractable>(HitActor)->Execute_GetInteractableMessage(HitActor);

				UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *InteractText.ToString());
			}
		}
		else
		{
			InteractActor = nullptr;
		}
	}

	else
	{
		InteractActor = nullptr;
	}

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 5.f);
}

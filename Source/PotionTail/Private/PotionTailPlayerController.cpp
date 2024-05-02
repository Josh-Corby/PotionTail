#include "PotionTailPlayerController.h"
#include "GameFramework/Pawn.h"
#include "PotionTailCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

APotionTailPlayerController::APotionTailPlayerController()
{
}

void APotionTailPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APotionTailCharacter>(GetPawn());

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void APotionTailPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APotionTailPlayerController::Move);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APotionTailPlayerController::Interact);
		EnhancedInputComponent->BindAction(MenuAction, ETriggerEvent::Started, this, &APotionTailPlayerController::Menu);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APotionTailPlayerController::Move(const FInputActionValue& InValue)
{
	// input is a Vector2D
	FVector2D MovementVector = InValue.Get<FVector2D>();

	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	PlayerCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
	PlayerCharacter->AddMovementInput(RightDirection, MovementVector.X);
}

void APotionTailPlayerController::Interact(const FInputActionValue& Invalue)
{
	PlayerCharacter->OnInteractInput();
}

void APotionTailPlayerController::Menu(const FInputActionValue& InValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Open menu"));
}

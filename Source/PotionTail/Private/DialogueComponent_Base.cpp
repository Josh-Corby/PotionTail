#include "DialogueComponent_Base.h"

// Sets default values for this component's properties
UDialogueComponent_Base::UDialogueComponent_Base()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDialogueComponent_Base::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UDialogueComponent_Base::OpenConversation_Implementation()
{
}

void UDialogueComponent_Base::CloseConversation_Implementation()
{
}

void UDialogueComponent_Base::ProgressDialogue_Implementation()
{
}

void UDialogueComponent_Base::Dialogue_Implementation()
{
}

void UDialogueComponent_Base::UpdateSelectedOption_Implementation()
{
}

void UDialogueComponent_Base::ClearDialogueProgress_Implementation()
{
}

void UDialogueComponent_Base::RemoveDialogueProgress_Implementation()
{
}

void UDialogueComponent_Base::SetDialogueTreeIndex_Implementation()
{
}

void UDialogueComponent_Base::AddDialogue_Implementation(const FText& InSpeakerName, const FText& InDialogue, const TArray<FText>& InOptionsText)
{
}


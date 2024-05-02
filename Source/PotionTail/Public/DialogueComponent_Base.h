#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueComponent_Base.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTIONTAIL_API UDialogueComponent_Base : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueComponent_Base();

	UPROPERTY(BlueprintReadWrite)
	TMap<int, int> DialogueProgress;

	UPROPERTY(BlueprintReadWrite)
	int DialogueIndex;

	UPROPERTY(BlueprintReadWrite)
	int DialogueTreeIndex;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OpenConversation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CloseConversation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ProgressDialogue();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Dialogue();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddDialogue(const FText& InSpeakerName, const FText& InDialogue, const TArray<FText>& InOptionsText);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateSelectedOption();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ClearDialogueProgress();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RemoveDialogueProgress();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetDialogueTreeIndex();
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactable.h"
#include "QuestGiverComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTIONTAIL_API UQuestGiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestGiverComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quests")
	struct FDataTableRowHandle QuestData;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DisplayGiveQuest();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DisplayQuestInProgress();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DisplayQuestReadyToComplete();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DisplayQuestAlreadyCompleted();

	UFUNCTION(BlueprintCallable)
	void OnInteract(AActor* InActor);
};

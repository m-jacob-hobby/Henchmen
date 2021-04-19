// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HenchmenTaskActor.generated.h"



UCLASS()
class HENCHMEN_API AHenchmenTaskActor : public AActor
{
	GENERATED_BODY()

public:	
	AHenchmenTaskActor();

	UFUNCTION(BlueprintCallable)
		bool TaskIsCompleted();

	UFUNCTION(BlueprintCallable)
		void SetTaskCompleted();

	UFUNCTION(BlueprintCallable)
		bool TaskIsSabotaged();

	UFUNCTION(BlueprintCallable)
		void SetTaskSabotaged();

	UFUNCTION(BlueprintCallable)
		void SabotagedTaskFixed();

	UFUNCTION(BlueprintCallable)
		bool TaskIsOpened();

	UFUNCTION(BlueprintCallable)
		void SetTaskOpened();

	UFUNCTION(BlueprintCallable)
		void SetTaskClosed();

private:
	UPROPERTY(Replicated)
		bool IsCompleted;

	UPROPERTY(Replicated)
		bool IsSabotaged;

	UPROPERTY(Replicated)
		bool IsOpened;

};

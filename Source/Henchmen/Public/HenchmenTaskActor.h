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
		bool CheckTaskCompleted();

	UFUNCTION(BlueprintCallable)
		void UpdateTaskToCompleted();

	UFUNCTION(BlueprintCallable)
		bool CheckTaskSabotaged();

	UFUNCTION(BlueprintCallable)
		void UpdateTaskToSabotaged();

	UFUNCTION(BlueprintCallable)
		void UpdateTaskToFixed();

	UFUNCTION(BlueprintCallable)
		bool CheckTaskInterfaceOpened();

	UFUNCTION(BlueprintCallable)
		void OpenTaskInterface();

	UFUNCTION(BlueprintCallable)
		void CloseTaskInterface();

private:
	UPROPERTY(Replicated)
		bool IsCompleted;

	UPROPERTY(Replicated)
		bool IsSabotaged;

	UPROPERTY(Replicated)
		bool IsOpened;

};

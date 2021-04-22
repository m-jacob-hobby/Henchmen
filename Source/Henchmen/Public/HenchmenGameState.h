// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "HenchmenGameState.generated.h"

/**
 * 
 */
UCLASS()
class HENCHMEN_API AHenchmenGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated)
		FString LatestEvent;

	UPROPERTY(Replicated)
		int TotalTasksCount;

	UPROPERTY(Replicated)
		int CompletedTasksCount;

	UPROPERTY(Replicated)
		FString TimerClock;

	UPROPERTY(Replicated)
		FString WinningTeam;

	UFUNCTION(BlueprintCallable, Category = "Server Settings")
		void NewHenchmenTaskCompleted();

	UFUNCTION(BlueprintCallable, Category = "Server Settings")
		void HenchmenTaskSabotaged();

	UFUNCTION(BlueprintCallable, Category = "Server Settings")
		int GetCompletedHenchmenTasks();

	UFUNCTION(BlueprintCallable, Category = "Server Settings")
		int GetTotalHenchmenTasks();
};

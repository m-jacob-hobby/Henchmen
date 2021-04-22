// Fill out your copyright notice in the Description page of Project Settings.


#include "HenchmenGameState.h"
#include "Net/UnrealNetwork.h"

void AHenchmenGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHenchmenGameState, LatestEvent);
	DOREPLIFETIME(AHenchmenGameState, TotalTasksCount);
	DOREPLIFETIME(AHenchmenGameState, CompletedTasksCount);
	DOREPLIFETIME(AHenchmenGameState, TimerClock);
	DOREPLIFETIME(AHenchmenGameState, WinningTeam);
}

void AHenchmenGameState::NewHenchmenTaskCompleted()
{
	if (CompletedTasksCount < TotalTasksCount)
	{
		this->CompletedTasksCount = CompletedTasksCount++;
		int RemainingTasks = TotalTasksCount - CompletedTasksCount;
		LatestEvent = TEXT("Another task was completed! Only " + FString::FromInt(RemainingTasks) + " more tasks remain...");
	}
}

void AHenchmenGameState::HenchmenTaskSabotaged()
{
	if (CompletedTasksCount > 0)
	{
		int RemainingTasks = TotalTasksCount - CompletedTasksCount;
		LatestEvent = TEXT("A task has been sabotaged! " + FString::FromInt(RemainingTasks) + " more tasks still remain to be completed...");
	}
}

int AHenchmenGameState::GetCompletedHenchmenTasks()
{
	return CompletedTasksCount;
}

int AHenchmenGameState::GetTotalHenchmenTasks()
{
	return TotalTasksCount;
}
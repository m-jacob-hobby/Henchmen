// Fill out your copyright notice in the Description page of Project Settings.

#include "HenchmenTaskActor.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"

AHenchmenTaskActor::AHenchmenTaskActor() {
	bReplicates = true;
	bAlwaysRelevant = true;
	IsCompleted = false;
	IsOpened = false;
	IsSabotaged = false;
}

void AHenchmenTaskActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHenchmenTaskActor, IsCompleted);
	DOREPLIFETIME(AHenchmenTaskActor, IsOpened);
	DOREPLIFETIME(AHenchmenTaskActor, IsSabotaged);
}

bool AHenchmenTaskActor::CheckTaskCompleted()
{
	return IsCompleted;
}

void AHenchmenTaskActor::UpdateTaskToCompleted()
{
	if (!IsSabotaged && !IsCompleted)
	{
		IsSabotaged = false;
		IsCompleted = true;
	}
}

bool AHenchmenTaskActor::CheckTaskSabotaged()
{
	return IsSabotaged;
}

void AHenchmenTaskActor::UpdateTaskToSabotaged()
{
	if (!IsSabotaged && !IsCompleted) 
	{
		IsSabotaged = true;
		IsCompleted = false;
	}
}

void AHenchmenTaskActor::UpdateTaskToFixed()
{
	if (IsSabotaged && !IsCompleted)
	{
		IsSabotaged = false;
		IsCompleted = false;
	}
}

bool AHenchmenTaskActor::CheckTaskInterfaceOpened()
{
	return IsOpened;
}

void AHenchmenTaskActor::OpenTaskInterface()
{
	IsOpened = true;
}

void AHenchmenTaskActor::CloseTaskInterface()
{
	IsOpened = false;
}
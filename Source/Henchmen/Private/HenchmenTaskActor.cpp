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

bool AHenchmenTaskActor::TaskIsCompleted()
{
	return IsCompleted;
}

void AHenchmenTaskActor::SetTaskCompleted()
{
	if (!IsSabotaged)
	{
		IsCompleted = true;
	}
}

bool AHenchmenTaskActor::TaskIsSabotaged()
{
	return IsSabotaged;
}

void AHenchmenTaskActor::SetTaskSabotaged()
{
	IsSabotaged = true;
	IsCompleted = false;
}

void AHenchmenTaskActor::SabotagedTaskFixed()
{
	IsSabotaged = false;
}

bool AHenchmenTaskActor::TaskIsOpened()
{
	return IsOpened;
}

void AHenchmenTaskActor::SetTaskOpened()
{
	IsOpened = true;
}

void AHenchmenTaskActor::SetTaskClosed()
{
	IsOpened = false;
}
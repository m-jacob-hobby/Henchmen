// Fill out your copyright notice in the Description page of Project Settings.


#include "HenchmenPlayerState.h"
#include "Net/UnrealNetwork.h"

void AHenchmenPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHenchmenPlayerState, Team);
}

bool AHenchmenPlayerState::PlayerIsAHenchman()
{
	return Team.Equals("henchmen");
}

bool AHenchmenPlayerState::PlayerIsASpy()
{
	return Team.Equals("spies");
}
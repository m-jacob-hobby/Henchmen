// Fill out your copyright notice in the Description page of Project Settings.

#include "HenchmenTaskActor.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"

AHenchmenTaskActor::AHenchmenTaskActor() {
	static ConstructorHelpers::FClassFinder<AActor> GameObj(TEXT("/Game/ThirdPersonCPP/Blueprints/BP_Task"));
	TaskActorClass = GameObj.Class;
	IsCompleted = false;
}

void AHenchmenTaskActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHenchmenTaskActor, IsCompleted);
}


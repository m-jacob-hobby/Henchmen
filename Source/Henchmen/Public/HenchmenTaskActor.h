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

	UPROPERTY(Replicated)
		bool IsCompleted;

private:
	UPROPERTY()
		TSubclassOf<AActor> TaskActorClass;

};

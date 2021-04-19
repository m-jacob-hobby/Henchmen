// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HenchmenWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class HENCHMEN_API UHenchmenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
		FTimerHandle SetTeammateCountHandle;

	UPROPERTY()
		FTimerHandle SetTimerHandle;

	UPROPERTY()
		FTimerHandle SetLatestEventHandle;

	UPROPERTY()
		FTimerHandle SetAveragePlayerLatencyHandle;

	UPROPERTY()
		FTimerHandle SetTasksCompletedPercentageHandle;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY()
		UTextBlock* TeamNameTextBlock;

	UPROPERTY()
		UTextBlock* EventTextBlock;

	UPROPERTY()
		UTextBlock* TimerTextBlock;

	UPROPERTY()
		UTextBlock* PingTextBlock;

	UPROPERTY()
		UProgressBar* CompletedTasksProgressBar;

	UPROPERTY()
		UImage* HenchmanIconImage;

	UPROPERTY()
		UImage* SpyIconImage;

	UFUNCTION()
		void SetTeammateCount();

	UFUNCTION()
		void SetTimer();

	UFUNCTION()
		void SetLatestEvent();

	UFUNCTION()
		void SetAveragePlayerLatency();

	UFUNCTION()
		void SetTasksCompletedPercentage();
};

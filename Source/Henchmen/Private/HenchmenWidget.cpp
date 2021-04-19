// Fill out your copyright notice in the Description page of Project Settings.


#include "HenchmenWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameStateBase.h"
#include "HenchmenPlayerState.h"
#include "HenchmenGameState.h"
#include "HenchmenGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UHenchmenWidget::NativeConstruct() {
	Super::NativeConstruct();

	TeamNameTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_TeamName"));
	EventTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Event"));
	TimerTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Timer"));
	PingTextBlock = (UTextBlock*)GetWidgetFromName(TEXT("TextBlock_Ping"));
	HenchmanIconImage = (UImage*)GetWidgetFromName(TEXT("Image_HenchmanIcon"));
	SpyIconImage = (UImage*)GetWidgetFromName(TEXT("Image_SpyIcon"));
	CompletedTasksProgressBar = (UProgressBar*)GetWidgetFromName(TEXT("ProgressBar_TasksCompleted"));

	GetWorld()->GetTimerManager().SetTimer(SetTeammateCountHandle, this, &UHenchmenWidget::SetTeammateCount, 1.0f, true, 1.0f);
	GetWorld()->GetTimerManager().SetTimer(SetLatestEventHandle, this, &UHenchmenWidget::SetLatestEvent, 1.0f, true, 1.0f);
	GetWorld()->GetTimerManager().SetTimer(SetTimerHandle, this, &UHenchmenWidget::SetTimer, 1.0f, true, 1.0f);
	GetWorld()->GetTimerManager().SetTimer(SetAveragePlayerLatencyHandle, this, &UHenchmenWidget::SetAveragePlayerLatency, 1.0f, true, 1.0f);
	GetWorld()->GetTimerManager().SetTimer(SetTasksCompletedPercentageHandle, this, &UHenchmenWidget::SetTasksCompletedPercentage, 1.0f, true, 1.0f);
}

void UHenchmenWidget::NativeDestruct() {
	GetWorld()->GetTimerManager().ClearTimer(SetTeammateCountHandle);
	GetWorld()->GetTimerManager().ClearTimer(SetLatestEventHandle);
	GetWorld()->GetTimerManager().ClearTimer(SetTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(SetAveragePlayerLatencyHandle);
	GetWorld()->GetTimerManager().ClearTimer(SetTasksCompletedPercentageHandle);
	Super::NativeDestruct();
}

void UHenchmenWidget::SetTeammateCount() {
	FString OwningPlayerTeam;
	APlayerState* OwningPlayerState = GetOwningPlayerState();

	if (OwningPlayerState != nullptr) {
		AHenchmenPlayerState* OwningHenchmenPlayerState = Cast<AHenchmenPlayerState>(OwningPlayerState);
		if (OwningHenchmenPlayerState != nullptr) {
			OwningPlayerTeam = OwningHenchmenPlayerState->Team;
			if (OwningPlayerTeam.Equals("henchmen")) {
				TeamNameTextBlock->SetText(FText::FromString("You are a henchman! Complete your tasks before time runs out."));
				HenchmanIconImage->SetVisibility(ESlateVisibility::Visible);
				SpyIconImage->SetVisibility(ESlateVisibility::Hidden);
			}
			else {
				TeamNameTextBlock->SetText(FText::FromString("You are a spy! Sabotage the Henchmen's operations."));
				HenchmanIconImage->SetVisibility(ESlateVisibility::Hidden);
				SpyIconImage->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}

}

void UHenchmenWidget::SetTimer() {
	FString TimerClock;
	AGameStateBase* GameState = GetWorld()->GetGameState();

	if (GameState != nullptr) {
		AHenchmenGameState* HenchmenGameState = Cast<AHenchmenGameState>(GameState);
		if (HenchmenGameState != nullptr) {
			TimerClock = HenchmenGameState->TimerClock;
		}
	}

	TimerTextBlock->SetText(FText::FromString(TimerClock));
}

void UHenchmenWidget::SetLatestEvent() {
	FString LatestEvent;
	FString WinningTeam;
	AGameStateBase* GameState = GetWorld()->GetGameState();

	if (GameState != nullptr) {
		AHenchmenGameState* HenchmenGameState = Cast<AHenchmenGameState>(GameState);
		if (HenchmenGameState != nullptr) {
			LatestEvent = HenchmenGameState->LatestEvent;
			WinningTeam = HenchmenGameState->WinningTeam;
		}
	}

	if (LatestEvent.Len() > 0) {
		if (LatestEvent.Equals("GameEnded")) {
			FString OwningPlayerTeam;
			APlayerState* OwningPlayerState = GetOwningPlayerState();

			if (OwningPlayerState != nullptr) {
				AHenchmenPlayerState* OwningHenchmenPlayerState = Cast<AHenchmenPlayerState>(OwningPlayerState);
				if (OwningHenchmenPlayerState != nullptr) {
					OwningPlayerTeam = OwningHenchmenPlayerState->Team;
				}
			}

			if (WinningTeam.Len() > 0 && OwningPlayerTeam.Len() > 0) {
				FString GameOverMessage = "You and the " + OwningPlayerTeam;
				if (OwningPlayerTeam.Equals(WinningTeam)) {
					EventTextBlock->SetText(FText::FromString(GameOverMessage + " won!"));
				}
				else {
					EventTextBlock->SetText(FText::FromString(GameOverMessage + " lost."));
				}
			}
		}
		else {
			EventTextBlock->SetText(FText::FromString(LatestEvent));
		}
	}
}

void UHenchmenWidget::SetAveragePlayerLatency() {
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance != nullptr) {
		UHenchmenGameInstance* HenchmenGameInstance = Cast<UHenchmenGameInstance>(GameInstance);
		if (HenchmenGameInstance != nullptr) {
			float TotalPlayerLatency = 0.0f;
			for (float PlayerLatency : HenchmenGameInstance->PlayerLatencies) {
				TotalPlayerLatency += PlayerLatency;
			}

			float AveragePlayerLatency = 60.0f;

			if (TotalPlayerLatency > 0) {
				AveragePlayerLatency = TotalPlayerLatency / HenchmenGameInstance->PlayerLatencies.Num();

				FString PingString = "Ping: " + FString::FromInt(FMath::RoundToInt(AveragePlayerLatency)) + "ms";
				PingTextBlock->SetText(FText::FromString(PingString));
			}
		}
	}
}

void UHenchmenWidget::SetTasksCompletedPercentage() {
	int TotalAvailableTasks;
	int CompletedTasks;
	AGameStateBase* GameState = GetWorld()->GetGameState();
	if (GameState != nullptr) {
		AHenchmenGameState* HenchmenGameState = Cast<AHenchmenGameState>(GameState);
		if (HenchmenGameState != nullptr) {
			TotalAvailableTasks = HenchmenGameState->TotalHenchmenTasks;
			CompletedTasks = HenchmenGameState->CompletedHenchmenTasks;
			CompletedTasksProgressBar->SetPercent(float(CompletedTasks) / float(TotalAvailableTasks));
		}
	}
}

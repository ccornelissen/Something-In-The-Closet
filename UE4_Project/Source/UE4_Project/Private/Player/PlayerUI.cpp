// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Project.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "ClosetPlayer.h"
#include "PlayerUI.h"

void UPlayerUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerUI::DisplayImage(int32 iArrayRef)
{
	ImageArray[0]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	APlayerController* CurPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

	iCurrentDisplayedImage = iArrayRef;

	AClosetPlayer* CPlayer = Cast<AClosetPlayer>(CurPlayer->GetPawn());

	if (CPlayer != nullptr)
	{
		CPlayer->CurrentPlayerState = EPlayerState::CP_LookingAtObject;
	}

	if (CurPlayer != nullptr)
	{
		CurPlayer->SetPause(true);
	}
}

void UPlayerUI::CloseImage()
{
	APlayerController* CurPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

	if (CurPlayer != nullptr)
	{
		CurPlayer->SetPause(false);
	}

	ImageArray[iCurrentDisplayedImage]->SetVisibility(ESlateVisibility::Hidden);
}

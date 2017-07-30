// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Project.h"
#include "Player/ClosetPlayer.h"
#include "ClosetBed.h"



// Sets default values
AClosetBed::AClosetBed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BedMesh"));
	SetRootComponent(BedMesh);
}

void AClosetBed::EnterBed(AClosetPlayer* Player)
{
	if (Player != nullptr)
	{
		Player->CurrentPlayerState = EPlayerState::CP_InBedSafe;

		FRotator RotToSet = FRotator(90, 0, 0);

		Player->SetActorLocation(PlayerBedLoc.GetLocation());
		Player->SetActorRotation(RotToSet);

		UStaticMeshComponent* BedSheet = &Player->GetPlayerBedSheet();

		if (BedSheet != nullptr)
		{
			BedSheet->SetVisibility(true);
			BedSheet->SetActive(true);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Player does not have bed sheet set!"));
		}
	}
}

void AClosetBed::LeaveBed(AClosetPlayer * Player)
{
	if (Player != nullptr)
	{
		Player->CurrentPlayerState = EPlayerState::CP_Wandering;

		Player->SetActorLocation(PlayerBedExitLoc.GetLocation());
		Player->SetActorRotation(Player->PlayerStartRot);

		UStaticMeshComponent* BedSheet = &Player->GetPlayerBedSheet();

		if (BedSheet != nullptr)
		{
			BedSheet->SetVisibility(false);
			BedSheet->SetActive(false);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Player does not have bed sheet set!"));
		}

		UCameraComponent* PlayerCam = &Player->GetPlayerCamera();

		if (PlayerCam != nullptr)
		{
			PlayerCam->SetWorldRotation(FRotator::ZeroRotator);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Player does not have camera set!"));
		}
	}
}




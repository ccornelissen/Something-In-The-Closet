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

		FRotator RotToSet = FRotator(PlayerBedLoc.GetRotation().Rotator().Pitch, Player->GetActorRotation().Yaw, Player->GetActorRotation().Roll);

		Player->SetActorLocation(PlayerBedLoc.GetLocation());
		Player->SetActorRotation(RotToSet);
	}
}

void AClosetBed::LeaveBed(AClosetPlayer * Player)
{
	if (Player != nullptr)
	{
		Player->CurrentPlayerState = EPlayerState::CP_Wandering;

		Player->SetActorLocation(PlayerBedExitLoc.GetLocation());
		Player->SetActorRotation(Player->PlayerStartRot);
	}
}




// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Project.h"
#include "ClosetBed.h"
#include "ClosetPlayer.h"


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
	Player->CurrentPlayerState = EPlayerState::CP_InBedSafe;

	FVector PlayerLoc = Player->GetActorLocation();

	Player->SetActorLocation(PlayerBedLoc);
}




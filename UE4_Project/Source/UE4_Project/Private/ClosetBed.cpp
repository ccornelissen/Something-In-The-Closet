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
	BedMesh->SetupAttachment(GetRootComponent());
}

void AClosetBed::EnterBed(AClosetPlayer* Player)
{
	Player->CurrentPlayerState = EPlayerState::CP_InBedSafe;

	FVector PlayerLoc = Player->GetActorLocation();

	//while (PlayerLoc != PlayerBedLoc)
	//{
		//FVector NewLoc = FMath::Lerp(PlayerLoc, PlayerBedLoc, fEnterBedSpeed);

	Player->SetActorLocation(PlayerBedLoc);

		//PlayerLoc = Player->GetActorLocation();
	//}
}




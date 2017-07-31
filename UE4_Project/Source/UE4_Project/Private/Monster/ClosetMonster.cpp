// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Project.h"
#include "ClosetMonster.h"


// Sets default values
AClosetMonster::AClosetMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClosetMonster::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocation = GetActorLocation();
}

// Called every frame
void AClosetMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


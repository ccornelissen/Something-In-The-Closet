// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Project.h"
#include "ClosetMonster.h"
#include "ClosetPlayer.h"
#include "MonsterSpawner.h"


// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMonsterSpawner::SpawnMonster()
{
	if (MonsterToSpawn != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRot = GetActorRotation();
			const FVector SpawnLocation = GetActorLocation();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AClosetPlayer* Player = Cast<AClosetPlayer>(World->GetFirstPlayerController()->GetPawn());

			// spawn the projectile at the muzzle
			Player->CurMonster = World->SpawnActor<AClosetMonster>(MonsterToSpawn, SpawnLocation, SpawnRot, ActorSpawnParams);
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Project.h"
#include "ClosetMonster.h"
#include "ClosetPlayer.h"
#include "PatrolPointsComponent.h"
#include "MonsterSpawner.h"


// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create patrol component
	PatrolComp = CreateDefaultSubobject<UPatrolPointsComponent>(TEXT("Patrol Points"));
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

			// spawn the monster
			if (MonsterToSpawn != nullptr)
			{
				AClosetMonster* SpawnedMonster = World->SpawnActor<AClosetMonster>(MonsterToSpawn, SpawnLocation, SpawnRot, ActorSpawnParams);
				Player->CurMonster = SpawnedMonster;

				//Pass housed patrol points to the spawned monster
				SpawnedMonster->PatrolPoints = PatrolComp->PatrolPoints;
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Monster spawner doesn't have a monster set to spawn!"));
			}
			
		}
	}
}

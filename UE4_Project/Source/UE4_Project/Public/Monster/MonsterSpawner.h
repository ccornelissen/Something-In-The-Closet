// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MonsterSpawner.generated.h"

class UPatrolPointsComponent;
UCLASS()
class UE4_PROJECT_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawner();

	//Spawn the monster
	void SpawnMonster();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patrol Points")
	UPatrolPointsComponent* PatrolComp;

protected:
	//Reference to the monster
	UPROPERTY(EditDefaultsOnly, Category = Monster)
	TSubclassOf<class AClosetMonster> MonsterToSpawn;



	
	
};

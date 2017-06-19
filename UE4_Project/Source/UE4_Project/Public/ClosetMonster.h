// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ClosetMonster.generated.h"

UCLASS()
class UE4_PROJECT_API AClosetMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AClosetMonster();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector SpawnLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};

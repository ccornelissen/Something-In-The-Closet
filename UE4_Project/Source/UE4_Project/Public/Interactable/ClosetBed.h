// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ClosetBed.generated.h"

class AClosetPlayer;

UCLASS()
class UE4_PROJECT_API AClosetBed : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* BedMesh = nullptr;

public:	
	// Sets default values for this actor's properties
	AClosetBed();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void EnterBed(AClosetPlayer* Player);

	UPROPERTY(BlueprintReadWrite, Category = "Gameplay")
	FVector PlayerBedLoc;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float fEnterBedSpeed = 0.5f;

};

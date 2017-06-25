// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ClosetPlayer.generated.h"

UENUM()
enum class EPlayerState : uint8
{
	CP_Wandering,
	CP_InBedSafe,
	CP_InBedPeeking,
	CP_LookingAtObject,
	CP_Paused,
	CP_Cinematic
};

class UPlayerUI;
class AClosetMonster;

UCLASS()
class UE4_PROJECT_API AClosetPlayer : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "First Person", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent = nullptr;

public:
	// Sets default values for this character's properties
	AClosetPlayer();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate;

	//How far away the player can be from an object before they get the option to interact
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float fPlayerReach = 75.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	UPlayerUI* PlayerUI;

	AClosetMonster* CurMonster;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	EPlayerState CurrentPlayerState = EPlayerState::CP_Wandering;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Cancel();

	/** Player Movement Functions */
	void MoveForward(float Val);

	void MoveRight(float Val);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);


private:
	const FHitResult GetTrace();

	void HighlightHit(FHitResult LineTraceHit);

	//Calculates distance between monster and player for HUD warning
	void GetDistanceFromMonster();

	void Interact();

};

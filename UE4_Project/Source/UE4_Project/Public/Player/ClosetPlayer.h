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
class UInteractableComponent;
class UCameraComponent;

UCLASS()
class UE4_PROJECT_API AClosetPlayer : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "First Person", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent = nullptr;

public:
	// Sets default values for this character's properties
	AClosetPlayer();

	/** Control turning sensitivity */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate = 100.0f;

	/** Control Mouse Y Sensitivity */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate = 100.0f;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
	EPlayerState CurrentPlayerState = EPlayerState::CP_Wandering;

	//In Radians
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float fCamMinPitch = -50.0f;
	//In Radians
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float fCamMaxPitch = 50.0f;

	//In Radians
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float fCamMinYaw = -100.0f;
	//In Radians
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float fCamMaxYaw = 100.0f;

	//How far the player moves the sheet done
	UPROPERTY(EditDefaultsOnly, Category = "Bed")
	float fSheetDecent = 70.0f;

	FRotator PlayerStartRot;

	//Getters 
	UStaticMeshComponent& GetPlayerBedSheet();
	UCameraComponent& GetPlayerCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Cancel();

	/** Player Movement Functions */
	void MoveForward(float Val);

	void MoveRight(float Val);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void SheetShieldDown();

	void SheetShieldUp();

	UPROPERTY(BlueprintReadWrite, Category = "Bed")
	UStaticMeshComponent* BedSheet = nullptr;

	FVector BedSheetStartLoc;

private:
	//Functions that allow player to interact with objects
	const FHitResult GetTrace(); //See if player is looking at object
	void HighlightHit(FHitResult LineTraceHit); //Highlight if object is interactable
	void Interact(); //Call interact blueprint if player clicks on object

	//Calculates distance between monster and player for HUD warning
	void GetDistanceFromMonster();

	//Storing the last interacted actor
	UInteractableComponent* LastInteractActor = nullptr;
};

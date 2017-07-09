// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Project.h"
#include "Interactable/InteractableComponent.h"
#include "PlayerUI.h"
#include "ClosetMonster.h"
#include "ClosetPlayer.h"

// Sets default values
AClosetPlayer::AClosetPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//FIRST PERSON COMPONENT SET UP
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(40.0f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void AClosetPlayer::BeginPlay()
{
	Super::BeginPlay();

	PlayerStartRot = GetActorRotation();
	
}

// Called every frame
void AClosetPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HighlightHit(GetTrace());

	GetDistanceFromMonster();
}

void AClosetPlayer::HighlightHit(FHitResult LineTraceHit)
{
	if (LineTraceHit.Actor != nullptr)
	{
		//Get the Interactable component from the actor
		UInteractableComponent* HighlightActor = LineTraceHit.Actor->FindComponentByClass<UInteractableComponent>();

		//Check to make sure the actor has the component
		if (HighlightActor != nullptr)
		{
			//Turning on the post process
			HighlightActor->Viewed();
		}
	}
}

void AClosetPlayer::GetDistanceFromMonster()
{
	if (CurMonster != nullptr)
	{
		FVector MonsterPos = CurMonster->GetActorLocation();
		FVector PlayerPos = GetActorLocation();

		float fDis = FVector::Dist(MonsterPos, PlayerPos);

		//Calculate the number so that the closer we get the higher number it will return
		fDis = 1.0f - (fDis / 1000);

		if (PlayerUI != nullptr)
		{
			PlayerUI->DistanceFromMonster = fDis;
		}
	}
}

void AClosetPlayer::Interact()
{
	FHitResult LineTraceHit = GetTrace();

	if (LastInteractActor != nullptr)
	{
		LastInteractActor->Untouched(this);
		LastInteractActor = nullptr;
		return;
	}

	if (LineTraceHit.Actor != nullptr)
	{
		//Get the Interactable component from the actor
		UInteractableComponent* InteractActor = LineTraceHit.Actor->FindComponentByClass<UInteractableComponent>();

		//Check to make sure the actor has the component
		if (InteractActor != nullptr)
		{
			LastInteractActor = InteractActor;
			//trigger the interaction
			InteractActor->Touched(this);
		}
	}

}

const FHitResult AClosetPlayer::GetTrace()
{
	//Get where the player is looking
	FVector PlayerLoc;
	FRotator PlayerRot;

	GetController()->GetPlayerViewPoint(PlayerLoc, PlayerRot);

	//Calculate how far they can reach based off where they're looking
	FVector LineTraceEnd = PlayerLoc + (PlayerRot.Vector() * fPlayerReach);

	FHitResult LineTraceHit;

	//Set up query params
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	//Perform the line trace
	GetWorld()->LineTraceSingleByObjectType
		(
			LineTraceHit,
			PlayerLoc,
			LineTraceEnd,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
			TraceParams
		);

	return LineTraceHit;
}

// Called to bind functionality to input
void AClosetPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AClosetPlayer::Interact).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("Cancel", IE_Pressed, this, &AClosetPlayer::Cancel).bExecuteWhenPaused = true;

	
	PlayerInputComponent->BindAxis("MoveForward", this, &AClosetPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AClosetPlayer::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &AClosetPlayer::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AClosetPlayer::LookUpAtRate);
}

void AClosetPlayer::MoveForward(float Value)
{
	if (Value != 0.0f && CurrentPlayerState == EPlayerState::CP_Wandering)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AClosetPlayer::MoveRight(float Value)
{
	if (Value != 0.0f && CurrentPlayerState == EPlayerState::CP_Wandering)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AClosetPlayer::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	FRotator StartRot = GetActorRotation();
	float YawToSet = StartRot.Yaw + (Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

	FRotator RotToSet = FRotator(StartRot.Pitch, YawToSet, StartRot.Roll);

	SetActorRotation(RotToSet);
}

void AClosetPlayer::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	FRotator StartRot = FirstPersonCameraComponent->GetComponentRotation();
	float PitchToSet = FMath::Clamp(StartRot.Pitch + (Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds()), fCamMinPitch, fCamMaxPitch);

	FRotator RotToSet = FRotator(PitchToSet, StartRot.Yaw, StartRot.Roll);

	FirstPersonCameraComponent->SetWorldRotation(RotToSet, false);
}

void AClosetPlayer::Cancel()
{
	if (CurrentPlayerState == EPlayerState::CP_LookingAtObject)
	{
		//Return if there is no player UI
		if (PlayerUI != nullptr)
		{
			PlayerUI->CloseImage();

			CurrentPlayerState = EPlayerState::CP_Wandering;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No Player UI Present!"));
		}
	}
}



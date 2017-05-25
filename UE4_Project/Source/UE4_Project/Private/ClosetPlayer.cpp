// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Project.h"
#include "ClosetPlayer.h"
#include "InteractableComponent.h"

// Sets default values
AClosetPlayer::AClosetPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//FIRST PERSON COMPONENT SET UP
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(40.0f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AClosetPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClosetPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HighlightHit(GetTrace());
}

void AClosetPlayer::HighlightHit(FHitResult LineTraceHit)
{
	if (LineTraceHit.Actor != nullptr)
	{
		//Get the UUserhighlight component from the actor
		UInteractableComponent* HighlightActor = LineTraceHit.Actor->FindComponentByClass<UInteractableComponent>();

		UE_LOG(LogTemp, Warning, TEXT("Found Actor!!!"));

		//Check to make sure the actor has the component
		if (HighlightActor != nullptr)
		{
			//Turning on the post process
			HighlightActor->Touched();

			UE_LOG(LogTemp, Warning, TEXT("TOUCHING!!!"));
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

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AClosetPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AClosetPlayer::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AClosetPlayer::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AClosetPlayer::LookUpAtRate);
}

void AClosetPlayer::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AClosetPlayer::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AClosetPlayer::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AClosetPlayer::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}




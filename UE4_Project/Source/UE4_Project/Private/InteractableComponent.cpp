// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Project.h"
#include "InteractableComponent.h"
#include "ClosetPlayer.h"


// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	//Get the static mesh component
	ActorMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
}


// Called every frame
void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Revert material if user hasn't looked at it
	if ((GetWorld()->GetTimeSeconds() - fMaterialRevertTimer) > fMaterialRevertTime)
	{
		if (ActorMesh == nullptr)
		{
			return;
		}

		//Turning off the highlight
		ActorMesh->SetRenderCustomDepth(false);
	}
}

void UInteractableComponent::Viewed()
{
	if (ActorMesh == nullptr)
	{
		return;
	}

	//Turning on the highlight
	ActorMesh->SetRenderCustomDepth(true);

	//Set the revert timer to current time
	fMaterialRevertTimer = GetWorld()->GetTimeSeconds();
}

void UInteractableComponent::Touched(AClosetPlayer* Player)
{
	if (Player != nullptr)
	{
		CurrentPlayer = Player;
	}

	WasTouched.Broadcast();
}
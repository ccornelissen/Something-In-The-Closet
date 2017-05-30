// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

class AClosetPlayer;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTouchDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_PROJECT_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Function used to turn on custom depth to show outline
	void Viewed();

	void Touched(AClosetPlayer* Player);

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	AClosetPlayer* CurrentPlayer = nullptr;

	UPROPERTY(BlueprintAssignable)
	FTouchDelegate WasTouched; //Event to tell the door to open

private:
	//Reference to the highlight actor
	UStaticMeshComponent* ActorMesh = nullptr;

	//Timer used to turn off the highlight when player leaves it
	float fMaterialRevertTimer;

	//How long before the highlight turns off
	UPROPERTY(EditAnywhere)
	float fMaterialRevertTime = 0.2f;
	
};

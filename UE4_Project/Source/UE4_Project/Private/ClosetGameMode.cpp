// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Project.h"
#include "ClosetGameMode.h"

AClosetGameMode::AClosetGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Player/ClosetPlayer_BP"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	// use our custom HUD class when we create one
	//HUDClass = APlayerHUD::StaticClass();
}





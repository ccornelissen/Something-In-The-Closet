// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Project.h"
#include "ClosetMonster.h"
#include "ClosetMonsterAI.h"


FVector AClosetMonsterAI::GetSpawnLocation()
{
	AClosetMonster* ControlledMonster = Cast<AClosetMonster>(GetPawn());

	if (ControlledMonster != nullptr)
	{
		return ControlledMonster->SpawnLocation;
	}
	else
	{
		return FVector::ZeroVector;
	}
}


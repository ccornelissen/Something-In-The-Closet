// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Project.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/ClosetPlayer.h"
#include "CheckPlayerState.h"


EBTNodeResult::Type UCheckPlayerState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the blackboard component
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	AClosetPlayer* Player = Cast<AClosetPlayer>(BlackboardComp->GetValueAsObject(PlayerKey.SelectedKeyName));

	if (Player->CurrentPlayerState == EPlayerState::CP_InBedSafe)
	{
		BlackboardComp->SetValueAsBool(IsPlayerInBedKey.SelectedKeyName, true);
	}
	else
	{
		BlackboardComp->SetValueAsBool(IsPlayerInBedKey.SelectedKeyName, false);
	}

	return EBTNodeResult::Succeeded;
}



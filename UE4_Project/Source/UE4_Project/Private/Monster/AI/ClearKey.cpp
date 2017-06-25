// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Project.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ClearKey.h"

EBTNodeResult::Type UClearKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the blackboard component
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	BlackboardComp->ClearValue(KeyToClear.SelectedKeyName);

	return EBTNodeResult::Succeeded;
}



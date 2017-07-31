// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_Project.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ClosetMonster.h"
#include "AIController.h"
#include "PatrolPointsComponent.h"
#include "ChooseNextWaypoint.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the blackboard component
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	//Get the current waypoint the AI is on 
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	//Get a reference to the controlled monster pawn
	AClosetMonster* ControlMonster = Cast<AClosetMonster>(OwnerComp.GetAIOwner()->GetPawn());

	if (!ensure(ControlMonster))
	{
		return EBTNodeResult::Failed;
	}

	if (ControlMonster->PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Monster patrol points are not set on the spawner!"));
	}

	int32 NextPoint = FMath::RandRange(0, (ControlMonster->PatrolPoints.Num() - 1));

	while (Index == NextPoint)
	{
		NextPoint = FMath::RandRange(0, (ControlMonster->PatrolPoints.Num() - 1));
	}

	if (ControlMonster->PatrolPoints[Index] != nullptr)
	{
		BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, ControlMonster->PatrolPoints[Index]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Monster patrol has an empty array element, check the spawner!"));
		return EBTNodeResult::Failed;
	}
	
	//Iterate to the next waypoint number
	Index = NextPoint;

	//Update the set waypoint
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);

	return EBTNodeResult::Succeeded;
}



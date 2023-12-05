// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "WC_CharacterBase.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	// behavior tree node name
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	if(OwnerComp.GetAIOwner() == nullptr) { return EBTNodeResult::Failed; }
	
	AWC_CharacterBase* Character = Cast<AWC_CharacterBase>(OwnerComp.GetAIOwner()->GetPawn());

	if(Character == nullptr) { return EBTNodeResult::Failed; }

	// fire magic projectile
	Character->ShootMagic();
	
	return EBTNodeResult::Succeeded;
}

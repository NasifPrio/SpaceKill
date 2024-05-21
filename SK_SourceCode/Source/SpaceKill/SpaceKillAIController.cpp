// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceKillAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SpaceKillCharacter.h"


void ASpaceKillAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr) 
	{
		RunBehaviorTree(AIBehavior);

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void ASpaceKillAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	/*APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (LineOfSightTo(PlayerPawn)) 
	{
		//Set PLayerLocation
		//Set LastKnownPlayerLocation
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());

	} else {
		//Clear PLayerLocation
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}*/
}

bool ASpaceKillAIController::IsDead() const
{
	ASpaceKillCharacter* ControlledCharacter =  Cast<ASpaceKillCharacter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}

	return true;
}

// Copyright 2020 Michael Palmer & Paradigm Game Studios


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

		//GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (LineOfSightTo(PlayerPawn))
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
		
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
		GetBlackboardComponent()->ClearValue(TEXT("LastKnownPlayerLocation"));
	}

	//if (LineOfSightTo(PlayerPawn))
	//{
	//	MoveToActor(PlayerPawn, AcceptanceRadius);
	//	SetFocus(PlayerPawn);
	//}
	//else
	//{
	//	ClearFocus(EAIFocusPriority::Gameplay);
	//	StopMovement();
	//}
}
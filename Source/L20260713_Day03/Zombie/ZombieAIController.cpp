// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


AZombieAIController::AZombieAIController()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	SetPerceptionComponent(*Perception.Get());

	UAISenseConfig_Sight* Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	Sight->SightRadius = 500.0f;
	Sight->LoseSightRadius = 600.0f;
	Sight->PeripheralVisionAngleDegrees = 60.0f;
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());
}

void AZombieAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (RunTree)
	{
		RunBehaviorTree(RunTree);
	}

	UE_LOG(LogTemp, Warning, TEXT("Perception %x"), GetPerceptionComponent());

	if (Perception)
	{
		UE_LOG(LogTemp, Warning, TEXT("Add %x"), GetPerceptionComponent());

		Perception->OnTargetPerceptionForgotten.AddDynamic(this, &AZombieAIController::OnActorPerceptionForgetUpdated);

		Perception->OnPerceptionUpdated.AddDynamic(this, &AZombieAIController::OnPerceptionUpdated);

		Perception->OnTargetPerceptionUpdated.AddDynamic(this, &AZombieAIController::OnActorPerceptionUpdated);

		Perception->OnTargetPerceptionInfoUpdated.AddDynamic(this, &AZombieAIController::OnPerceptionInfoUpdated);
	}


	SetGenericTeamId(3);


}

void AZombieAIController::OnUnPossess()
{
	BrainComponent->StopLogic(TEXT("UnPossess"));

	Super::OnUnPossess();
}

void AZombieAIController::BeginPlay()
{
	Super::BeginPlay();


}

void AZombieAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	UE_LOG(LogTemp, Warning, TEXT("OnPerceptionUpdated Update"));

}

void AZombieAIController::OnActorPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogTemp, Warning, TEXT("OnActorPerceptionUpdated Update %s"), *Actor->GetName());
}

void AZombieAIController::OnActorPerceptionForgetUpdated(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Perception Forgotten %s"), *Actor->GetName());
}

void AZombieAIController::OnPerceptionInfoUpdated(const FActorPerceptionUpdateInfo& UpdateInfo)
{
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMyCharacter* Character = Cast<AMyCharacter>(TryGetPawnOwner());
	if (Character)
	{
		Speed = Character->GetCharacterMovement()->Velocity.Size2D();
		Direction = CalculateDirection(Character->GetCharacterMovement()->Velocity, Character->GetActorRotation());
		//bArmed = Character->bArmed;
	}
}

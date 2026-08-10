// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPC.h"
#include "Kismet/KismetSystemLibrary.h"


void ALobbyPC::BeginPlay()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ALobbyPC::BeginPlay Begin"));

	Super::BeginPlay();

	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ALobbyPC::BeginPlay End"));
}

void ALobbyPC::OnPossess(APawn* aPawn)
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ALobbyPC::OnPossess Begin"));

	Super::OnPossess(aPawn);

	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ALobbyPC::OnPossess End"));
}

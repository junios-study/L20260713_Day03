// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPC.h"

void ALobbyPC::BeginPlay()
{
	Super::BeginPlay();



	UE_LOG(LogTemp, Warning, TEXT("Lobby %d"), GetNetMode());
}

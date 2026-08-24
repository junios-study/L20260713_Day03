// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGM.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LobbyGS.h"

void ALobbyGM::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	//UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ALobbyGM::PreLogin Begin"));

	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	//UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ALobbyGM::PreLogin End"));
}

APlayerController* ALobbyGM::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	//UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ALobbyGM::Login Begin"));

	APlayerController* PC =  Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	//UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ALobbyGM::Login End"));

	return PC;
}

void ALobbyGM::PostLogin(APlayerController* NewPlayer)
{
	//UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ALobbyGM::PostLogin Begin"));

	Super::PostLogin(NewPlayer);

	CountConnection();
	//UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ALobbyGM::PostLogin End"));

}

void ALobbyGM::Logout(AController* Exiting)
{
	//UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ALobbyGM::Logout Begin"));
	
	Super::Logout(Exiting);

	CountConnection();

	//UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ALobbyGM::Logout End"));
}

void ALobbyGM::StartPlay()
{
	//UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ALobbyGM::StartPlay Begin"));

	Super::StartPlay();

	//UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ALobbyGM::StartPlay End"));
}

void ALobbyGM::CountConnection()
{
	int Count = GetNumPlayers();
	//for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	//{
	//	Count++;
	//}

	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		GS->ConnectionCount = Count;
	}
}

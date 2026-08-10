// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidgetBase.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "../DataGameInstanceSubsystem.h"

void UTitleWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartServerButton)
	{
		StartServerButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::StartServer);
	}

	if (ConnectServerButton)
	{
		ConnectServerButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::ConnectServer);
	}
}

void UTitleWidgetBase::StartServer()
{
	SaveData();

	UGameplayStatics::OpenLevel(GetWorld(),
		TEXT("Lobby"),
		true,
		TEXT("Listen")
	);
}

void UTitleWidgetBase::ConnectServer()
{
	SaveData();

	UGameplayStatics::OpenLevel(GetWorld(),
		FName(ServerIP->GetText().ToString()),
		true,
		TEXT("Key=100")
	);
}

void UTitleWidgetBase::SaveData()
{
	UGameInstance* GI = UGameplayStatics::GetGameInstance(GetWorld());
	if (GI)
	{
		UDataGameInstanceSubsystem* MySubSystem = GI->GetSubsystem<UDataGameInstanceSubsystem>();
		if (MySubSystem)
		{
			MySubSystem->UserID = UserID->GetText().ToString();
			MySubSystem->Password = Password->GetText().ToString();
			MySubSystem->ServerIP = ServerIP->GetText().ToString();
		}
	}
}

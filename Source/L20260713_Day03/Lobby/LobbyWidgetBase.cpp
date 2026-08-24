// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidgetBase.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "LobbyWidgetBase.h"
#include "LobbyPC.h"


void ULobbyWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
}

void ULobbyWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &ULobbyWidgetBase::ProcessStartServer);
	}

	if (ChatButton)
	{
		ChatButton->OnClicked.AddDynamic(this, &ULobbyWidgetBase::ProcessSendMessage);
	}

	if (ChatInput)
	{
		ChatInput->OnTextChanged.AddDynamic(this, &ULobbyWidgetBase::ProcessTextChanged);
		ChatInput->OnTextCommitted.AddDynamic(this, &ULobbyWidgetBase::ProcessTextCommited);
	}

}

void ULobbyWidgetBase::ShowStartButton(bool IsShow)
{
	PlayShowStartButton();
}

void ULobbyWidgetBase::PlayShowStartButton_Implementation()
{
}

void ULobbyWidgetBase::ProcessTextCommited(const FText& Text, ETextCommit::Type CommitMethod)
{
	switch (CommitMethod)
	{
		case ETextCommit::OnEnter:
		{
			ALobbyPC* PC = Cast<ALobbyPC>(GetOwningPlayer());
			if (PC)
			{
				PC->C2S_SendMessage(Text);
				ChatInput->SetText(FText::FromString(TEXT("")));
			}
		}
		break;

		case ETextCommit::OnCleared:
		{
			ChatInput->SetUserFocus(GetOwningPlayer());
		}
		break;
	}

}

void ULobbyWidgetBase::ProcessTextChanged(const FText& Text)
{
}

void ULobbyWidgetBase::ProcessStartServer()
{
}

void ULobbyWidgetBase::ProcessSendMessage()
{
}

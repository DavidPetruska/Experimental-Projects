// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "WarGamesGameMode.h"
#include "WarGamesHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWarGamesGameMode::AWarGamesGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Character/Ue4ASP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AWarGamesHUD::StaticClass();
}

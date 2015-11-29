// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "UnrealRpg.h"
#include "UnrealRpgGameMode.h"
#include "UnrealRpgCharacter.h"

AUnrealRpgGameMode::AUnrealRpgGameMode()
{
	// Set the default player pawn
	// Failsafe
	DefaultPawnClass = AUnrealRpgPlayerCharacter::StaticClass();
	// Blueprinted Version, relies on the asset path obtained from the editor
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(*FURLs::DefaultPlayerCharacterBP);
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	// set the default player controller
	PlayerControllerClass = AUnrealRpgPlayerController::StaticClass();
}

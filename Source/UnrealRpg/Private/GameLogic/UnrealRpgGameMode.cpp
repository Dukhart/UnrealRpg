// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "UnrealRpg.h"
#include "UnrealRpgGameMode.h"
// includes for our custom classes
#include "UnrealRpgPlayerCharacter.h"
#include "UnrealRpgPlayerController.h"
#include "UnrealRpgHUD.h"


AUnrealRpgGameMode::AUnrealRpgGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
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
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBpClass(*FURLs::DefaultPlayerControllerBp);
	if (PlayerControllerBpClass.Class != NULL) {
		PlayerControllerClass = PlayerControllerBpClass.Class;
	}
	HUDClass = AUnrealRpgHUD::StaticClass();
}

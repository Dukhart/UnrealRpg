// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "UnrealRpg.h"
#include "UnrealRpgGameMode.h"
// includes for our custom classes
#include "UnrealRpgPlayerCharacter.h"
#include "UnrealRpgPlayerController.h"
#include "UnrealRpgHUD.h"


AURpg_GameMode::AURpg_GameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	// Set the default player pawn
	// Failsafe
	DefaultPawnClass = AURpg_PlayerCharacter::StaticClass();
	// Blueprinted Version, relies on the asset path obtained from the editor
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(*FURpg_BpAsset_Paths::DefaultPlayerCharacterBP);
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	// set the default player controller
	PlayerControllerClass = AURpg_PlayerController::StaticClass();
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBpClass(*FURpg_BpAsset_Paths::DefaultPlayerControllerBp);
	if (PlayerControllerBpClass.Class != NULL) {
		PlayerControllerClass = PlayerControllerBpClass.Class;
	}
	HUDClass = AURpg_HUD::StaticClass();
}

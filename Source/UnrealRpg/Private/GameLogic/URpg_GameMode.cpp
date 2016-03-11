// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#include "UnrealRpg.h"
#include "URpg_GameMode.h"
// includes for our custom classes
#include "URpg_PlayerCharacter.h"
#include "URpg_PlayerController.h"
#include "URpg_HUD.h"


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

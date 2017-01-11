// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealRpg.h"
#include "URpg_MainMenu_Pawn.h"
#include "URpg_MainMenu_Controller.h"
#include "URpg_MainMenu_GameMode.h"




AURpg_MainMenu_GameMode::AURpg_MainMenu_GameMode(const FObjectInitializer& Objectinitializer)
	: Super(Objectinitializer) {
	// Set Default Pawn
	DefaultPawnClass = AURpg_MainMenu_Pawn::StaticClass();
	// Set Default Controller
	PlayerControllerClass = AURpg_MainMenu_Controller::StaticClass();
}

void AURpg_MainMenu_GameMode::PostLogin(APlayerController* NewPlayer) {
	Super::PostLogin(NewPlayer);
	if (NewPlayer != nullptr) {
		AURpg_MainMenu_Controller* player = Cast<AURpg_MainMenu_Controller>(NewPlayer);
		if (player != nullptr) {
			player->PostLoginEvents();
		}
	}
}
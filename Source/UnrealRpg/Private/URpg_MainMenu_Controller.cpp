// Fill out your copyright notice in the Description page of Project Settings.
#include "URpg_MainMenu_Controller.h"
#include "URpg_GameInstance.h"

AURpg_MainMenu_Controller::AURpg_MainMenu_Controller(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	// enable the mouse cursor
	//ShowCursor(true);
	bEnableClickEvents = true;
}

void AURpg_MainMenu_Controller::PostLoginEvents() {
	// load the hud
	LoadHUD();
}
// loads the Main menu UI
void AURpg_MainMenu_Controller::LoadHUD_Implementation() {
	// check for a valid template
	if (HUD_Template->IsChildOf<UURpg_Base_UserWidget>()) {
		// get the game instance
		UURpg_GameInstance* GI = Cast<UURpg_GameInstance>(GetGameInstance());
		if (GI != nullptr) {
			// create the hud
			HUD_Instance = CreateWidget<UURpg_Base_UserWidget>(GI, HUD_Template);
			if (HUD_Instance != nullptr) {
				// set and buid default params
				HUD_Instance->Owner = this;
				HUD_Instance->BuildDefaults();
				// add the hud to the viewport
				HUD_Instance->AddToViewport();
				// return true for successfully adding the HUD
				return;
			}
		}
	}
	// TODO :: ADD failure to load HUD error
}
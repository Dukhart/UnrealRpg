// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "URpg_Base_UserWidget.h"
#include "URpg_MainMenu_Controller.generated.h"



/**
 * 
 */
UCLASS()
class UNREALRPG_API AURpg_MainMenu_Controller : public APlayerController
{
	GENERATED_BODY()
	
public:
	AURpg_MainMenu_Controller(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	// setup behavior to run after the controller is fully loaded by the game
	UFUNCTION()
	virtual void PostLoginEvents();
protected:
	// load HUD
	UFUNCTION(Client, Reliable)
		void LoadHUD();
	virtual void LoadHUD_Implementation();
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UURpg_Base_UserWidget> HUD_Template;
	UPROPERTY()
		UURpg_Base_UserWidget* HUD_Instance;
	

};

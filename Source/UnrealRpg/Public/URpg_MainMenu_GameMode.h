// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "URpg_MainMenu_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API AURpg_MainMenu_GameMode : public AGameMode
{
	GENERATED_BODY()
		// * INITIALIZATION * //
		AURpg_MainMenu_GameMode(const FObjectInitializer& Objectinitializer = FObjectInitializer::Get());
protected:
	// Player Login
	virtual void PostLogin(APlayerController* NewPlayer) override;
	
};

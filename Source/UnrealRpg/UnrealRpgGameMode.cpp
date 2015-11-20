// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "UnrealRpg.h"
#include "UnrealRpgGameMode.h"
#include "UnrealRpgCharacter.h"

AUnrealRpgGameMode::AUnrealRpgGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(*FURLs::DefaultPlayerCharacterBP);
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

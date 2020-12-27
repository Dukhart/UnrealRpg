// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#pragma once

#include "URpg_BpAsset_Paths.generated.h"


USTRUCT()
struct UNREALRPG_API FURpg_BpAsset_Paths
{
	GENERATED_USTRUCT_BODY()
public:
	// * PLAYER ASSETS * //
	// Default Player assets
	static const FString DefaultPlayerCharacterBP;
	static const FString DefualtPlayerAnimationBP;
	static const FString DefaultPlayerControllerBp;
	static const FString DefaultPlayerCameraManagerBp;
	static const FString DefaultHUD;

};

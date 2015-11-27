// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "URLs.generated.h"
/**
 * 
 */
USTRUCT()
struct UNREALRPG_API FURLs
{
	GENERATED_USTRUCT_BODY()
public:
	// Default Player assets
	static const FString DefaultPlayerCharacterBP;
	static const FString DefaultPlayerCharacterMesh;
	static const FString DefualtPlayerAnimationBP;
	static const FString DefaultPlayerControllerBp;
	static const FString DefaultPlayerCameraManagerBp;
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealRpg.h"
#include "URLs.h"


// Default Player Assets
const FString FURLs::DefaultPlayerCharacterBP = FString("APlayerCharacter'/Game/Blueprints/Characters/Player/Human/Male/BasicMale/PlayerCharacterBasicMaleBP.PlayerCharacterBasicMaleBP_C'");
const FString FURLs::DefaultPlayerCharacterMesh = FString("SkeletalMesh'/Game/Characters/Humanoid/Human/Male/BasicMale.BasicMale'");
const FString FURLs::DefualtPlayerAnimationBP = FString("AnimBlueprint'/Game/Blueprints/Animation/Humaniod/Male/BasicMale/BasicMale_AnimBP.BasicMale_AnimBP_C'");
const FString FURLs::DefaultPlayerControllerBp = FString("AUnrealRpgPlayerController'/Game/Blueprints/GameLogic/Player/UnrealRpgPlayerControllerBp.UnrealRpgPlayerControllerBp_C'");
const FString FURLs::DefaultPlayerCameraManagerBp = FString("AUnrealRpgPlayerCameraManager'/Game/Blueprints/GameLogic/Player/UnrealRpgPlayerCameraManagerBp.UnrealRpgPlayerCameraManagerBp_C'");
// Default HUD assets
const FString FURLs::DefaultCrosshiarTexture = FString("Texture2D'/Game/Textures/HUD/FirstPersonCrosshair.FirstPersonCrosshair'");
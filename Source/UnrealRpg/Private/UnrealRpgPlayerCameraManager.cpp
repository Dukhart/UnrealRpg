// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealRpg.h"
#include "UnrealRpgPlayerCameraManager.h"




AUnrealRpgPlayerCameraManager::AUnrealRpgPlayerCameraManager() {
	eDefaultCameraMode = ECameraMode::OverShoulder;
	eCurrentCameraMode = eDefaultCameraMode;
}
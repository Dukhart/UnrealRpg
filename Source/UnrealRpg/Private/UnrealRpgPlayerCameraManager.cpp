// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealRpg.h"
#include "UnrealRpgPlayerCameraManager.h"




AUnrealRpgPlayerCameraManager::AUnrealRpgPlayerCameraManager() {
	eDefaultCameraMode = ECameraMode::OverShoulder;
	fixedCamera = false;
	//eCurrentCameraMode = eDefaultCameraMode;
}
void AUnrealRpgPlayerCameraManager::BeginPlay() {
	Super::BeginPlay();
	eCurrentCameraMode = eDefaultCameraMode;
	switch (eCurrentCameraMode) {
	case ECameraMode::FirstPerson:
		Cast<AUnrealRpgPlayerController>(GetOwningPlayerController())->ActivateFirstPersonCamera();
		break;
	case ECameraMode::OverShoulder:
		Cast<AUnrealRpgPlayerController>(GetOwningPlayerController())->ActivateOverShoulderCamera();
		break;
	case ECameraMode::FreeRange:
		Cast<AUnrealRpgPlayerController>(GetOwningPlayerController())->ActivateFreeRangeCamera();
		break;
	case ECameraMode::SkyViewCamera:
		Cast<AUnrealRpgPlayerController>(GetOwningPlayerController())->ActivateSkyViewCamera();
		break;
	case ECameraMode::FreeCamera:
		Cast<AUnrealRpgPlayerController>(GetOwningPlayerController())->ActivateFreeCamera();
		break;
	default:
		break;
	}
	Cast<AUnrealRpgPlayerController>(GetOwningPlayerController())->ActivateFreeRangeCamera();
}
// Get and Set functions for eCurrentCameraMode 
void AUnrealRpgPlayerCameraManager::SetCameraMode(ECameraMode newCameraMode) {
	eCurrentCameraMode = newCameraMode;
}
ECameraMode AUnrealRpgPlayerCameraManager::GetCameraMode() {
	return eCurrentCameraMode;
}
// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#include "UnrealRpg.h"
#include "URpg_PlayerCameraManager.h"
// includes for custom classes
#include "URpg_PlayerController.h"



AURpg_PlayerCameraManager::AURpg_PlayerCameraManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	eDefaultCameraMode = ECameraMode::OverShoulder;
	fixedCamera = false;
	//eCurrentCameraMode = eDefaultCameraMode;
}

void AURpg_PlayerCameraManager::BeginPlay() {
	Super::BeginPlay();
	eCurrentCameraMode = eDefaultCameraMode;
	switch (eCurrentCameraMode) {
	case ECameraMode::FirstPerson:
		Cast<AURpg_PlayerController>(GetOwningPlayerController())->ActivateFirstPersonCamera();
		break;
	case ECameraMode::OverShoulder:
		Cast<AURpg_PlayerController>(GetOwningPlayerController())->ActivateOverShoulderCamera();
		break;
	case ECameraMode::FreeRange:
		Cast<AURpg_PlayerController>(GetOwningPlayerController())->ActivateFreeRangeCamera();
		break;
	case ECameraMode::SkyViewCamera:
		Cast<AURpg_PlayerController>(GetOwningPlayerController())->ActivateSkyViewCamera();
		break;
	case ECameraMode::FreeCamera:
		Cast<AURpg_PlayerController>(GetOwningPlayerController())->ActivateFreeCamera();
		break;
	default:
		break;
	}
	Cast<AURpg_PlayerController>(GetOwningPlayerController())->ActivateFreeRangeCamera();
}
// Get and Set functions for eCurrentCameraMode 
void AURpg_PlayerCameraManager::SetCameraMode(ECameraMode newCameraMode) {
	eCurrentCameraMode = newCameraMode;
}
ECameraMode AURpg_PlayerCameraManager::GetCameraMode() {
	return eCurrentCameraMode;
}

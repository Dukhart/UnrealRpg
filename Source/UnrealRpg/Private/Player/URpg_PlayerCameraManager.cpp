// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#include "UnrealRpg.h"
#include "URpg_PlayerCameraManager.h"
// includes for custom classes
#include "URpg_PlayerController.h"


// * INTITIALIZATION * //
// Constructor
AURpg_PlayerCameraManager::AURpg_PlayerCameraManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	eDefaultCameraMode = ECameraMode::FreeRange;
	//fixedCamera = true;
	eCurrentCameraMode = ECameraMode::None;
}
// called after the constructor
// world and component dependent starting behavior should go here
void AURpg_PlayerCameraManager::BeginPlay() {
	Super::BeginPlay();
	// activate our default camera mode
	Cast<AURpg_PlayerController>(GetOwningPlayerController())->ActivateCameraMode(eDefaultCameraMode);

	//eCurrentCameraMode = eDefaultCameraMode;
	/*
	switch (eDefaultCameraMode) {
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
	*/
	//Cast<AURpg_PlayerController>(GetOwningPlayerController())->ActivateFreeRangeCamera();
}


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
	// ensure replicates is true
	bReplicates = true;
}
// set replicated properties
/*
void AURpg_PlayerCameraManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	//DOREPLIFETIME(AURpg_PlayerCameraManager, eDefaultCameraMode);
	//DOREPLIFETIME(AURpg_PlayerCameraManager, eCurrentCameraMode);
}
*/

// called after the constructor
// world and component dependent starting behavior should go here
void AURpg_PlayerCameraManager::BeginPlay() {
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Black, GetName());
	// activate our default camera mode
	InitDefaultCameraMode();
	
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

// activates our default camera mode
void AURpg_PlayerCameraManager::InitDefaultCameraMode() {
	if (Cast<AURpg_PlayerController>(GetOwningPlayerController())) {
		/* Debug helpers
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ECameraMode"), true);
		if (EnumPtr != nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Black, GetName() + " " + GetOwningPlayerController()->GetName() + " " + EnumPtr->GetNameByIndex(static_cast<uint8>(eDefaultCameraMode)).ToString());
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Black, GetName() + " " + GetOwningPlayerController()->GetName());
		}
		*/
		AURpg_PlayerController* controlRef = Cast<AURpg_PlayerController>(GetOwningPlayerController());
		if (controlRef != nullptr) {
			controlRef->ActivateCameraMode(eDefaultCameraMode);
		}
	}
	else if (GetWorld()) {
		// will re-call this function in 1 sec if it fails
		GetWorld()->GetTimerManager().SetTimer(InitCameraHandle, this, &AURpg_PlayerCameraManager::InitDefaultCameraMode, 1, false);
	}
}


// Copyright Jordan Duncan 2015 \\

#include "UnrealRpg.h"
#include "UnrealRpgPlayerController.h"



AUnrealRpgPlayerController::AUnrealRpgPlayerController() {
	PlayerCameraManagerClass = AUnrealRpgPlayerCameraManager::StaticClass();
}
void AUnrealRpgPlayerController::SetupInputComponent() {
	// Call Super Setup Input Component to get the InputCompent ready to Bind our custom Inputs
	Super::SetupInputComponent();
	// Check that the input component was succesfully Initialized
	check(InputComponent);
	if (InputComponent != NULL) {
		// Bind player input to the appropriate functions
		// Bind Input AXIS
		InputComponent->BindAxis("Move_Strafe", this, &AUnrealRpgPlayerController::MoveStrafe);
		InputComponent->BindAxis("Move_ForwardBackward", this, &AUnrealRpgPlayerController::MoveForwardBack);
		InputComponent->BindAxis("Look_UpDown", this, &AUnrealRpgPlayerController::LookUpDown);
		InputComponent->BindAxis("Look_RightLeft", this, &AUnrealRpgPlayerController::LookRightLeft);
		// Bind Input BUTTONS
	}
}

void AUnrealRpgPlayerController::MoveStrafe(float value) {

}
void AUnrealRpgPlayerController::MoveForwardBack(float value) {

}
void AUnrealRpgPlayerController::MoveJump(float value) {

}

void AUnrealRpgPlayerController::LookUpDown(float value) {

}
void AUnrealRpgPlayerController::LookRightLeft(float value) {

}

void AUnrealRpgPlayerController::ActivateFirstPersonCamera() {

}
void AUnrealRpgPlayerController::ActivateOverShoulderCamera() {

}
void AUnrealRpgPlayerController::ActivateFreeRangeCamera() {

}
void AUnrealRpgPlayerController::ActivateSkyViewCamera() {

}
void AUnrealRpgPlayerController::ActivateFreeCamera() {

}
// Copyright Jordan Duncan 2015 \\

#include "UnrealRpg.h"
#include "UnrealRpgPlayerController.h"



AUnrealRpgPlayerController::AUnrealRpgPlayerController() {
	PlayerCameraManagerClass = AUnrealRpgPlayerCameraManager::StaticClass();
	bInvertLookXAxis = false;
	bInvertLookYAxis = true;
	
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
	if (GetPawn() != NULL && value != 0.0f)
	{
		// find out which way is right
		const FRotator RotationControlSpace = GetControlRotation();
		const FRotator YawRotation(0, RotationControlSpace.Yaw, 0);
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		GetPawn()->AddMovementInput(Direction, value);
	}
	MoveValX = value;
}
void AUnrealRpgPlayerController::MoveForwardBack(float value) {
	if (GetPawn() != NULL && value != 0.0f) {
		// find out which way is forward
		const FRotator RotationControlSpace = GetControlRotation();
		const FRotator YawRotation(0, RotationControlSpace.Yaw, 0);
		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		//const FVector Direction = FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y)
		// transform to world space and add it
		GetPawn()->AddMovementInput(Direction, value);
	}
	MoveValY = value;
}
void AUnrealRpgPlayerController::MoveJump(float value) {

}

void AUnrealRpgPlayerController::LookUpDown(float value) {
	if (bInvertLookYAxis) {
		value *= -1.0f;
	}
	AddPitchInput(value);
	
}
void AUnrealRpgPlayerController::LookRightLeft(float value) {
	if (bInvertLookXAxis) {
		value *= -1.0f;
	}
	AddYawInput(value);
	
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
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
		FRotator RotationControlSpace;
		FRotator YawRotation;
		FVector Direction;
		ECameraMode eCurrentCameraRef = Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->GetCurrentCameraMode();

		switch (eCurrentCameraRef)
		{
		case ECameraMode::FirstPerson:
			break;
		case ECameraMode::OverShoulder:
			RotationControlSpace = PlayerCameraManager->GetCameraRotation();
			YawRotation = FRotator(0, RotationControlSpace.Yaw, 0);
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			GetPawn()->SetActorRotation(YawRotation);
			GetPawn()->AddMovementInput(Direction, value);
			MoveValX = value;
			break;
		case ECameraMode::FreeRange:
			break;
		case ECameraMode::SkyViewCamera:
			break;
		case ECameraMode::FreeCamera:
			break;
		default:
			break;
		}
	}
	else
	{
		MoveValX = value;
	}
}
void AUnrealRpgPlayerController::MoveForwardBack(float value) {
	if (GetPawn() != NULL && value != 0.0f) {
		FRotator RotationControlSpace;
		FRotator YawRotation;
		FVector Direction;

		ECameraMode eCurrentCameraRef = Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->GetCurrentCameraMode();
		
		switch (eCurrentCameraRef)
		{
		case ECameraMode::FirstPerson:
			break;
		case ECameraMode::OverShoulder:
			RotationControlSpace = PlayerCameraManager->GetCameraRotation();
			YawRotation = FRotator(0, RotationControlSpace.Yaw, 0);
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			GetPawn()->SetActorRotation(YawRotation);
			GetPawn()->AddMovementInput(Direction, value);
			MoveValY = value;
			break;
		case ECameraMode::FreeRange:
			break;
		case ECameraMode::SkyViewCamera:
			break;
		case ECameraMode::FreeCamera:
			break;
		default:
			break;
		}
	}
	else
	{
		MoveValY = value;
	}
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
// Activates the chosen camera mode
void AUnrealRpgPlayerController::ActivateFirstPersonCamera() {
	GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
	Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::FirstPerson);
}
void AUnrealRpgPlayerController::ActivateOverShoulderCamera() {
	if (GetCharacter() != NULL) {
		GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::OverShoulder);
	if (GetPawn() != NULL) {
		APawn* pawnRef = GetPawn();
		pawnRef->bUseControllerRotationPitch = false;
		pawnRef->bUseControllerRotationYaw = false;
		pawnRef->bUseControllerRotationRoll = false;
	}
}
void AUnrealRpgPlayerController::ActivateFreeRangeCamera() {
	GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
	Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::FreeRange);
}
void AUnrealRpgPlayerController::ActivateSkyViewCamera() {
	GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
	Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::SkyViewCamera);
}
void AUnrealRpgPlayerController::ActivateFreeCamera() {
	GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
	Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::FreeCamera);
}
// Copyright Jordan Duncan 2015 \\

#include "UnrealRpg.h"
#include "UnrealRpgPlayerController.h"


// Constructor
AUnrealRpgPlayerController::AUnrealRpgPlayerController() {
	/* Sets the player camera manager
	* @param fail safe assigns the player camera manager to the c++ template
	* @param attempts to find blueprint based off of c++ template and assign it as the camera manager
	*/
	PlayerCameraManagerClass = AUnrealRpgPlayerCameraManager::StaticClass();
	static ConstructorHelpers::FClassFinder<APlayerCameraManager> PlayerCameraManagerBpClass(*FURLs::DefaultPlayerCameraManagerBp);
	if (PlayerCameraManagerBpClass.Class != NULL) {
		PlayerCameraManagerClass = PlayerCameraManagerBpClass.Class;
	}
	// sets the default invert look params
	bInvertLookXAxis = false;
	bInvertLookYAxis = true;
}
// Binds user input to functions
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
// activated when the controller spawns
void AUnrealRpgPlayerController::BeginPlay() {
	Super::BeginPlay();
	// set the active camera mode
	ECameraMode eCameraRef = Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->GetCameraMode();
	switch (eCameraRef)
	{
	case ECameraMode::FirstPerson:
		ActivateFirstPersonCamera();
		break;
	case ECameraMode::OverShoulder:
		ActivateOverShoulderCamera();
		break;
	case ECameraMode::FreeRange:
		ActivateFreeRangeCamera();
		break;
	case ECameraMode::SkyViewCamera:
		ActivateSkyViewCamera();
		break;
	case ECameraMode::FreeCamera:
		ActivateFreeCamera();
		break;
	default:
		break;
	}
}
// INPUT
// Handles moving the player in a strafing manner
void AUnrealRpgPlayerController::MoveStrafe(float value) {
	if (GetPawn() != NULL && value != 0.0f)
	{
		FRotator RotationControlSpace;
		FRotator YawRotation;
		FVector Direction;
		ECameraMode eCurrentCameraRef = Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->GetCameraMode();

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
// Handles Forward and Back input
void AUnrealRpgPlayerController::MoveForwardBack(float value) {
	if (GetPawn() != NULL && value != 0.0f) {
		FRotator RotationControlSpace;
		FRotator YawRotation;
		FVector Direction;

		ECameraMode eCurrentCameraRef = Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->GetCameraMode();
		
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
// CAMERA
// Activates First Person Camera
void AUnrealRpgPlayerController::ActivateFirstPersonCamera() {
	GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
	Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::FirstPerson);
}
// Activates Over the Shoulder Camera
void AUnrealRpgPlayerController::ActivateOverShoulderCamera() {
	Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::OverShoulder);
	if (GetCharacter() != NULL && GetPawn() != NULL) {
		APawn* pawnRef = GetPawn();
		GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
		pawnRef->bUseControllerRotationPitch = false;
		pawnRef->bUseControllerRotationYaw = false;
		pawnRef->bUseControllerRotationRoll = false;
	}
}
// Activates Free Range Camera
void AUnrealRpgPlayerController::ActivateFreeRangeCamera() {
	GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
	Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::FreeRange);
}
// Activates Skyview Camera
void AUnrealRpgPlayerController::ActivateSkyViewCamera() {
	GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
	Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::SkyViewCamera);
}
// Activates Free Camera
void AUnrealRpgPlayerController::ActivateFreeCamera() {
	GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
	Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::FreeCamera);
}
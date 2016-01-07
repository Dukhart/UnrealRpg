// Copyright Jordan Duncan 2015 \\

#include "UnrealRpg.h"
#include "UnrealRpgPlayerController.h"


// Constructor
AUnrealRpgPlayerController::AUnrealRpgPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	/* Sets the player camera manager
	* @param fail safe assigns the player camera manager to the c++ template
	* @param attempts to find blueprint based off of c++ template and assign it as the camera manager
	*/
	PlayerCameraManagerClass = AUnrealRpgPlayerCameraManager::StaticClass();
	static ConstructorHelpers::FClassFinder<APlayerCameraManager> PlayerCameraManagerBpClass(*FURLs::DefaultPlayerCameraManagerBp);
	if (PlayerCameraManagerBpClass.Class != NULL) {
		PlayerCameraManagerClass = PlayerCameraManagerBpClass.Class;
	}
	// sets the default look params
	bInvertLookXAxis = false;
	bInvertLookYAxis = true;
	baseTurnRate = 45.0f;
	baseLookRate = 45.0f;
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
		InputComponent->BindAxis("Look_UpDownRate", this, &AUnrealRpgPlayerController::LookUpDownRate);
		InputComponent->BindAxis("Look_UpDown", this, &AUnrealRpgPlayerController::LookUpDown);
		InputComponent->BindAxis("Look_RightLeftRate", this, &AUnrealRpgPlayerController::LookRightLeftRate);
		InputComponent->BindAxis("Look_RightLeft", this, &AUnrealRpgPlayerController::LookRightLeft);
		// Bind Input BUTTONS
	}
}
// activated when the controller spawns
void AUnrealRpgPlayerController::BeginPlay() {
	Super::BeginPlay();
	// set the active camera mode
	/*
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
	*/
}
// INPUT
// Handles moving the player in a strafing manner
void AUnrealRpgPlayerController::MoveStrafe(float value) {
	ECameraMode eCurrentCameraRef = Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->GetCameraMode();
	if (GetPawn() != NULL && value != 0.0f)
	{
		FRotator RotationControlSpace;
		FRotator YawRotation;
		FVector Direction;
		
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
			RotationControlSpace = GetControlRotation();
			YawRotation = FRotator(0, RotationControlSpace.Yaw, 0);
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			GetPawn()->AddMovementInput(Direction, value);
			if (value < 0.0f) {
				value *= -1.0f;
			}
			MoveValX = value;
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
		MoveValX = 0.0f;
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
		case ECameraMode::OverShoulder: // Over the shoulder camera behavior for forward back input
			RotationControlSpace = PlayerCameraManager->GetCameraRotation();
			YawRotation = FRotator(0, RotationControlSpace.Yaw, 0);
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			GetPawn()->SetActorRotation(YawRotation);
			GetPawn()->AddMovementInput(Direction, value);
			MoveValY = value;
			break;
		case ECameraMode::FreeRange: // Free Range camera behavior for forward back input
			RotationControlSpace = GetControlRotation(); 
			YawRotation = FRotator(0, RotationControlSpace.Yaw, 0);
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			GetPawn()->AddMovementInput(Direction, value);
			// In free range mode when not locked on all move directions will be considered forward by the animator
			if (value < 0.0f) {
				value *= -1.0f;
			}
			MoveValY = value;
			if (Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->fixedCamera == false) {
				FRotator pawnRot = GetPawn()->GetActorRotation();
				FRotator cameraRotation = PlayerCameraManager->GetCameraRotation();
				if (pawnRot != cameraRotation) {


					AddYawInput(0.0f);
				}
			}
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
		MoveValY = 0.0f;
	}
}
void AUnrealRpgPlayerController::MoveJump(float value) {

}
void AUnrealRpgPlayerController::LookUpDownRate(float value) {
	if (bInvertLookYAxis) {
		value *= -1.0f;
	}
	// calculate delta for this frame from the rate information
	AddPitchInput(value * baseLookRate * GetWorld()->GetDeltaSeconds());
}
void AUnrealRpgPlayerController::LookUpDown(float value) {
	if (bInvertLookYAxis) {
		value *= -1.0f;
	}
	AddPitchInput(value);
}
void AUnrealRpgPlayerController::LookRightLeftRate(float value) {
	if (bInvertLookXAxis) {
		value *= -1.0f;
	}
	// calculate delta for this frame from the rate information
	AddYawInput(value * baseTurnRate * GetWorld()->GetDeltaSeconds());
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
	UE_LOG(InitLog, Warning, TEXT("ACTIVATING FirstPerson CameraMode"));
	Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::FirstPerson);
	if (GetCharacter() != NULL) {
		// get a refrence to the player character
		AUnrealRpgPlayerCharacter* characterRef = Cast<AUnrealRpgPlayerCharacter>(GetCharacter());
		if (Cast<USpringArmComponent>(characterRef->GetPlayerCamera()->GetAttachParent()) != characterRef->GetCameraBoom()) {
			// remove the camera from current parent
			characterRef->GetPlayerCamera()->DetachFromParent();
			UE_LOG(DebugLog, Warning, TEXT("attaching Cam to player pawn's Camera boom"));
			characterRef->GetPlayerCamera()->AttachTo(characterRef->GetCameraBoom(), USpringArmComponent::SocketName);
		}
		//characterRef->GetCharacterMovement()->bOrientRotationToMovement = false;
		//characterRef->bUseControllerRotationPitch = false;
		//characterRef->bUseControllerRotationYaw = false;
		//characterRef->bUseControllerRotationRoll = false;
	}
}
// Activates Over the Shoulder Camera
void AUnrealRpgPlayerController::ActivateOverShoulderCamera() {
	UE_LOG(InitLog, Warning, TEXT("ACTIVATING OverTheShoulder CameraMode"));
	Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::OverShoulder);
	if (GetCharacter() != NULL) {
		// get a refrence to the player character
		AUnrealRpgPlayerCharacter* characterRef = Cast<AUnrealRpgPlayerCharacter>(GetCharacter());
		if (Cast<USpringArmComponent>(characterRef->GetPlayerCamera()->GetAttachParent()) != characterRef->GetCameraBoom()) {
			// remove the camera from current parent
			characterRef->GetPlayerCamera()->DetachFromParent();
			UE_LOG(DebugLog, Warning, TEXT("attaching Cam to player pawn's Camera boom"));
			characterRef->GetPlayerCamera()->AttachTo(characterRef->GetCameraBoom(), USpringArmComponent::SocketName);
		}
		characterRef->GetCharacterMovement()->bOrientRotationToMovement = false;
		characterRef->bUseControllerRotationPitch = false;
		characterRef->bUseControllerRotationYaw = false;
		characterRef->bUseControllerRotationRoll = false;
	}
}
// Activates Free Range Camera
void AUnrealRpgPlayerController::ActivateFreeRangeCamera() {
	UE_LOG(InitLog, Warning, TEXT("ACTIVATING FreeRange CameraMode"));
	Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::FreeRange);
	if (GetCharacter() != NULL) {

		// get a refrence to the player character
		AUnrealRpgPlayerCharacter* characterRef = Cast<AUnrealRpgPlayerCharacter>(GetCharacter());
		
		if (Cast<USpringArmComponent>(characterRef->GetPlayerCamera()->GetAttachParent()) != characterRef->GetCameraBoom()) {
			// remove the camera from current parent
			characterRef->GetPlayerCamera()->DetachFromParent();
			UE_LOG(DebugLog, Warning, TEXT("attaching Cam to player pawn's Camera boom"));
			// attach the camera to the player pawn's camera boom
			characterRef->GetPlayerCamera()->AttachTo(characterRef->GetCameraBoom(), USpringArmComponent::SocketName);
		}
		characterRef->GetCharacterMovement()->bOrientRotationToMovement = true;
		characterRef->bUseControllerRotationPitch = false;
		characterRef->bUseControllerRotationYaw = false;
		characterRef->bUseControllerRotationRoll = false;
	}
}
// Activates Skyview Camera
void AUnrealRpgPlayerController::ActivateSkyViewCamera() {
	UE_LOG(InitLog, Warning, TEXT("ACTIVATING SkyView CameraMode"));
	Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::SkyViewCamera);
	if (GetCharacter() != NULL) {
		// get a refrence to the player character
		AUnrealRpgPlayerCharacter* characterRef = Cast<AUnrealRpgPlayerCharacter>(GetCharacter());
		if (Cast<USpringArmComponent>(characterRef->GetPlayerCamera()->GetAttachParent()) != characterRef->GetCameraBoom()) {
			// remove the camera from current parent
			characterRef->GetPlayerCamera()->DetachFromParent();
			UE_LOG(DebugLog, Warning, TEXT("attaching Cam to player pawn's Camera boom"));
			characterRef->GetPlayerCamera()->AttachTo(characterRef->GetCameraBoom(), USpringArmComponent::SocketName);
		}
		//characterRef->GetCharacterMovement()->bOrientRotationToMovement = false;
		//characterRef->bUseControllerRotationPitch = false;
		//characterRef->bUseControllerRotationYaw = false;
		//characterRef->bUseControllerRotationRoll = false;
	}
}
// Activates Free Camera
void AUnrealRpgPlayerController::ActivateFreeCamera() {
	UE_LOG(InitLog, Warning, TEXT("ACTIVATING FreeCameraMode"));
	Cast<AUnrealRpgPlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::FreeCamera);
	if (GetCharacter() != NULL) {
		// get a refrence to the player character
		AUnrealRpgPlayerCharacter* characterRef = Cast<AUnrealRpgPlayerCharacter>(GetCharacter());
		
		if (Cast<USpringArmComponent>(characterRef->GetPlayerCamera()->GetAttachParent()) == characterRef->GetCameraBoom()) {
			// remove the camera from current parent
			characterRef->GetPlayerCamera()->DetachFromParent();
			UE_LOG(DebugLog, Warning, TEXT("detaching Cam to player pawn's Camera boom"));
		}
		//characterRef->GetCharacterMovement()->bOrientRotationToMovement = false;
		//characterRef->bUseControllerRotationPitch = false;
		//characterRef->bUseControllerRotationYaw = false;
		//characterRef->bUseControllerRotationRoll = false;
	}
}
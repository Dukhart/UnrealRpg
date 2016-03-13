// Copyright Jordan Duncan 2015 \\ Description=RPG Template


#include "UnrealRpg.h"
#include "URpg_PlayerController.h"
// includes for our custom classes
#include "URpg_PlayerCharacter.h"


// * INTITIALIZATION * //
// Constructor
AURpg_PlayerController::AURpg_PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {

	/* Sets the player camera manager
	* @param fail safe assigns the player camera manager to the c++ template
	* @param attempts to find blueprint based off of c++ template and assign it as the camera manager
	*/
	PlayerCameraManagerClass = AURpg_PlayerCameraManager::StaticClass();
	static ConstructorHelpers::FClassFinder<APlayerCameraManager> PlayerCameraManagerBpClass(*FURpg_BpAsset_Paths::DefaultPlayerCameraManagerBp);
	if (PlayerCameraManagerBpClass.Class != nullptr) {
		PlayerCameraManagerClass = PlayerCameraManagerBpClass.Class;
	}
	// sets the default look params
	bInvertLookXAxis = false;
	bInvertLookYAxis = true;
	baseTurnRate = 45.0f;
	baseLookRate = 45.0f;
}
// Binds user input to functions
void AURpg_PlayerController::SetupInputComponent() {
	// Call Super Setup Input Component to get the InputCompent ready to Bind our custom Inputs
	Super::SetupInputComponent();
	// Check that the input component was succesfully Initialized
	check(InputComponent);
	if (InputComponent != nullptr) {
		// Bind player input to the appropriate functions
		// Bind Input AXIS
		InputComponent->BindAxis("Move_Strafe", this, &AURpg_PlayerController::MoveStrafe);
		InputComponent->BindAxis("Move_ForwardBackward", this, &AURpg_PlayerController::MoveForwardBack);
		InputComponent->BindAxis("Look_UpDownRate", this, &AURpg_PlayerController::LookUpDownRate);
		InputComponent->BindAxis("Look_UpDown", this, &AURpg_PlayerController::LookUpDown);
		InputComponent->BindAxis("Look_RightLeftRate", this, &AURpg_PlayerController::LookRightLeftRate);
		InputComponent->BindAxis("Look_RightLeft", this, &AURpg_PlayerController::LookRightLeft);
		// Bind Input BUTTONS
	}
}
// Called after the constructor
// World and component dependent starting behavior should go here
void AURpg_PlayerController::BeginPlay() {
	Super::BeginPlay();
}

// * INPUT * //
// Detect Character Movement Input on the X axis (Left / Right)
void AURpg_PlayerController::MoveStrafe(float value) {
	ECameraMode eCurrentCameraRef = Cast<AURpg_PlayerCameraManager>(PlayerCameraManager)->GetCameraMode();
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
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Green, FString("X move = " + FString::SanitizeFloat(MoveValX)));
}

// Detect Character Movement Input on the Y axis (Forward / Back)
void AURpg_PlayerController::MoveForwardBack(float value) {
	if (GetPawn() != nullptr && value != 0.0f) {
		FRotator RotationControlSpace;
		FRotator YawRotation;
		FVector Direction;

		ECameraMode eCurrentCameraRef = Cast<AURpg_PlayerCameraManager>(PlayerCameraManager)->GetCameraMode();
		
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
			// Pawn movement
			RotationControlSpace = GetControlRotation(); 
			YawRotation = FRotator(0, RotationControlSpace.Yaw, 0);
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			GetPawn()->AddMovementInput(Direction, value);

			// Pawn Animation
			// In free range mode when not locked on all move directions will be considered forward by the animator
			if (value < 0.0f) {
				value *= -1.0f;
			}
			MoveValY = value;

			/*
			if (Cast<AURpg_PlayerCameraManager>(PlayerCameraManager)->fixedCamera == false) {
			FRotator pawnRot = GetPawn()->GetActorRotation();
			FRotator cameraRotation = PlayerCameraManager->GetCameraRotation();
			if (GetPawn()->GetActorRotation() != PlayerCameraManager->GetCameraRotation()) {

				AddYawInput(0.0f);
			}
			}
			*/
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
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Green, FString("Y move = " + FString::SanitizeFloat(MoveValY)));
}

// Detect Jump Input
void AURpg_PlayerController::MoveJump(float value) {

}
// Detect Camera Movement Input on the Y Axis
void AURpg_PlayerController::LookUpDownRate(float value) {
	if (bInvertLookYAxis) {
		value *= -1.0f;
	}
	// calculate delta for this frame from the rate information
	AddPitchInput(value * baseLookRate * GetWorld()->GetDeltaSeconds());
}
// Detect Camera Movement Input on the Y Axis
void AURpg_PlayerController::LookUpDown(float value) {
	if (bInvertLookYAxis) {
		value *= -1.0f;
	}
	AddPitchInput(value);
}
// Detect Camera Movement Input on the X Axis
void AURpg_PlayerController::LookRightLeftRate(float value) {
	if (bInvertLookXAxis) {
		value *= -1.0f;
	}
	// calculate delta for this frame from the rate information
	AddYawInput(value * baseTurnRate * GetWorld()->GetDeltaSeconds());
}
// Detect Camera Movement Input on the X Axis
void AURpg_PlayerController::LookRightLeft(float value) {
	if (bInvertLookXAxis) {
		value *= -1.0f;
	}
	AddYawInput(value);
}
// * CAMERA * //
// Switch between Controller/Camera styles
void AURpg_PlayerController::ActivateCameraMode(ECameraMode newCameraMode) {
	AURpg_PlayerCameraManager* camManRef = Cast<AURpg_PlayerCameraManager>(PlayerCameraManager);
	// if the new camera mode is the same as our new camera mode return
	if (camManRef == nullptr || newCameraMode == camManRef->GetCameraMode()) {
		return;
	}
	switch (newCameraMode) {
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
#if !UE_BUILD_SHIPPING
		UE_LOG(GeneralLog, Warning, TEXT("Invalid Camera mode input: Activating backup FreeRangeMode"))
#endif // !UE_BUILD_SHIPPING
			ActivateFreeRangeCamera();
		break;
	}
	camManRef->SetCameraMode(newCameraMode);
}

// Activates First Person Camera Mode
void AURpg_PlayerController::ActivateFirstPersonCamera() {

#if !UE_BUILD_SHIPPING
	UE_LOG(InitLog, Log, TEXT("ACTIVATING FirstPerson CameraMode"));
#endif // !UE_BUILD_SHIPPING

	Cast<AURpg_PlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::FirstPerson);
	if (GetCharacter() != NULL) {
		// get a refrence to the player character
		AURpg_PlayerCharacter* characterRef = Cast<AURpg_PlayerCharacter>(GetCharacter());
		if (Cast<USpringArmComponent>(characterRef->GetPlayerCamera()->GetAttachParent()) != characterRef->GetCameraBoom()) {
			// remove the camera from current parent
			characterRef->GetPlayerCamera()->DetachFromParent();

#if !UE_BUILD_SHIPPING
			UE_LOG(DebugLog, Log, TEXT("ATTACHING Camera to player pawn's Camera boom"));
#endif // !UE_BUILD_SHIPPING

			characterRef->GetPlayerCamera()->AttachTo(characterRef->GetCameraBoom(), USpringArmComponent::SocketName);
		}
		//characterRef->GetCharacterMovement()->bOrientRotationToMovement = false;
		//characterRef->bUseControllerRotationPitch = false;
		//characterRef->bUseControllerRotationYaw = false;
		//characterRef->bUseControllerRotationRoll = false;
	}
}

// Activates Over the Shoulder Camera Mode
void AURpg_PlayerController::ActivateOverShoulderCamera() {

#if !UE_BUILD_SHIPPING
	UE_LOG(InitLog, Log, TEXT("ACTIVATING OverTheShoulder CameraMode"));
#endif // !UE_BUILD_SHIPPING

	Cast<AURpg_PlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::OverShoulder);
	if (GetCharacter() != NULL) {
		// get a refrence to the player character
		AURpg_PlayerCharacter* characterRef = Cast<AURpg_PlayerCharacter>(GetCharacter());
		if (Cast<USpringArmComponent>(characterRef->GetPlayerCamera()->GetAttachParent()) != characterRef->GetCameraBoom()) {
			// remove the camera from current parent
			characterRef->GetPlayerCamera()->DetachFromParent();

#if !UE_BUILD_SHIPPING
			UE_LOG(DebugLog, Log, TEXT("ATTACHING Camera to player pawn's Camera boom"));
#endif // !UE_BUILD_SHIPPING

			characterRef->GetPlayerCamera()->AttachTo(characterRef->GetCameraBoom(), USpringArmComponent::SocketName);
		}
		characterRef->GetCharacterMovement()->bOrientRotationToMovement = false;
		characterRef->bUseControllerRotationPitch = false;
		characterRef->bUseControllerRotationYaw = false;
		characterRef->bUseControllerRotationRoll = false;
	}
}

// Activates Free Range Camera Mode
void AURpg_PlayerController::ActivateFreeRangeCamera() {

#if !UE_BUILD_SHIPPING
	UE_LOG(InitLog, Log, TEXT("ACTIVATING FreeRange CameraMode"));
#endif // !UE_BUILD_SHIPPING
	
	Cast<AURpg_PlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::FreeRange);
	if (GetCharacter() != NULL) {

		// get a refrence to the player character
		AURpg_PlayerCharacter* characterRef = Cast<AURpg_PlayerCharacter>(GetCharacter());
		
		// see if we are not connected to the camera boom
		if (Cast<USpringArmComponent>(characterRef->GetPlayerCamera()->GetAttachParent()) != characterRef->GetCameraBoom()) {
			// remove the camera from current parent
			characterRef->GetPlayerCamera()->DetachFromParent();

#if !UE_BUILD_SHIPPING
			UE_LOG(DebugLog, Log, TEXT("ATTACHING Camera to player pawn's Camera boom"));
#endif // !UE_BUILD_SHIPPING

			// attach the camera to the player pawn's camera boom
			characterRef->GetPlayerCamera()->AttachTo(characterRef->GetCameraBoom(), USpringArmComponent::SocketName);
		}
		characterRef->GetCharacterMovement()->bOrientRotationToMovement = true;
		characterRef->bUseControllerRotationPitch = false;
		characterRef->bUseControllerRotationYaw = false;
		characterRef->bUseControllerRotationRoll = false;
	}
}

// Activates SkyView Camera Mode
void AURpg_PlayerController::ActivateSkyViewCamera() {

#if !UE_BUILD_SHIPPING
	UE_LOG(InitLog, Log, TEXT("ACTIVATING SkyView CameraMode"));
#endif // !UE_BUILD_SHIPPING
	
	Cast<AURpg_PlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::SkyViewCamera);
	if (GetCharacter() != NULL) {
		// get a refrence to the player character
		AURpg_PlayerCharacter* characterRef = Cast<AURpg_PlayerCharacter>(GetCharacter());
		if (Cast<USpringArmComponent>(characterRef->GetPlayerCamera()->GetAttachParent()) != characterRef->GetCameraBoom()) {
			// remove the camera from current parent
			characterRef->GetPlayerCamera()->DetachFromParent();

#if !UE_BUILD_SHIPPING
			UE_LOG(DebugLog, Log, TEXT("ATTACHING Camera to player pawn's Camera boom"));
#endif // !UE_BUILD_SHIPPING
			
			characterRef->GetPlayerCamera()->AttachTo(characterRef->GetCameraBoom(), USpringArmComponent::SocketName);
		}
		//characterRef->GetCharacterMovement()->bOrientRotationToMovement = false;
		//characterRef->bUseControllerRotationPitch = false;
		//characterRef->bUseControllerRotationYaw = false;
		//characterRef->bUseControllerRotationRoll = false;
	}
}

// Detaches camera and controls from player character, operates like a spectator
void AURpg_PlayerController::ActivateFreeCamera() {

#if !UE_BUILD_SHIPPING
	UE_LOG(InitLog, Log, TEXT("ACTIVATING FreeCameraMode"));
#endif // !UE_BUILD_SHIPPING
	
	Cast<AURpg_PlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::FreeCamera);
	if (GetCharacter() != NULL) {
		// get a refrence to the player character
		AURpg_PlayerCharacter* characterRef = Cast<AURpg_PlayerCharacter>(GetCharacter());
		
		if (Cast<USpringArmComponent>(characterRef->GetPlayerCamera()->GetAttachParent()) == characterRef->GetCameraBoom()) {
			// remove the camera from current parent
			characterRef->GetPlayerCamera()->DetachFromParent();

#if !UE_BUILD_SHIPPING
			UE_LOG(DebugLog, Log, TEXT("DETACHING Camera to player pawn's Camera boom"));
#endif // !UE_BUILD_SHIPPING
			
		}
		//characterRef->GetCharacterMovement()->bOrientRotationToMovement = false;
		//characterRef->bUseControllerRotationPitch = false;
		//characterRef->bUseControllerRotationYaw = false;
		//characterRef->bUseControllerRotationRoll = false;
	}
}

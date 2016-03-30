// Copyright Jordan Duncan 2015 \\ Description=RPG Template


#include "UnrealRpg.h"
#include "URpg_PlayerController.h"
// includes for our custom classes
#include "URpg_PlayerCharacter.h"

#include "Net/UnrealNetwork.h"

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

	if (HasAuthority()) {
		// server players wont get a call from game mode so must run this in begin play
		RunPostLoginEvents();
	}
}
void AURpg_PlayerController::Possess(APawn* InPawn) {
	// call the super
	Super::Possess(InPawn);
}
// handles contruction that requires the player to be fully loaded
void AURpg_PlayerController::RunPostLoginEvents() {
	// check we have a pawn
	if (GetPawn() != nullptr) {
		// cast the pawn to our custom player character
		AURpg_PlayerCharacter* charRef = Cast<AURpg_PlayerCharacter>(GetPawn());
		if (charRef != nullptr) {
			// tell the bound character to run post login events
			charRef->RunPostLoginEvents();
		}
	}
}
// * INPUT * //
// Detect Character Movement Input on the X axis (Left / Right)
void AURpg_PlayerController::MoveStrafe(float value) {
	// make sure we have a pawn
	if (GetPawn() != nullptr)
	{
		// vars to hold move params
		FRotator RotationControlSpace;
		FRotator YawRotation;
		FVector Direction;

		/*
		// move will be based off the controller
		RotationControlSpace = GetControlRotation();
		YawRotation = FRotator(0, RotationControlSpace.Yaw, 0);
		Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		if (value != 0)
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Strafe");
		// broadcast the move
		Move_Strafe.Broadcast(Direction, value);
		*/
		// get the current camera mode
		AURpg_PlayerCameraManager* camManRef = Cast<AURpg_PlayerCameraManager>(PlayerCameraManager);
		if (camManRef == nullptr) {
			// return if we didn't find our camera manager
			return;
		}
		ECameraMode eCurrentCameraRef = camManRef->GetCameraMode();


		switch (eCurrentCameraRef)
		{
		case ECameraMode::FirstPerson:
			// move will be based off the camera
			RotationControlSpace = PlayerCameraManager->GetCameraRotation();
			YawRotation = FRotator(0, RotationControlSpace.Yaw, 0);
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			/*
			if (value != 0) {
				GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Red, "FPS");
			}
			*/
			// if the input was not zero update the pawns rotation
			GetPawn()->SetActorRotation(YawRotation);

			// broadcast the move
			Move_Strafe.Broadcast(Direction, value);
			break;
		case ECameraMode::OverShoulder:
			// move will be based off the camera
			RotationControlSpace = PlayerCameraManager->GetCameraRotation();
			YawRotation = FRotator(0, RotationControlSpace.Yaw, 0);
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// if the input was not zero update the pawns rotation
			if (value != 0) {
				GetPawn()->SetActorRotation(YawRotation);

				//FRotator rot = Cast<ACharacter>(GetPawn())->GetCharacterMovement()->ComputeOrientToMovementRotation(GetPawn()->GetActorRotation(), GetWorld()->DeltaTimeSeconds, YawRotation);

				//GetPawn()->AddActorWorldRotation(rot - GetPawn()->GetActorRotation());

				//GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Red, "OS");
			}
			// broadcast the move
			Move_Strafe.Broadcast(Direction, value);
			break;
		case ECameraMode::FreeRange:
			// move will be based off the controller
			RotationControlSpace = GetControlRotation();
			YawRotation = FRotator(0, RotationControlSpace.Yaw, 0);
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			/*
			if (value != 0)
			{
				GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Red, "FR");
			}
			*/
			// broadcast the move
			Move_Strafe.Broadcast(Direction, value);
			break;
		case ECameraMode::SkyViewCamera:
			break;
		case ECameraMode::FreeCamera:
			break;
		default:
			break;
		}
	}
	//GEngine->AddOnScreenDebugMessage(0, 1, FColor::Green, FString("X move = " + FString::SanitizeFloat(MoveValX)));
}

// Detect Character Movement Input on the Y axis (Forward / Back)
void AURpg_PlayerController::MoveForwardBack(float value) {
	// make sure we have a pawn
	if (GetPawn() != nullptr)
	{
		// vars to hold move params
		FRotator RotationControlSpace;
		FRotator YawRotation;
		FVector Direction;

		/*
		// move will be based off the controller
		RotationControlSpace = GetControlRotation();
		YawRotation = FRotator(0, RotationControlSpace.Yaw, 0);
		Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		if (value != 0)
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, GetPawn()->GetName() + " ForwardBack ");
		// Broadcast the move
		Move_ForwardBack.Broadcast(Direction, value);
		*/
		// get the current camera mode
		AURpg_PlayerCameraManager* camManRef = Cast<AURpg_PlayerCameraManager>(PlayerCameraManager);
		if (camManRef == nullptr) {
			// return if we didn't find our camera manager
			return;
		}
		ECameraMode eCurrentCameraRef = camManRef->GetCameraMode();
		
		switch (eCurrentCameraRef)
		{
		case ECameraMode::FirstPerson:
			// move will be based off the camera
			RotationControlSpace = PlayerCameraManager->GetCameraRotation();
			YawRotation = FRotator(0, RotationControlSpace.Yaw, 0);
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			// update the pawns rotation
			GetPawn()->SetActorRotation(YawRotation);

			/*
			if (value != 0) {
				GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, GetPawn()->GetName() + " FB:: FPS ");
			}
			*/

			// Broadcast the move
			Move_ForwardBack.Broadcast(Direction, value);

			break;
		case ECameraMode::OverShoulder:
			// move will be based off the camera
			RotationControlSpace = PlayerCameraManager->GetCameraRotation();
			YawRotation = FRotator(0, RotationControlSpace.Yaw, 0);
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			// if the input was not zero update the pawns rotation
			if (value != 0) {
				GetPawn()->SetActorRotation(YawRotation);
				
				//FRotator rot = Cast<ACharacter>(GetPawn())->GetCharacterMovement()->ComputeOrientToMovementRotation(GetPawn()->GetActorRotation(), GetWorld()->DeltaTimeSeconds, YawRotation);

				//GetPawn()->SetActorRotation(rot);
				//GetPawn()->AddActorWorldRotation(rot - GetPawn()->GetActorRotation());

				//Cast<ACharacter>(GetPawn())->GetCharacterMovement()->Rot
				//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, GetPawn()->GetName() + " FB:: Over Shoulder ");
			}
			// Broadcast the move
			Move_ForwardBack.Broadcast(Direction, value);

			break;
		case ECameraMode::FreeRange:
			// move will be based off the controller
			RotationControlSpace = GetControlRotation(); 
			YawRotation = FRotator(0, RotationControlSpace.Yaw, 0);
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			/*
			if (value != 0) {
				GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, GetPawn()->GetName() + " FB:: Free Range ");
			}
			*/
			// Broadcast the move
			Move_ForwardBack.Broadcast(Direction, value);

			break;
		case ECameraMode::SkyViewCamera:
			break;
		case ECameraMode::FreeCamera:
			break;
		default:
			break;
		}
		
	}
	//GEngine->AddOnScreenDebugMessage(0, 1, FColor::Green, FString("Y move = " + FString::SanitizeFloat(MoveValY)));
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
// Attach the Camera to the Pawns camera Boom
bool AURpg_PlayerController::AttachCameraToOwnedCharacter() {
	if (GetCharacter() != nullptr) {
		// get a refrence to the player character
		AURpg_PlayerCharacter* characterRef = Cast<AURpg_PlayerCharacter>(GetCharacter());
		// try to get attached parent as a spring arm compenent
		USpringArmComponent* parentAsSpringArmRef = Cast<USpringArmComponent>(characterRef->GetPlayerCamera()->GetAttachParent());
		// check if we failed to get the spring arm parent OR are spring arm doesn't mach the characters spring arm
		if (parentAsSpringArmRef == nullptr || parentAsSpringArmRef != characterRef->GetCameraBoom()) {
			// remove the camera from current parent
			characterRef->GetPlayerCamera()->DetachFromParent();

#if !UE_BUILD_SHIPPING
			UE_LOG(DebugLog, Log, TEXT("ATTACHING Camera to player pawn's Camera boom"));
#endif // !UE_BUILD_SHIPPING

			// attach the camera to the Player
			characterRef->GetPlayerCamera()->AttachTo(characterRef->GetCameraBoom(), USpringArmComponent::SocketName);
			return true;
		}
	}
	return false;
}


// Activates First Person Camera Mode
void AURpg_PlayerController::ActivateFirstPersonCamera() {

#if !UE_BUILD_SHIPPING
	UE_LOG(InitLog, Log, TEXT("ACTIVATING FirstPerson CameraMode"));
#endif // !UE_BUILD_SHIPPING
	if (GetCharacter() != nullptr) {
		// get a refrence to the player character
		AURpg_PlayerCharacter* characterRef = Cast<AURpg_PlayerCharacter>(GetCharacter());
		//Attach Camare to the head
		USkeletalMeshSocket* sSocket = characterRef->GetMesh()->SkeletalMesh->FindSocket("Head");
		if (sSocket != nullptr) {
			characterRef->GetPlayerCamera()->AttachTo(characterRef->GetMesh(), sSocket->BoneName);
		}
		else {
			characterRef->GetPlayerCamera()->AttachTo(RootComponent);
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
	if (GetCharacter() != nullptr) {
		// get a refrence to the player character
		AURpg_PlayerCharacter* characterRef = Cast<AURpg_PlayerCharacter>(GetCharacter());

		AttachCameraToOwnedCharacter();

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
	if (GetCharacter() != nullptr) {

		// get a refrence to the player character
		AURpg_PlayerCharacter* characterRef = Cast<AURpg_PlayerCharacter>(GetCharacter());
		
		AttachCameraToOwnedCharacter();

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

		AttachCameraToOwnedCharacter();

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
		
		// remove the camera from current parent
		characterRef->GetPlayerCamera()->DetachFromParent();

#if !UE_BUILD_SHIPPING
			UE_LOG(DebugLog, Log, TEXT("DETACHING Camera to player pawn's Camera boom"));
#endif // !UE_BUILD_SHIPPING
			
		
		//characterRef->GetCharacterMovement()->bOrientRotationToMovement = false;
		//characterRef->bUseControllerRotationPitch = false;
		//characterRef->bUseControllerRotationYaw = false;
		//characterRef->bUseControllerRotationRoll = false;
	}
}

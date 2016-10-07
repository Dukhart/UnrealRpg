// Copyright Jordan Duncan 2015 \\ Description=RPG Template


#include "UnrealRpg.h"
#include "URpg_PlayerController.h"


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

	// status
	bIsAlive = false;
	bLockoutDeathNSpawning = false;
	bIsImmortal = false;
	bCanSpawn = false;

	SuicideHeldTime = 0;
	SuicideHoldTime = 1;

	// * UI HUD Widget * //
	// create the component
	//HUDComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HUDComponent"));
	// attach to the root
	//HUDComp->AttachTo(RootComponent);
}
// handles replicated property behavior
void AURpg_PlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(AURpg_PlayerController, CharacterClass);
	DOREPLIFETIME(AURpg_PlayerController, bIsAlive);
	DOREPLIFETIME(AURpg_PlayerController, bLockoutDeathNSpawning);
	DOREPLIFETIME(AURpg_PlayerController, bIsImmortal);
	DOREPLIFETIME(AURpg_PlayerController, bCanSpawn);
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
		InputComponent->BindAction("SuicideRespawn", IE_Pressed, this, &AURpg_PlayerController::OnRespawnSuicide_Press);
		InputComponent->BindAction("SuicideRespawn", IE_Released, this, &AURpg_PlayerController::OnRespawnSuicide_Release);
		InputComponent->BindAction("ToggleHUD", IE_Released, this, &AURpg_PlayerController::OnToggleHUD);
	
	}

}
// Called after the constructor
// World and component dependent starting behavior should go here
void AURpg_PlayerController::BeginPlay() {
	Super::BeginPlay();
	
	if (Role == ROLE_Authority) {
		// server players wont get a call from game mode so must run this in begin play

		//RunPostLoginEvents();
		if (CharacterClass == NULL) {
			if (GetWorld() != nullptr && GetWorld()->GetAuthGameMode() != nullptr) {

				CharacterClass = GetWorld()->GetAuthGameMode()->GetDefaultPawnClassForController(this);
			}
		}

	}
}
void AURpg_PlayerController::Possess(APawn* InPawn) {
	// call the super
	Super::Possess(InPawn);
}

void AURpg_PlayerController::SERVER_RunPostLogin_Implementation() {
	if (GetPawn() != nullptr && PlayerCameraManager != nullptr && GetPawn()->GetController() != nullptr) {

#if !UE_BUILD_SHIPPING
		UE_LOG(DebugLog, Log, TEXT("SERVER post login call"));
#endif // !UE_BUILD_SHIPPING



		RunPostLoginEvents();
		AURpg_PlayerCameraManager* camManRef = Cast<AURpg_PlayerCameraManager>(PlayerCameraManager);
		if (camManRef != nullptr) {
			//GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Red, "Init CAmera");
			camManRef->InitDefaultCameraMode();
		}
	}
	else {
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AURpg_PlayerController::SERVER_RunPostLogin);
		//GEngine->AddOnScreenDebugMessage(10, 50, FColor::Red, "server pl wait");
	}
}
bool AURpg_PlayerController::SERVER_RunPostLogin_Validate() {
	return true;
}

void AURpg_PlayerController::CLIENT_RunPostLogin_Implementation() {
	if (GetPawn() != nullptr && PlayerCameraManager != nullptr && GetPawn()->GetController() != nullptr && GetGameInstance() != nullptr) {

#if !UE_BUILD_SHIPPING
		UE_LOG(DebugLog, Log, TEXT("CLIENT post login call"));
#endif // !UE_BUILD_SHIPPING

		SERVER_RunPostLogin();

		AURpg_PlayerCameraManager* camManRef = Cast<AURpg_PlayerCameraManager>(PlayerCameraManager);
		if (camManRef != nullptr) {

#if !UE_BUILD_SHIPPING
			UE_LOG(DebugLog, Log, TEXT("Init Camera"));
#endif // !UE_BUILD_SHIPPING

			camManRef->InitDefaultCameraMode();
		}
		// make the ui
		if (HUDTemplate->IsChildOf(UURpg_HUD_UserWidget::StaticClass())) {
			// get a ref to the game instance
			UURpg_GameInstance* GI = Cast<UURpg_GameInstance>(GetGameInstance());
			// check we have a ref to the game instance
			if (GI != nullptr) {
				// create the widget and store a ref to the widget instance
				HUDInstance = CreateWidget<UURpg_HUD_UserWidget>(GI, HUDTemplate);
				if (HUDInstance != nullptr) {
					// set the controller to the widgets owner
					HUDInstance->Owner = this;
					// build default starting vals
					HUDInstance->BuildDefaults();
					// update the widget
					HUDInstance->UpdateWidget();
					// add it to the players viewport
					HUDInstance->AddToViewport();
				}
			}
		}
#if !UE_BUILD_SHIPPING
		else {
			UE_LOG(DebugLog, Error, TEXT("Invalid HUD Class Set check HUD Template in player controller for valid class.\nMust inherit from *UURpg_HUD_UserWidget*"));
		}
#endif // !UE_BUILD_SHIPPING
		
	}
	else {
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AURpg_PlayerController::CLIENT_RunPostLogin);
		//GEngine->AddOnScreenDebugMessage(12, 50, FColor::Red, "pl wait");
	}
}
// handles contruction that requires the player to be fully loaded
void AURpg_PlayerController::RunPostLoginEvents_Implementation() {
	// check we have a pawn
	if (GetPawn() != nullptr && PlayerCameraManager != nullptr) {
		// cast the pawn to our custom player character
		AURpg_PlayerCharacter* charRef = Cast<AURpg_PlayerCharacter>(GetPawn());
		if (charRef != nullptr) {
			// tell the bound character to run post login events
			charRef->RunPostLoginEvents();

			charRef->SetCharacterType(ECharacterType::Player);
		}
		/*
		AURpg_PlayerCameraManager* camManRef = Cast<AURpg_PlayerCameraManager>(PlayerCameraManager);
		if (camManRef != nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Red, "Init CAmera");
			camManRef->InitDefaultCameraMode();
		}
		*/
	}
}
void AURpg_PlayerController::RunRespawnEvents_Implementation() {
	// check we have a pawn
	if (GetPawn() != nullptr) {
		// Activate the Camera
		ActivateCameraMode(GetCameraMode(), true);
		// cast the pawn to our custom player character
		AURpg_PlayerCharacter* charRef = Cast<AURpg_PlayerCharacter>(GetPawn());
		if (charRef != nullptr) {
			// tell the bound character to run post login events
			charRef->RunPostLoginEvents();
		}
	}
}

// * INPUT * //
// AXIS
// Detect Character Movement Input on the X axis (Left / Right)
void AURpg_PlayerController::MoveStrafe_Implementation(float value) {
	// make sure we have a pawn
	if (GetPawn() != nullptr && GetPawn()->GetMovementComponent() != nullptr)
	{

		UURpg_CharacterMovementComponent* MoveCompRef = Cast<UURpg_CharacterMovementComponent>(GetPawn()->GetMovementComponent());
		if (MoveCompRef == nullptr) {
			return;
		}

		// vars to hold move params
		FRotator RotationControlSpace;
		FRotator YawRotation;
		FVector Direction;


		/*
		if (value != 0) {
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Strafe");

			const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ECameraMode"), true);
			if (EnumPtr != nullptr) {
				GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Black, GetName() + " " + EnumPtr->GetNameByIndex(static_cast<uint8>(GetCameraMode())).ToString());
			}
		}

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
				MoveCompRef->SetRotation(YawRotation);
			}

			// broadcast the move
			Move_Strafe.Broadcast(Direction, value);
			break;
		case ECameraMode::FreeRange:
			// move will be based off the controller
			RotationControlSpace = GetControlRotation();
			YawRotation = FRotator(0, RotationControlSpace.Yaw, 0);
			Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

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
void AURpg_PlayerController::MoveForwardBack_Implementation(float value) {
	// make sure we have a pawn
	if (GetPawn() != nullptr && GetPawn()->GetMovementComponent() != nullptr)
	{
		UURpg_CharacterMovementComponent* MoveCompRef = Cast<UURpg_CharacterMovementComponent>(GetPawn()->GetMovementComponent());
		if (MoveCompRef == nullptr) {
			return;
		}
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
				MoveCompRef->SetRotation(YawRotation);
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
void AURpg_PlayerController::MoveJump_Implementation(float value) {

}
// Detect Camera Movement Input on the Y Axis
void AURpg_PlayerController::LookUpDownRate_Implementation(float value) {
	if (bInvertLookYAxis) {
		value *= -1.0f;
	}
	// calculate delta for this frame from the rate information
	AddPitchInput(value * baseLookRate * GetWorld()->GetDeltaSeconds());
}
// Detect Camera Movement Input on the Y Axis
void AURpg_PlayerController::LookUpDown_Implementation(float value) {
	if (bInvertLookYAxis) {
		value *= -1.0f;
	}
	AddPitchInput(value);
}
// Detect Camera Movement Input on the X Axis
void AURpg_PlayerController::LookRightLeftRate_Implementation(float value) {
	if (bInvertLookXAxis) {
		value *= -1.0f;
	}
	// calculate delta for this frame from the rate information
	AddYawInput(value * baseTurnRate * GetWorld()->GetDeltaSeconds());
}
// Detect Camera Movement Input on the X Axis
void AURpg_PlayerController::LookRightLeft_Implementation(float value) {
	if (bInvertLookXAxis) {
		value *= -1.0f;
	}
	AddYawInput(value);
}

// ACTIONS
// Suicide player if held and alive
// Respawn the player if pressed when dead
void AURpg_PlayerController::OnRespawnSuicide_Press_Implementation() {
	if (GetWorld() != nullptr) {
		GetWorld()->GetTimerManager().SetTimer(Suicide_TimerHandle, this, &AURpg_PlayerController::OnRespawnSuicide_Hold, 0.01f, true);

#if !UE_BUILD_SHIPPING
		UE_LOG(GeneralLog, Log, TEXT("Start Suicide Timer"));
#endif // !UE_BUILD_SHIPPING

	}
}
void AURpg_PlayerController::OnRespawnSuicide_Release_Implementation() {
	// if alive check for suicede params
	if (bIsAlive) {
		// check we held the button down for the required time
		if (SuicideHeldTime >= SuicideHoldTime) {
			// suicide request doesn't require immortality check so override immortality check on reuest to server
			SERVER_KillPlayer(true);
		}
	}
	// else we are dead so request respawn
	else {
		SERVER_RespawnPlayer();
	}

	// reset hold time
	SuicideHeldTime = 0;
	if (GetWorld() != nullptr) {
		// clear the timer
		GetWorld()->GetTimerManager().ClearTimer(Suicide_TimerHandle);

#if !UE_BUILD_SHIPPING
		UE_LOG(GeneralLog, Log, TEXT("Stop Suicide Timer"));
#endif // !UE_BUILD_SHIPPING

	}
}
void AURpg_PlayerController::OnRespawnSuicide_Hold_Implementation() {
	// increase held time by activation interval
	if (GetWorld() != nullptr) {
		SuicideHeldTime += GetWorld()->GetTimerManager().GetTimerRate(Suicide_TimerHandle);
	}
#if !UE_BUILD_SHIPPING
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::SanitizeFloat(SuicideHeldTime));
#endif // !UE_BUILD_SHIPPING
}
// * REQUEST TO SERVER * //
// request the server to kill the player
void AURpg_PlayerController::SERVER_KillPlayer_Implementation(bool bOverrideImmortality) {
	if ((bIsImmortal == false || bOverrideImmortality == true) && bLockoutDeathNSpawning == false) {
		if (GetWorld() != nullptr || GetWorld()->GetAuthGameMode() != nullptr) {
			AURpg_GameMode* gm = Cast<AURpg_GameMode>(GetWorld()->GetAuthGameMode());
			if (gm != nullptr) {
				// lockout spawn and kill options until operation is complete
				SetLockoutDeathNSpawning(true);
				gm->KillPlayer(this, bOverrideImmortality);
			}
		}
	}
}
bool AURpg_PlayerController::SERVER_KillPlayer_Validate(bool bOverrideImmortality) {
	return true;
}
// request the server to respawn the player
void AURpg_PlayerController::SERVER_RespawnPlayer_Implementation() {
	if (bCanSpawn == true && bLockoutDeathNSpawning == false) {
		if (GetWorld() != nullptr || GetWorld()->GetAuthGameMode() != nullptr) {
			AURpg_GameMode* gm = Cast<AURpg_GameMode>(GetWorld()->GetAuthGameMode());
			if (gm != nullptr) {
				// lockout spawn and kill options until operation is complete
				SetLockoutDeathNSpawning(true);
				gm->RespawnPlayer(this);
			}
		}
	}
}
bool AURpg_PlayerController::SERVER_RespawnPlayer_Validate() {
	return true;
}

// * CAMERA * //
// Switch between Controller/Camera styles
void AURpg_PlayerController::ActivateCameraMode(ECameraMode newCameraMode, bool bForceActivate) {
	
	
#if !UE_BUILD_SHIPPING
	// print the camera mode being activated to the log
	// try to get the enum as a UEnum
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ECameraMode"), true);
	if (EnumPtr != nullptr) {
		// print to the log by name if we have th UEnum
		UE_LOG(InitLog, Log, TEXT("Activating Camera Mode: %s"), *EnumPtr->GetNameByIndex(static_cast<uint8>(newCameraMode)).ToString());
	}
	else {
		// else print to the log by index
		UE_LOG(InitLog, Log, TEXT("Activating Camera Mode: %s"), *FString::SanitizeFloat(static_cast<uint8>(newCameraMode)));
	}
#endif // !UE_BUILD_SHIPPING

	AURpg_PlayerCameraManager* camManRef = Cast<AURpg_PlayerCameraManager>(PlayerCameraManager);
	// if the new camera mode is the same as our new camera mode return
	if (camManRef == nullptr || (newCameraMode == camManRef->GetCameraMode() && !bForceActivate)) {
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
		UE_LOG(DebugLog, Warning, TEXT("Invalid Camera mode input: Activating backup FreeRangeMode"))
#endif // !UE_BUILD_SHIPPING

			ActivateFreeRangeCamera();
		break;
	}
	//camManRef->SetCameraMode(newCameraMode);
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
			UE_LOG(InitLog, Log, TEXT("ATTACHING Camera to player pawn's Camera boom"));
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

	Cast<AURpg_PlayerCameraManager>(PlayerCameraManager)->SetCameraMode(ECameraMode::FirstPerson);
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
		//GEngine->AddOnScreenDebugMessage(-1, 19, FColor::Red, "os settings2");
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
// Toggles the entire HUD to be Visible or Hidden Deppending on current state
void AURpg_PlayerController::OnToggleHUD() {
	if (HUDInstance != nullptr) {
		// if visible
		if (HUDInstance->IsVisible()) {
			// Hide the HUD
			HUDInstance->SetVisibility(ESlateVisibility::Hidden);
		}
		else {
			// else make the HUD visible
			HUDInstance->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

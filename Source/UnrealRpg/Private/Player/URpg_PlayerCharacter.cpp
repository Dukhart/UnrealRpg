// Copyright Jordan Duncan 2015 \\ Description=RPG Template


#include "UnrealRpg.h"
#include "URpg_PlayerCharacter.h"
// needed to get information from the controller
#include "URpg_PlayerController.h"
// needed for replicated properties
#include "Net/UnrealNetwork.h"

// * INTITIALIZATION * //
// constructor
// add components and set default values
AURpg_PlayerCharacter::AURpg_PlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UURpg_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName)) {
	// get the refrence to our character Mesh asset
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(*FURpg_MeshAsset_Paths::DefaultPlayerCharacterMesh);
	
	// Set default character type
	CharacterType = ECharacterType::AI;

	// get the refrence to our character animation asset
	// disabled for now seems to be causing a strange bug that prevents the editor from loading if we cast to our CharacterBp from our AnimBp
	//static ConstructorHelpers::FObjectFinder<UAnimBlueprintGeneratedClass> AnimBp(*FURpg_BpAsset_Paths::DefualtPlayerAnimationBP);
	
	if (MeshObj.Object && GetMesh() != NULL) {
		// Set the new Mesh
		GetMesh()->SetSkeletalMesh(MeshObj.Object);
		// Set the Mesh LOCAL posistion and rotation
		FRotator rotation;
		rotation.Yaw = -90.0f;
		rotation.Roll = 0.0f;
		rotation.Pitch = 0.0f;
		FVector position;
		position.X = 0.0f;
		position.Y = 0.0f;
		position.Z = -87.0f;
		GetMesh()->SetRelativeLocationAndRotation(position, rotation);
		// Set the animation blueprint
		//if (AnimBp.Object) {
		//	GetMesh()->AnimBlueprintGeneratedClass = AnimBp.Object;
		//}
	}
	// Create a camera boom (pulls in towards the player if there is a collision)
	// Note current values are for CONSTRUCTION ONLY final values will set individualy per camera mode	
	// see Character Controller Activate Camera mode to adjust values
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// attach the camera boom to our root
	CameraBoom->AttachTo(RootComponent);
	// The camera follows at this distance behind the character.
	CameraBoom->TargetArmLength = 300.0f;
	// Rotate the arm based on the controller
	CameraBoom->bUsePawnControlRotation = true;
	// Create a follow camera
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	// Attach the camera to the end of the camera boom
	PlayerCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	// Camera does not rotate relative to arm
	PlayerCamera->bUsePawnControlRotation = false;
	// store a ref to our movement component
	MovementCompRef = Cast<UURpg_CharacterMovementComponent>(Super::GetMovementComponent());

	
	// * STATS * //
	// Add Main Stats
	Stats.Add(FURpg_Stat_Struct(EStatName::Health));
	Stats.Add(FURpg_Stat_Struct(EStatName::Stamina));
	Stats.Add(FURpg_Stat_Struct(EStatName::Mana));
	// Add Survival Stats
	Stats.Add(FURpg_Stat_Struct(EStatName::Hunger));
	Stats.Add(FURpg_Stat_Struct(EStatName::Thirst));
	Stats.Add(FURpg_Stat_Struct(EStatName::Warmth));
	Stats.Add(FURpg_Stat_Struct(EStatName::Rest));
	// Add emotional stats
	Stats.Add(FURpg_Stat_Struct(EStatName::Happiness));
	// * ATTRIBUTES * //
	// Add core Attributes
	Attributes.Add(FURpg_Attribute_Struct(EAttributeName::Strength));
	Attributes.Add(FURpg_Attribute_Struct(EAttributeName::Dexterity));
	Attributes.Add(FURpg_Attribute_Struct(EAttributeName::Constitution));
	Attributes.Add(FURpg_Attribute_Struct(EAttributeName::Intelligence));
	Attributes.Add(FURpg_Attribute_Struct(EAttributeName::Wisdom));
	Attributes.Add(FURpg_Attribute_Struct(EAttributeName::Charisma));
	Attributes.Add(FURpg_Attribute_Struct(EAttributeName::Luck));
	

	// * UI HUD Widget * //
	StatusWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatusWidgetComponent"));
	StatusWidgetComp->AttachTo(RootComponent);

}

// set replicated properties and their conditions
void AURpg_PlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// initialize replication params
	DOREPLIFETIME(AURpg_PlayerCharacter, eCurrentCameraMode);
}

// called after the constructor
void AURpg_PlayerCharacter::BeginPlay() {
	Super::BeginPlay();
}
// runs when a player first logs in
void AURpg_PlayerCharacter::RunPostLoginEvents_Implementation() {
	// tell the client to bind inputs
	CLIENT_BindInputDelegates();
	// get our controller
	if (GetController() != nullptr) {
		AURpg_PlayerController* ControlRef = Cast<AURpg_PlayerController>(GetController());
		if (ControlRef != nullptr) {
			// set is Alive to true
			ControlRef->SetIsAlive(true);
		}
	}
}
// runs whenever the character is respawned
void AURpg_PlayerCharacter::RunRespawnEvents_Implementation() {
	// tell the client to bind inputs
	CLIENT_BindInputDelegates();
	// get our controller
	if (GetController() != nullptr) {
		AURpg_PlayerController* ControlRef = Cast<AURpg_PlayerController>(GetController());
		if (ControlRef != nullptr) {
			// set is Alive to true
			ControlRef->SetIsAlive(true);
		}
	}
}

// binds client input from the controller to the characters movement
void AURpg_PlayerCharacter::CLIENT_BindInputDelegates_Implementation() {
//	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Blue, "starts Binding Delegates");
	if (GetController() != nullptr) {
		// get the InPawn as a URpg_Character
		AURpg_PlayerController* ControlRef = Cast<AURpg_PlayerController>(GetController());
	//	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Blue, "has controller Binding Delegates");
		// check the cast was successfull
		if (ControlRef != nullptr) {

#if UE_BUILD_SHIPPING
			UE_LOG(InitLog, Log, TEXT("%s Binding Delegates"), *GetName());
#endif // UE_BUILD_SHIPPING

			
			// Bind Character movement methods to our delegates
			ControlRef->Move_Strafe.AddDynamic(this, &AURpg_PlayerCharacter::DoMoveStrafe);
			ControlRef->Move_ForwardBack.AddDynamic(this, &AURpg_PlayerCharacter::DoMoveForwardBack);
		}
	}
}

// returns the movement component
UPawnMovementComponent* AURpg_PlayerCharacter::GetMovementComponent() const {
	return MovementCompRef;
	//return Super::GetMovementComponent();
}

// * DESTRUCTION * //
// extra end play behavior
void AURpg_PlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
}

// * MOVEMENT * //
// Apply Character Movement Input on the X axis (Left / Right)
void AURpg_PlayerCharacter::DoMoveStrafe(const FVector& Direction, const float& value) {
	if (GetMovementComponent() != nullptr && value != 0) {
		GetMovementComponent()->AddInputVector(Direction * value);

#if !UE_BUILD_SHIPPING
		GEngine->AddOnScreenDebugMessage(3, 1, FColor::Red, GetName() + " Doing Strafe: " + FString::SanitizeFloat(value));
#endif // !UE_BUILD_SHIPPING

	}
}

// Apply Character Movement Input on the Y axis (Forward / Back)
void AURpg_PlayerCharacter::DoMoveForwardBack(const FVector& Direction, const float& value) {
	if (GetMovementComponent() != nullptr && value != 0) {
		GetMovementComponent()->AddInputVector(Direction * value, true);

#if !UE_BUILD_SHIPPING
		GEngine->AddOnScreenDebugMessage(2, 1, FColor::Green, GetName() + " Doing FB: " + FString::SanitizeFloat(value));
#endif // !UE_BUILD_SHIPPING

	}
}

// Apply Jump Input
void AURpg_PlayerCharacter::DoMoveJump(float value) {

}
// Apply Camera Movement Input on the Y Axis
void AURpg_PlayerCharacter::DoLookUpDownRate(float value) {

}
void AURpg_PlayerCharacter::DoLookUpDown(float value) {

}
// Apply Camera Movement Input on the X Axis
void AURpg_PlayerCharacter::DoLookRightLeftRate(float value) {

}
void AURpg_PlayerCharacter::DoLookRightLeft(float value) {

}

// Asks the server what the players current camera mode is
ECameraMode AURpg_PlayerCharacter::GetPlayersCameraMode() {
	if (Role == ROLE_AutonomousProxy)
		SERVER_RequestPlayerCameraMode();

	return eCurrentCameraMode;
}
// returns characters camera mode from the server
void AURpg_PlayerCharacter::SERVER_RequestPlayerCameraMode_Implementation() {
	// get the controller
	if (GetController() != nullptr) {
		AURpg_PlayerController* controlRef = Cast<AURpg_PlayerController>(GetController());
		if (controlRef != nullptr) {
			// get the camera mode from the controller
			eCurrentCameraMode = controlRef->GetCameraMode();
		}
	}
}
bool AURpg_PlayerCharacter::SERVER_RequestPlayerCameraMode_Validate() {
	return true;
}




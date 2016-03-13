// Copyright Jordan Duncan 2015 \\ Description=RPG Template


#include "UnrealRpg.h"
#include "URpg_PlayerCharacter.h"


// * INTITIALIZATION * //
// constructor
// add components and set default values
AURpg_PlayerCharacter::AURpg_PlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	// get the refrence to our character Mesh asset
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(*FURpg_MeshAsset_Paths::DefaultPlayerCharacterMesh);
	// get the refrence to our character animation asset
	static ConstructorHelpers::FObjectFinder<UAnimBlueprintGeneratedClass> AnimBp(*FURpg_BpAsset_Paths::DefualtPlayerAnimationBP);
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
		if (AnimBp.Object) {
			GetMesh()->AnimBlueprintGeneratedClass = AnimBp.Object;
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
		//bUseControllerRotationPitch = false;
		//bUseControllerRotationYaw = false;
		//bUseControllerRotationRoll = false;
		//GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}
// called after the constructor
// world and component dependent starting behavior should go here
void AURpg_PlayerCharacter::BeginPlay() {
	Super::BeginPlay();
}

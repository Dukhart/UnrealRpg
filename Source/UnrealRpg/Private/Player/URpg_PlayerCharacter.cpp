// Copyright Jordan Duncan 2015 \\ Description=RPG Template


#include "UnrealRpg.h"
#include "URpg_PlayerCharacter.h"





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
		//  Note current values are for CONSTRUCTION ONLY final values will set individualy per camera mode	see Character Controller Activate Camera mode to adjust values
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
		CameraBoom->AttachTo(RootComponent);
		CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character.
		CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
													// Create a follow camera
		PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
		PlayerCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
		PlayerCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
		//bUseControllerRotationPitch = false;
		//bUseControllerRotationYaw = false;
		//bUseControllerRotationRoll = false;
		//GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}
/*
void AURpg_PlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{

	// Set up gameplay key bindings
	check(InputComponent);
	//InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//InputComponent->BindAxis("MoveForward", this, &AUnrealRpgCharacter::MoveForward);
//	InputComponent->BindAxis("MoveRight", this, &AUnrealRpgCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
//	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
//	InputComponent->BindAxis("TurnRate", this, &AUnrealRpgCharacter::TurnAtRate);
//	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
//	InputComponent->BindAxis("LookUpRate", this, &AUnrealRpgCharacter::LookUpAtRate);

	// handle touch devices
//	InputComponent->BindTouch(IE_Pressed, this, &AUnrealRpgCharacter::TouchStarted);
//	InputComponent->BindTouch(IE_Released, this, &AUnrealRpgCharacter::TouchStopped);
	
}
*/
void AURpg_PlayerCharacter::BeginPlay() {
	Super::BeginPlay();
}

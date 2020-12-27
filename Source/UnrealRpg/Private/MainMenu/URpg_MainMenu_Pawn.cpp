// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealRpg.h"
#include "URpg_MainMenu_Pawn.h"


// Sets default values
AURpg_MainMenu_Pawn::AURpg_MainMenu_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// create the default collider
	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	Collider->AttachTo(RootComponent);
	// create the players camera
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	PlayerCamera->AttachTo(Collider);

	MainMenuTransform = FTransform();
	MainMenuTransform.SetLocation(FVector(-250.0f, 240.0f, -58.0f));
	MainMenuTransform.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
	MainMenuTransform.SetScale3D(FVector(1.0f));
	
	CharSelectTransform = FTransform();
	CharSelectTransform.SetLocation(FVector(520.0f, -383.0f, -34.0f));
	CharSelectTransform.SetRotation(FQuat(FRotator(0.0f, -40.0f, 0.0f)));
	CharSelectTransform.SetScale3D(FVector(1.0f));
}

// Called when the game starts or when spawned
void AURpg_MainMenu_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AURpg_MainMenu_Pawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AURpg_MainMenu_Pawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

FTransform AURpg_MainMenu_Pawn::GetMainMenuTransform() {
	return MainMenuTransform;
}
FTransform AURpg_MainMenu_Pawn::GetCharSelectTransform() {
	return CharSelectTransform;
}
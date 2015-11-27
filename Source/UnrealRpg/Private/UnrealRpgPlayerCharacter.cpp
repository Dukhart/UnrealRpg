// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealRpg.h"
#include "UnrealRpgPlayerCharacter.h"
#include "Animation/AnimBlueprint.h"
#include "Animation/AnimBlueprintGeneratedClass.h"




AUnrealRpgPlayerCharacter::AUnrealRpgPlayerCharacter() {

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(*FURLs::DefaultPlayerCharacterMesh);
	static ConstructorHelpers::FObjectFinder<UAnimBlueprintGeneratedClass> AnimBp(*FURLs::DefualtPlayerAnimationBP);
	if (MeshObj.Object && GetMesh() != NULL) {
		// Set the new Mesh
		GetMesh()->SetSkeletalMesh(MeshObj.Object);
		// Set the Mesh local posistion
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
	}
}
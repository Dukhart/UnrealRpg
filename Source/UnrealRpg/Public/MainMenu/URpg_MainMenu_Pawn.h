// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "URpg_MainMenu_Pawn.generated.h"

UCLASS()
class UNREALRPG_API AURpg_MainMenu_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AURpg_MainMenu_Pawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
		USphereComponent* Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* PlayerCamera;
private:
	UPROPERTY()
		FTransform MainMenuTransform;
	UPROPERTY()
		FTransform CharSelectTransform;
public:
	UFUNCTION(BlueprintCallable, Category = "Locations")
	FTransform GetMainMenuTransform();
	UFUNCTION(BlueprintCallable, Category = "Locations")
		FTransform GetCharSelectTransform();
};

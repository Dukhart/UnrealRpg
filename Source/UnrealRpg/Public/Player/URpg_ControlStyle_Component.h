// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "URpg_ControlStyle_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALRPG_API UURpg_ControlStyle_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UURpg_ControlStyle_Component();

	// Called when the game starts
	virtual void BeginPlay() override;

	//virtual void Move_Strafe_FreeRange();
	

};

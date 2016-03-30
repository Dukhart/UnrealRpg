// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealRpg.h"
#include "URpg_ControlStyle_Component.h"


// Sets default values for this component's properties
UURpg_ControlStyle_Component::UURpg_ControlStyle_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UURpg_ControlStyle_Component::BeginPlay()
{
	Super::BeginPlay();
	// ...
}



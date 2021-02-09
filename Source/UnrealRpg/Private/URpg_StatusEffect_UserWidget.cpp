// Fill out your copyright notice in the Description page of Project Settings.
#include "URpg_StatusEffect_UserWidget.h"
#include "URpg_StatusEffect.h"

UURpg_StatusEffect_UserWidget::UURpg_StatusEffect_UserWidget(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	//bTick = true;
}
void UURpg_StatusEffect_UserWidget::NativeTick(const FGeometry& Geometry, float DeltaTime) {
	Super::NativeTick(Geometry, DeltaTime);
}
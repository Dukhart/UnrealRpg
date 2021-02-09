// Copyright Jordan Duncan 2015
#include "URpg_HUD_UserWidget.h"

UURpg_HUD_UserWidget::UURpg_HUD_UserWidget(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	//bCanEverTick = true;
}

void UURpg_HUD_UserWidget::NativeTick(const FGeometry& Geometry, float DeltaTime) {
	Super::NativeTick(Geometry, DeltaTime);
}
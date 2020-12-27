// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Player/UI/URpg_Base_UserWidget.h"
#include "URpg_StatusEffect_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UURpg_StatusEffect_UserWidget : public UURpg_Base_UserWidget
{
	GENERATED_BODY()
		UURpg_StatusEffect_UserWidget(const class FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
protected:

	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
	float BlinkSpeed = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
	class UURpg_StatusEffect* StatusEffectRef;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Settings")
		void SetImage(const UImage* newImage);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Settings")
		void SetText(const FString& newText);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Settings")
	void SetBlinkSpeed(const float newRate);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Settings")
		void SetTextVisible(const bool val);
};

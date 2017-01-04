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
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings")
	float BlinkSpeed = 0;

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

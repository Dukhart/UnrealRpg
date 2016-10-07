// Copyright Jordan Duncan 2015

#pragma once

#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"

#include "URpg_Base_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UURpg_Base_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
		AActor* Owner;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Update")
		void UpdateWidget();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Update")
		void BuildDefaults();
	
	
};

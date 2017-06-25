// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "PlayerUI.generated.h"

/**
 * 
 */

class UImage;

UCLASS()
class UE4_PROJECT_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Images")
	TArray<UImage*> ImageArray;

	UFUNCTION(BlueprintCallable, Category = "Images")
	void DisplayImage(int32 iArrayRef);

	UFUNCTION(BlueprintCallable, Category = "Images")
	void CloseImage();

	UPROPERTY(BlueprintReadOnly, Category = "Monster Warning")
	float DistanceFromMonster;

private:
	int32 iCurrentDisplayedImage;
	
	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class L20240625_API AMyHUD : public AHUD
{
	GENERATED_BODY()
public:
	AMyHUD();

	int32 CenterX;

	int32 CenterY;

	int32 CrosshairHalfSize;

	int32 CrosshairMaxOpen;

	int32 CrosshairOpen;

	virtual void DrawHUD() override;
};

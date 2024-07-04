// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/Canvas.h"	
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyHUD::AMyHUD()
{
	CrosshairHalfSize = 15;
	CrosshairMaxOpen = 30;
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	int32 SizeX = Canvas->SizeX;
	int32 SizeY = Canvas->SizeY;

	//FVector2D Size = UWidgetLayoutLibrary::GetViewportSize(GetWorld());

	//APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//PC = GetOwningPlayerController();

	//PC->GetViewportSize(SizeX, SizeY);

	//GetOwner()

	CenterX = SizeX / 2;
	CenterY = SizeY / 2;

	ACharacter* Pawn = Cast<ACharacter>(GetOwningPawn());
	if (Pawn)
	{
		double Speed = Pawn->GetCharacterMovement()->Velocity.Size2D();
		double Ratio = Speed / Pawn->GetCharacterMovement()->GetMaxSpeed();
		CrosshairOpen = (int32)((double)CrosshairMaxOpen * Ratio);
	}

	//Left
	DrawLine(CenterX - CrosshairHalfSize - CrosshairOpen,
		CenterY,
		CenterX - CrosshairOpen,
		CenterY,
		FLinearColor::Red,
		3.0f);

	//Right
	DrawLine(CenterX + CrosshairOpen,
		CenterY,
		CenterX + CrosshairHalfSize + CrosshairOpen,
		CenterY,
		FLinearColor::Red,
		3.0f);

	//Up
	DrawLine(CenterX,
		CenterY - CrosshairHalfSize - CrosshairOpen,
		CenterX,
		CenterY - CrosshairOpen,
		FLinearColor::Red,
		3.0f);

	//Down
	DrawLine(CenterX,
		CenterY + CrosshairOpen,
		CenterX,
		CenterY + CrosshairHalfSize + CrosshairOpen,
		FLinearColor::Red,
		3.0f);
}

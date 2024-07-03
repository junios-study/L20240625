// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EIC)
	{
		EIC->BindAction(IA_Forward, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		EIC->BindAction(IA_MyJump, ETriggerEvent::Triggered, this, &AMyCharacter::Jump);

		EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyCharacter::Look);

		EIC->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &AMyCharacter::Zoom);
	}

}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Direction = Value.Get<FVector2D>();

	FRotator DesireRotation = FRotator(0, GetControlRotation().Yaw, 0);

	FVector DesireForward = UKismetMathLibrary::GetForwardVector(DesireRotation);
	FVector DesireRight = UKismetMathLibrary::GetRightVector(DesireRotation);


	AddMovementInput(
		DesireForward * Direction.X
	);

	AddMovementInput(
		DesireRight * Direction.Y
	);

}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	FVector2D Rotation = Value.Get<FVector2D>();

	//AddControllerRollInput(Rotation.X);
	AddControllerYawInput(Rotation.X);
	AddControllerPitchInput(Rotation.Y);
}

void AMyCharacter::Zoom(const FInputActionValue& Value)
{
	float ZoomDepth = Value.Get<float>();

	float NewTargetLength = CameraBoom->TargetArmLength + (ZoomDepth * -500.0f);

	CameraBoom->TargetArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, NewTargetLength, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 1.0f);

	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength, 40.0f, 600.0f);
}


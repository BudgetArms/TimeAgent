// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeAgentPlayer.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ATimeAgentPlayer::ATimeAgentPlayer()
{
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh(), FName("Mesh"));
	Camera->SetRelativeLocation(FVector(0.0f, 17.0f, 170.0f));
	Camera->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	
	UCapsuleComponent* Capsule = ACharacter::GetCapsuleComponent();
	Capsule->SetCapsuleRadius(20);
	
	
	Camera->bUsePawnControlRotation = true;
	Camera->bEnableFirstPersonFieldOfView = true;
	Camera->bEnableFirstPersonScale = true;
		
	// Set First person type's to capsule/mesh, so the camera doesn't pick up the player
	Capsule->SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::FirstPerson);
	GetMesh()->SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::FirstPerson);
	
}

void ATimeAgentPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATimeAgentPlayer::MoveInput);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATimeAgentPlayer::LookInput);
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATimeAgentPlayer::JumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ATimeAgentPlayer::JumpEnd);
	}
}

void ATimeAgentPlayer::MoveInput(const FInputActionValue& Value)
{
	// Get move vector
	FVector2D MoveInput = Value.Get<FVector2D>();
	
	// Apply movement input
	Move(MoveInput.Y, MoveInput.X);
}

void ATimeAgentPlayer::LookInput(const FInputActionValue& Value)
{
	// Get look vector
	FVector2D LookInput = Value.Get<FVector2D>();
	
	// Apply move force
	if (LookInput.IsNearlyZero())
	{
		return;
	}
	
	Look(LookInput.X, LookInput.Y);
	
}

void ATimeAgentPlayer::JumpStart(const FInputActionValue& Value)
{
	// if the player is on the ground, jump
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		Jump();
	}
}

void ATimeAgentPlayer::JumpEnd(const FInputActionValue& Value)
{
	StopJumping();
}

void ATimeAgentPlayer::Move(const float Forward, const float Right)
{
	if (GetController())
	{
		AddMovementInput(GetActorForwardVector(), Forward);
		AddMovementInput(GetActorRightVector(), Right);
	}
}

void ATimeAgentPlayer::Look(const float Yaw, const float Pitch)
{
	if (GetController())
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}


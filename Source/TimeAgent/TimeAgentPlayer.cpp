// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeAgentPlayer.h"

#include "EnhancedInputComponent.h"
#include "SlowMotionComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ATimeAgentPlayer::ATimeAgentPlayer()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh(), FName("Mesh"));
	Camera->SetRelativeLocation(FVector(0.0f, 17.0f, 170.0f));
	Camera->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	Camera->bUsePawnControlRotation = true;
	Camera->bEnableFirstPersonFieldOfView = true;
	Camera->bEnableFirstPersonScale = true;


	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->SetCapsuleRadius(20);

	// Set First person type's to capsule/mesh, so the camera doesn't pick up the player
	Capsule->SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::FirstPerson);
	GetMesh()->SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::FirstPerson);
	
	
	// SlowMotionComp = CreateDefaultSubobject<USlowMotionComponent>(TEXT("SlowMotion"));
	// SlowMotionComp->Activate();
	// if (!SlowMotionComp)
	// {
		// UE_LOG(LogTemp, Warning, TEXT("Player CTOR: SlowMotionComp is not valid"))
	// }	
	
}

void ATimeAgentPlayer::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	AddPostProcessingMaterial();
}

UMaterialInstanceDynamic* ATimeAgentPlayer::GetSlowMotionPostProcessMaterial() const
{
	return PostProcessMID;
}


FVector ATimeAgentPlayer::GetLookDirection() const
{
	return Camera->GetForwardVector();
}

FVector ATimeAgentPlayer::GetBulletDirection() const
{
	FVector LookDirection = GetLookDirection();	
	
	if (!SlowMotionComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("FUCKED SlowMotionComp"));
		return LookDirection;
	}	
		
	if (SlowMotionComp->IsInSlowMotion())
	{
		return LookDirection;
	}
	
	// if standing still
	if (GetCharacterMovement()->Velocity.Length() == 0)
	{
		return LookDirection;
	}

	const float RandomX = FMath::FRandRange(-MovingSway, MovingSway);
	const float RandomY = FMath::FRandRange(-MovingSurge, MovingSurge);
	const float RandomZ = FMath::FRandRange(-MovingHeave, MovingHeave);

	const FVector RandomDirection = FVector(RandomX, RandomY, RandomZ);
	
	LookDirection += RandomDirection;
	
	UE_LOG(LogTemp, Warning, TEXT("RandomDir: %s"), *RandomDirection.ToString());
	return LookDirection.GetSafeNormal();
}

void ATimeAgentPlayer::SetSlowMotionComponent(USlowMotionComponent* NewSlowMotionComponent)
{
	SlowMotionComp = NewSlowMotionComponent;
}

void ATimeAgentPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	if (!SlowMotionComp)
	{
		UE_LOG(LogTemp, Error, TEXT("BeginPlay: SlowMotionComp is not valid"))
	}
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
	const FVector2D LookInput = Value.Get<FVector2D>();

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


void ATimeAgentPlayer::AddPostProcessingMaterial()
{
	if (!PostProcessMI)
	{
		UE_LOG(LogTemp, Error, TEXT("PostProcessMaterialInstance is not assigned"));
		return;
	}


	// Create the dynamic material instance
	PostProcessMID = UMaterialInstanceDynamic::Create(PostProcessMI, this);

	FWeightedBlendable WeightedBlendable;

	WeightedBlendable.Weight = 1.f;
	WeightedBlendable.Object = PostProcessMID;

	Camera->PostProcessSettings.WeightedBlendables.Array.Add(WeightedBlendable);
}

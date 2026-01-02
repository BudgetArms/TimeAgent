// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeAgentCharacter.h"


ATimeAgentCharacter::ATimeAgentCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void ATimeAgentCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ATimeAgentCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATimeAgentCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATimeAgentCharacter::OnDeath()
{
	bIsDead = true;

}

void ATimeAgentCharacter::DealDamage(float damage, AActor* damageSource)
{
	if (Health <= 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Character has no health"));
		return;
	}

	Health -= damage;
	Health = FMath::Clamp(Health, 0, MaxHealth);

	if (damageSource)
	{
		DamageSource = damageSource;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("damageSource not given"));
	}
	
	if (Health == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Character died"));
		bIsDead = true;
	}
	
	
}


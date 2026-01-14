// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeAgentGameModeBase.h"

#include "SlowMotionComponent.h"
#include "TimeAgentPlayer.h"
#include "Kismet/GameplayStatics.h"


void ATimeAgentGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ATimeAgentPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player is null"));
		return;
	}
	
	PlayerSlowMotion = Cast<USlowMotionComponent>(Player->GetComponentByClass(USlowMotionComponent::StaticClass()));
	if (!PlayerSlowMotion)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerSlowMotionComponent is null"));
		return;
	}
	
}

void ATimeAgentGameModeBase::Tick(float elapsedSec)
{
	Super::Tick(elapsedSec);
	
	// UE_LOG(LogTemp, Warning, TEXT("SlowMotion %d"), PlayerSlowMotion->IsInSlowMotion());
}

bool ATimeAgentGameModeBase::IsInSlowMotion() const
{
	if (!PlayerSlowMotion)
	{
		return false;
	}
	
	return PlayerSlowMotion->IsInSlowMotion();
}

void ATimeAgentGameModeBase::ToggleSlowdownTime()
{
	// const FString Text = PlayerSlowMotion->IsInSlowMotion() ? "OFF" : "ON";
	// UE_LOG(LogTemp, Warning, TEXT("ToggleSlowdownTime is %s"), *Text); 
	
	if (!PlayerSlowMotion)
	{
		return;
	}
	
	if (PlayerSlowMotion->IsInSlowMotion())
	{
		PlayerSlowMotion->StopSlowMotion();
	}
	else
	{
		PlayerSlowMotion->StartSlowMotion();
	}
	
}

void ATimeAgentGameModeBase::TryToggleSlowdownTime()
{
	if (!PlayerSlowMotion)
	{
		return;
	}
	
	if (PlayerSlowMotion->IsInSlowMotion())
	{
		PlayerSlowMotion->StopSlowMotion();
	}
	else
	{
		PlayerSlowMotion->TryActiveSlowMotion();
	}
	
}

float ATimeAgentGameModeBase::GetSlowTimeScale() const
{
	UE_LOG(LogTemp, Verbose, TEXT("GetGlobalTimeDilation"));
	return SlowMotionTimeScale;
}

void ATimeAgentGameModeBase::SetSlowTimeScale(float TimeScale)
{
	UE_LOG(LogTemp, Verbose, TEXT("SetGlobalTimeDilation"));
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeScale);
}

void ATimeAgentGameModeBase::RespawnPlayer()
{
}

void ATimeAgentGameModeBase::RespawnEnemies(int LevelNumber)
{
	LevelNumber;
}

void ATimeAgentGameModeBase::EnableSlowMotion() const
{
	if (!PlayerSlowMotion)
	{
		return;
	}
	
	PlayerSlowMotion->StartSlowMotion();
}

void ATimeAgentGameModeBase::DisableSlowMotion() const
{
	if (!PlayerSlowMotion)
	{
		return;
	}
	
	PlayerSlowMotion->StopSlowMotion();
}


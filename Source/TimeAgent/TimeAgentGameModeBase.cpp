// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeAgentGameModeBase.h"

#include "SlowMotionComponent.h"
#include "TimeAgentPlayer.h"
#include "Kismet/GameplayStatics.h"


ATimeAgentGameModeBase::ATimeAgentGameModeBase()
{
	
}


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
	
	UE_LOG(LogTemp, Log, TEXT("SlowMotion %d"), bInSlowMotion);
	
}

bool ATimeAgentGameModeBase::IsInSlowMotion() const
{
	return PlayerSlowMotion->IsInSlowMotion();
}

void ATimeAgentGameModeBase::ToggleSlowdownTime()
{
	if (bInSlowMotion)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
		
		PlayerSlowMotion->StopSlowMotion();
		bInSlowMotion = false;
	}
	else
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), SlowMotionTimeScale);
		
		PlayerSlowMotion->StartSlowMotion();
		bInSlowMotion = true;;
	}
	
}


float ATimeAgentGameModeBase::GetSlowTimeScale() const
{
	UE_LOG(LogTemp, Log, TEXT("GetGlobalTimeDilation"));
	return SlowMotionTimeScale;
}

void ATimeAgentGameModeBase::SetSlowTimeScale(float TimeScale)
{
	UE_LOG(LogTemp, Log, TEXT("SetGlobalTimeDilation"));
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeScale);
}

void ATimeAgentGameModeBase::RespawnPlayer()
{
}


void ATimeAgentGameModeBase::RespawnEnemies(int LevelNumber)
{
	LevelNumber;
}

void ATimeAgentGameModeBase::EnableSlowMotion()
{
	bInSlowMotion = true;
}

void ATimeAgentGameModeBase::DisableSlowMotion()
{
	bInSlowMotion = false;
}

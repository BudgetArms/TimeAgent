// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeAgentGameModeBase.h"

#include "Kismet/GameplayStatics.h"


ATimeAgentGameModeBase::ATimeAgentGameModeBase()
{
	
}


void ATimeAgentGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsInSlowMotion())
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), SlowMotionTimeScale);
	else
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	
}

void ATimeAgentGameModeBase::Tick(float elapsedSec)
{
	Super::Tick(elapsedSec);
	
	
	
}

void ATimeAgentGameModeBase::ToggleSlowdownTime()
{
	if (IsInSlowMotion())
		Mode = TimeState::NoSlowMotion;		
	else
		Mode = TimeState::SlowMotion;		
		
	if (IsInSlowMotion())
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), SlowMotionTimeScale);
	else
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	
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

void ATimeAgentGameModeBase::SpawnPlayer(const FVector3f& Position)
{
	Position;	
	// UWorld::SpawnActor()
	
}

void ATimeAgentGameModeBase::SpawnEnemy(const FVector3f& Position)
{
	Position;
}

bool ATimeAgentGameModeBase::IsInSlowMotion() const
{
	// if (!Player)	
	// 	return false;
	
	if (Mode == TimeState::NoSlowMotion)
		return false;
	
	return true;
}

	
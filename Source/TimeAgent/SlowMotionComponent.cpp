// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowMotionComponent.h"

#include "TimeAgentGameModeBase.h"
#include "TimeAgentPlayer.h"
#include "VectorUtil.h"
#include "Kismet/GameplayStatics.h"


USlowMotionComponent::USlowMotionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USlowMotionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	const AActor* Owner = GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner not found"));
		return;
	}
	
	MaterialInstanceDynamic = Cast<ATimeAgentPlayer>(GetOwner())->GetSlowMotionPostProcessMaterial();
	if (!MaterialInstanceDynamic)
	{
		UE_LOG(LogTemp, Error, TEXT("SlowMotionComponent: MaterialInstanceDynamic not found"));
		return;
	}
	
	MaterialInstanceDynamic->GetScalarParameterValue(RadiusParamName, DefaultVignetteRadius);
	
	StopSlowMotion();
}

void USlowMotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (!bIsSlowMotionEnabled)
	{
		return;	
	}
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	ElapsedSlowDownTime += DeltaTime / GetWorld()->GetAuthGameMode<ATimeAgentGameModeBase>()->GetSlowTimeScale();
	UE_LOG(LogTemp, Verbose, TEXT("%f"), ElapsedSlowDownTime)
	
	if (ElapsedSlowDownTime >= SlowMotionDuration - SlowDownVisuallyFadingTime)
	{
		FadeOverlay();
		
		if (ElapsedSlowDownTime >= SlowMotionDuration)
		{
			StopSlowMotion();
		}
	}

}

void USlowMotionComponent::StartSlowMotion()
{
	bIsSlowMotionEnabled = true;
	OpacityOverlay = 100.f;
	ElapsedSlowDownTime = 0.f;
	
	const float TimeScale = GetWorld()->GetAuthGameMode<ATimeAgentGameModeBase>()->GetSlowTimeScale();
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeScale); 
	
	MaterialInstanceDynamic->SetScalarParameterValue(OpacityParamName, 1.f);
	
	GetOwner<ATimeAgentPlayer>()->PlaySound(StartSound);	
}

void USlowMotionComponent::StopSlowMotion()
{
	bIsSlowMotionEnabled = false;
	OpacityOverlay = 0.f;	
	ElapsedSlowDownTime = 0.f;
	
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	
	MaterialInstanceDynamic->SetScalarParameterValue(OpacityParamName, 0.f);
	
	GetOwner<ATimeAgentPlayer>()->PlaySound(EndSound);	

}

bool USlowMotionComponent::IsInSlowMotion() const
{
	return bIsSlowMotionEnabled;
}

void USlowMotionComponent::FadeOverlay()
{
	const float OpacityToRemovePerSecond = 100.f / SlowMotionDuration;
	OpacityOverlay -= OpacityToRemovePerSecond * GetWorld()->GetDeltaSeconds(); 
	OpacityOverlay = FMathf::Clamp(OpacityOverlay, 0.f, 1.f);
	MaterialInstanceDynamic->SetScalarParameterValue(OpacityParamName, OpacityOverlay);
}


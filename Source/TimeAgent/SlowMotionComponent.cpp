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

	if (const AActor* Owner = GetOwner(); !Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner not found"));
		return;
	}
	
	PostProcessMID = Cast<ATimeAgentPlayer>(GetOwner())->GetSlowMotionPostProcessMaterial();
	if (!PostProcessMID)
	{
		UE_LOG(LogTemp, Error, TEXT("SlowMotionComponent: MaterialInstanceDynamic not found"));
		return;
	}
		
	PostProcessMID->SetScalarParameterValue(RadiusParamName, VignetteRadius);
	PostProcessMID->SetScalarParameterValue(OpacityParamName, 0.f);
	
	if (!StartSound)
	{
		UE_LOG(LogTemp, Error, TEXT("SlowMotionComponent: StartSound not found"));
		return;
	}
	if (!EndSound)
	{
		UE_LOG(LogTemp, Error, TEXT("SlowMotionComponent: EndSound not found"));
		return;
	}
	
	StopSlowMotion(false);
}

void USlowMotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (bIsInfinite || !bIsEnabled)
	{
		return;	
	}
	
	if (bIsCoolDownActive)
	{
		ElapsedCooldownTime += DeltaTime;
		
		if (ElapsedCooldownTime >= Duration)
		{
			bIsCoolDownActive = false;
			ElapsedCooldownTime = 0.f;
			GetOwner<ATimeAgentPlayer>()->ShowCooldownDoneVfx();
		}
	}
	
	if (!bIsActive)
	{
		return;
	}
	
	ElapsedSlowMotionTime += DeltaTime / GetWorld()->GetAuthGameMode<ATimeAgentGameModeBase>()->GetSlowTimeScale();
	UE_LOG(LogTemp, Verbose, TEXT("%f"), ElapsedSlowMotionTime)
	
	if (ElapsedSlowMotionTime >= Duration - VisuallyFadingTime)
	{
		FadeOverlay();
		
		if (ElapsedSlowMotionTime >= Duration)
		{
			StopSlowMotion();
		}
	}

}

void USlowMotionComponent::TryActiveSlowMotion()
{
	if (bIsCoolDownActive || !bIsEnabled)
	{
		return;	
	}
	
	StartSlowMotion();
}

void USlowMotionComponent::StartSlowMotion(bool bIsInfiniteSlowMotion)
{
	bIsInfinite = bIsInfiniteSlowMotion;	
	bIsEnabled = true;
	bIsActive = true;
	OpacityOverlay = StartOpacityOverlay;
	ElapsedCooldownTime = 0.f;
	ElapsedSlowMotionTime = 0.f;
	
	const float TimeScale = GetWorld()->GetAuthGameMode<ATimeAgentGameModeBase>()->GetSlowTimeScale();
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeScale); 
	
	PostProcessMID->SetScalarParameterValue(OpacityParamName, StartOpacityOverlay);
	
	GetOwner<ATimeAgentPlayer>()->PlaySound(StartSound);	
}

void USlowMotionComponent::StopSlowMotion(bool bPlaySound)
{
	bIsCoolDownActive = true;
	bIsActive = false;
	bIsInfinite = false;
	OpacityOverlay = 0.f;	
	ElapsedCooldownTime = 0.f;
	ElapsedSlowMotionTime = 0.f;
	
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	
	PostProcessMID->SetScalarParameterValue(OpacityParamName, 0.f);
	
	if(bPlaySound)
	{
		GetOwner<ATimeAgentPlayer>()->PlaySound(EndSound);	
	}

}

bool USlowMotionComponent::IsInSlowMotion() const
{
	return bIsEnabled && bIsActive;
}

bool USlowMotionComponent::IsInCooldown() const
{
	return bIsCoolDownActive;
}

bool USlowMotionComponent::IsEnabled() const
{
	return bIsEnabled;
}

void USlowMotionComponent::Enable()
{
	bIsEnabled = true;
}

void USlowMotionComponent::FadeOverlay()
{
	const float OpacityToRemovePerSecond = 7.f / Duration;
	OpacityOverlay -= OpacityToRemovePerSecond * GetWorld()->GetDeltaSeconds(); 
	OpacityOverlay = FMathf::Clamp(OpacityOverlay, 0.f, 1.f);
	PostProcessMID->SetScalarParameterValue(OpacityParamName, OpacityOverlay);
	
	UE_LOG(LogTemp, Verbose, TEXT("OpacityOverlay: %f"), OpacityOverlay)
}


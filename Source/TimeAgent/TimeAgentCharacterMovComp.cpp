// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeAgentCharacterMovComp.h"

#include "TimeAgentGameModeBase.h"

void UTimeAgentCharacterMovComp::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	// if not in slowmode, normal
	if (!GetWorld()->GetAuthGameMode<ATimeAgentGameModeBase>()->IsInSlowMotion())
	{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		bFirstFrameInSlowMotion = true;
		return;	
	}
	
	
	if (bFirstFrameInSlowMotion)
	{
		bFirstFrameInSlowMotion = false;
		
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		return;
	}
	
	const float TimeScale = GetWorld()->GetAuthGameMode<ATimeAgentGameModeBase>()->GetSlowTimeScale();
	Super::TickComponent(DeltaTime / TimeScale, TickType, ThisTickFunction);
	
}

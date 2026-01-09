// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimeAgentCharacterMovComp.generated.h"

/**
 * 
 */
UCLASS()
class TIMEAGENT_API UTimeAgentCharacterMovComp : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

private:
	float LastRealTime{ 0.0f };
	
	bool bFirstFrameInSlowMotion{ false };
	
	
};


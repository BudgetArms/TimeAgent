// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimeAgentCharacter.h"
#include "TimeAgentEnemy.generated.h"

/**
 * 
 */
UCLASS()
class TIMEAGENT_API ATimeAgentEnemy : public ATimeAgentCharacter
{
	GENERATED_BODY()
	
public:
	ATimeAgentEnemy();

protected:
	virtual void BeginPlay() override;
	
	
protected:
	
	
};

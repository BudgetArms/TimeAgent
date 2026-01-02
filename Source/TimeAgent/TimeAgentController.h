// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TimeAgentController.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class TIMEAGENT_API ATimeAgentController : public APlayerController
{
	GENERATED_BODY()

public:
	ATimeAgentController() = default;
	
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess=true))
	TArray<UInputMappingContext*> InputMappingContexts;
};

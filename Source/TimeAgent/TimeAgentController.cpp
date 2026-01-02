// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeAgentController.h"
#include "EnhancedInputSubsystems.h"


void ATimeAgentController::BeginPlay()
{
	Super::BeginPlay();

	if (InputMappingContexts.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Player Input Mappings are not set"));
		return;
	}

	if (!IsLocalPlayerController())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller is not Local, so cannot setup input"));
		return;
	}


	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (const UInputMappingContext* InputMappingContext : InputMappingContexts)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "TimeAgentCharacter.h"
#include "TimeAgentPlayer.generated.h"

class UCameraComponent;
/**
 * 
 */
UCLASS(abstract)
class TIMEAGENT_API ATimeAgentPlayer : public ATimeAgentCharacter
{
	GENERATED_BODY()

public:
	ATimeAgentPlayer();
	
	
protected:
	
	UPROPERTY(EditAnywhere, Category="Camera", meta=(AllowPrivateAccess=true))
	UCameraComponent* Camera;
	
	
	UFUNCTION()
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	virtual void MoveInput(const FInputActionValue& Value);
	
	UFUNCTION()
	virtual void LookInput(const FInputActionValue& Value);
		
	UFUNCTION()
	virtual void JumpStart(const FInputActionValue& Value);

	UFUNCTION()
	virtual void JumpEnd(const FInputActionValue& Value);
	
	
	void Move(const float Forward, const float Right);
	
	void Look(const float Yaw, const float Pitch);
	
	
	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* MoveAction;
		
	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* ShootAction;
		
	
};

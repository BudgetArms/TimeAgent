// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "TimeAgentCharacter.h"
#include "TimeAgentPlayer.generated.h"

class USlowMotionComponent;
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

	virtual void OnConstruction(const FTransform& Transform) override;
	
	UMaterialInstanceDynamic* GetSlowMotionPostProcessMaterial() const;
	
	UFUNCTION(BlueprintImplementableEvent, Category="Player|SlowMotion")
	void PlaySound(USoundBase* SoundBase);
	
	UFUNCTION(BlueprintImplementableEvent, Category="Player|SlowMotion")
	void ShowCooldownDoneVfx();
	
	UFUNCTION(BlueprintCallable, Category="Player|SlowMotion")
	FVector GetLookDirection() const;
		
	UFUNCTION(BlueprintCallable, Category="Player|SlowMotion", meta=(ToolTip="Get aim direction + sway (if moving)"))
	FVector GetBulletDirection() const;
	

	UFUNCTION(BlueprintCallable)
	void SetSlowMotionComponent(USlowMotionComponent* NewSlowMotionComponent);
	
protected:
	
	virtual void BeginPlay() override;
	
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
	
	void AddPostProcessingMaterial();

	UPROPERTY(EditAnywhere, Category="Player|Camera", meta=(AllowPrivateAccess=true))
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category="Player|Input", meta=(AllowPrivateAccess=true))
	UInputAction* MoveAction;
		
	UPROPERTY(EditAnywhere, Category="Player|Input", meta=(AllowPrivateAccess=true))
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, Category="Player|Input", meta=(AllowPrivateAccess=true))
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, Category="Player|Input", meta=(AllowPrivateAccess=true))
	UInputAction* ShootAction;
		

	UPROPERTY(EditDefaultsOnly, Category="Player|Effects")
	UMaterialInstance* PostProcessMI;
		
	UPROPERTY()
	UMaterialInstanceDynamic* PostProcessMID;
	
	UPROPERTY(EditAnywhere, Category="Player|Effects", meta=(AllowPrivateAccess=true))
	USlowMotionComponent* SlowMotionComp;
	
	
	UPROPERTY(BlueprintReadWrite, Category="Player|Effects", meta=(AllowPrivateAccess=true))
	bool bPickedUpGlove{ false };
		
	UPROPERTY(EditAnywhere, Category="Player|Effects", meta=(AllowPrivateAccess=true, ToolTip="X movement"))
	float MovingSway{ 0.2f };
	
	UPROPERTY(EditAnywhere, Category="Player|Effects", meta=(AllowPrivateAccess=true, ToolTip="Y movement"))
	float MovingSurge{ 0.2f };
	
	UPROPERTY(EditAnywhere, Category="Player|Effects", meta=(AllowPrivateAccess=true, ToolTip="Z movement"))
	float MovingHeave{ 0.2f };
	
	
	
};

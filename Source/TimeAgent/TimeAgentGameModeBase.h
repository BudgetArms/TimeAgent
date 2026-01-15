// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimeAgentGameModeBase.generated.h"

class USlowMotionComponent;
class ATimeAgentPlayer;
/**
 * 
 */
UCLASS()
class TIMEAGENT_API ATimeAgentGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void Tick(float elapsedSec) override;

	bool IsInSlowMotion() const;	
	
	UFUNCTION(BlueprintCallable)
	void ToggleSlowdownTime();
	
	UFUNCTION(BlueprintCallable)
	void TryToggleSlowdownTime();

	UFUNCTION(BlueprintCallable)
	float GetSlowTimeScale() const;

	UFUNCTION(BlueprintCallable)
	void SetSlowTimeScale(float TimeScale);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RespawnPlayer();
	
	void EnableSlowMotion()	const;
	void DisableSlowMotion() const;
	
	
private:

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true), EditAnywhere)
	float SlowMotionTimeScale{ 0.1f };

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	ATimeAgentPlayer* Player{ nullptr };
	
	UPROPERTY()
	USlowMotionComponent* PlayerSlowMotion{ nullptr };
	
	
};


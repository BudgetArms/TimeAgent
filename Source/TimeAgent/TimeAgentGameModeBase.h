// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimeAgentGameModeBase.generated.h"

class ATimeAgentPlayer;
/**
 * 
 */
UCLASS()
class TIMEAGENT_API ATimeAgentGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATimeAgentGameModeBase();

	virtual void BeginPlay() override;
	virtual void Tick(float elapsedSec) override;

	UFUNCTION(BlueprintCallable)
	void ToggleSlowdownTime();

	UFUNCTION(BlueprintCallable)
	float GetSlowTimeScale() const;

	UFUNCTION(BlueprintCallable)
	void SetSlowTimeScale(float TimeScale);

	UFUNCTION(BlueprintCallable)
	void SpawnPlayer(const FVector3f& Position);
	
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy(const FVector3f& Position);

	
private:

	enum class TimeState
	{
		NoSlowMotion,
		StartSlowMotion,
		SlowMotion,
		EndSlowMotion,
	};
	

	UFUNCTION(BlueprintCallable)
	bool IsInSlowMotion() const;
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true), EditAnywhere)
	float SlowMotionTimeScale{ 0.02f };

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	ATimeAgentPlayer* Player{ nullptr };
	
	TimeState Mode { TimeState::NoSlowMotion };
	
};


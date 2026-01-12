// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SlowMotionComponent.generated.h"


class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TIMEAGENT_API USlowMotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlowMotionComponent();
	
protected:
	virtual void BeginPlay() override;

	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartSlowMotion();
	void StopSlowMotion();
	
	bool IsInSlowMotion() const;
	
	
private:
	void FadeOverlay();
	
	
	bool bIsSlowMotionEnabled{ false };
	
	float OpacityOverlay{ 100.f };
	
	float ElapsedSlowDownTime{ 0.f };
	float SlowMotionDuration{ 8.f };
	float SlowDownVisuallyFadingTime{ 4.f };
	
	
	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstanceDynamic{ nullptr };
	
	FName OpacityParamName{ TEXT("Opacity") };
	FName RadiusParamName{ TEXT("Radius") };
	
	float DefaultVignetteRadius{};
	float CurrentVignetteRadius{};
	
	UPROPERTY(EditAnywhere, Category="Abilities|SlowMotion")
	float MaxVignetteRadius{ 10 };
	
	
	UPROPERTY(EditAnywhere, Category="Sounds", meta=(AllowPrivateAccess=true))
	USoundBase* StartSound{ nullptr };
	
	UPROPERTY(EditAnywhere, Category="Sounds", meta=(AllowPrivateAccess=true))
	USoundBase* EndSound{ nullptr };
	
	
};

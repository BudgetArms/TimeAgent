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

	
	UFUNCTION(Blueprintcallable, Category="SlowMotion")
	void TryActiveSlowMotion();
	
	UFUNCTION(Blueprintcallable, Category="SlowMotion")
	void StartSlowMotion(bool bIsInfinity = false);
	
	UFUNCTION(Blueprintcallable, Category="SlowMotion")
	void StopSlowMotion(bool bPlaySound = true);
	
	UFUNCTION(BlueprintCallable, Category="SlowMotion")
	bool IsInSlowMotion() const;
	
	UFUNCTION(BlueprintCallable, Category="SlowMotion")
	bool IsInCooldown() const;
	
	UFUNCTION(BlueprintCallable, Category="SlowMotion")
	bool IsEnabled() const;
		
	UFUNCTION(BlueprintCallable, Category="SlowMotion")
	void Enable();
	
	
private:

	void FadeOverlay();
	
	bool bIsInfinite{ false };
	bool bIsEnabled{ false };
	bool bIsActive{ false };
	bool bIsCoolDownActive{ false };
	
	float OpacityOverlay{};
	
	UPROPERTY(EditAnywhere, Category="SlowMotion")
	float StartOpacityOverlay{ 0.76f };
		
	UPROPERTY(EditAnywhere, Category="SlowMotion")
	float VignetteRadius{ 0.6f };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SlowMotion", meta=(AllowPrivateAccess=true))
	float ElapsedSlowMotionTime{ 0.f };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SlowMotion", meta=(AllowPrivateAccess=true))
	float Duration{ 8.f };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SlowMotion", meta=(AllowPrivateAccess=true))
	float VisuallyFadingTime{ 5.f };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SlowMotion", meta=(AllowPrivateAccess=true))
	float CooldownTime{ 5.f };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SlowMotion", meta=(AllowPrivateAccess=true))
	float ElapsedCooldownTime{};
	
	
	UPROPERTY()
	UMaterialInstanceDynamic* PostProcessMID{ nullptr };
	
	FName OpacityParamName{ TEXT("Opacity") };
	FName RadiusParamName{ TEXT("Radius") };

	
	UPROPERTY(EditAnywhere, Category="Sounds", meta=(AllowPrivateAccess=true))
	USoundBase* StartSound{ nullptr };
	
	UPROPERTY(EditAnywhere, Category="Sounds", meta=(AllowPrivateAccess=true))
	USoundBase* EndSound{ nullptr };
	
	
};

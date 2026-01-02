// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimeAgentCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)

UCLASS(abstract)
class TIMEAGENT_API ATimeAgentCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATimeAgentCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnDeath();

	virtual void DealDamage(float damage, AActor* damageSource);
	
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category="Health")
	bool bIsDead { false };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float MaxHealth { 100.f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float Health{ MaxHealth };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	AActor* DamageSource { nullptr };

};


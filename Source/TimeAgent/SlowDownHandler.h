// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TIMEAGENT_API SlowDownHandler
{
public:
	SlowDownHandler();
	~SlowDownHandler();
	
	void StartSlowMotion();
	void StopSlowMotion();
	
	bool IsInSlowMotion() const;
	
private:
	void UpdateSlowDown();
	void FadeOverlay();
	
	
	bool bIsSlowMotionEnabled{ false };
	
	float OpacityOverlay{ 100.f };
	
	float ElapsedSlowDownTime{ 0.f };
	float SlowDownDuration{ 10.f };
	float SlowDownVisuallyFadingTime{ 2.f };
	
};

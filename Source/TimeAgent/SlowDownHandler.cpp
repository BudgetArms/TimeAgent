// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowDownHandler.h"

SlowDownHandler::SlowDownHandler()
{
	
}

SlowDownHandler::~SlowDownHandler()
{
	
}

void SlowDownHandler::StartSlowMotion()
{
	bIsSlowMotionEnabled = true;
	OpacityOverlay = 100.f;
	ElapsedSlowDownTime = 0.f;
	
}

void SlowDownHandler::StopSlowMotion()
{
	bIsSlowMotionEnabled = false;
	OpacityOverlay = 0.f;	
	ElapsedSlowDownTime = 0.f;
	
	
}

bool SlowDownHandler::IsInSlowMotion() const
{
	return bIsSlowMotionEnabled;
}

void SlowDownHandler::UpdateSlowDown()
{
	if (!bIsSlowMotionEnabled)
	{
		return;	
	}
	
	// fucked way, but okay
	ElapsedSlowDownTime += FApp::GetDeltaTime();
	
	if (ElapsedSlowDownTime >= SlowDownDuration - SlowDownVisuallyFadingTime)
	{
		FadeOverlay();
		
		if (ElapsedSlowDownTime >= SlowDownDuration)
		{
			StopSlowMotion();
		}
	}
	
}

void SlowDownHandler::FadeOverlay()
{
	OpacityOverlay = (1 - ElapsedSlowDownTime / (SlowDownDuration - SlowDownVisuallyFadingTime));
}


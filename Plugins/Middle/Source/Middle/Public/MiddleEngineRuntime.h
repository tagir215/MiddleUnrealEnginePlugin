// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <memory>
#include "middle_state.h"
#include "MiddleUnrealInputSystem.h"

/**
 * 
 */
class MIDDLE_API MiddleEngineRuntime
{
public:
	MiddleEngineRuntime();
	void Initialize(UWorld* World);
	void Tick(UWorld* World, float deltaTime);
	void ShutDown();
	~MiddleEngineRuntime();
private:
	middle::MiddleOutputState* outputStatePtr = nullptr;
	middle::MiddleInputState inputState;
	bool gameMode = false;
	MiddleUnrealInputSystem inputSystem;
};

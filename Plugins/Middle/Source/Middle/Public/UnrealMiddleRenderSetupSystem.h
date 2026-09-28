// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "middle_state.h"

/**
 * 
 */
class MIDDLE_API UnrealMiddleRenderSetupSystem
{
public:
	UnrealMiddleRenderSetupSystem();
	~UnrealMiddleRenderSetupSystem();
	static void Update(UWorld* World, const middle::MiddleOutputState* const middleOutputState, middle::MiddleInputState* inputState);
};

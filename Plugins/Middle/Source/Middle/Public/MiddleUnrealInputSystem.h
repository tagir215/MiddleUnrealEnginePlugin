// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "middle_state.h"
#include "InputCoreTypes.h"


class APlayerController;

/**
 * 
 */
class MIDDLE_API MiddleUnrealInputSystem
{
public:
	MiddleUnrealInputSystem();
	~MiddleUnrealInputSystem();

public:

    void Update(UWorld* World, const middle::MiddleOutputState* output,
        middle::MiddleInputState& input);

private:
    APlayerController* PlayerController = nullptr;

private:
    bool IsDown(FKey key) const;
    bool WasPressed(FKey key) const;
    bool WasReleased(FKey key) const;

    bool KeyboardBlocked(
        const middle::MiddleOutputState* output) const;

    bool MouseBlocked(
        const middle::MiddleOutputState* output) const;
};

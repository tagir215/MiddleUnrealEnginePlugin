// Fill out your copyright notice in the Description page of Project Settings.
#include "MiddleEngineRuntime.h"
#include "UnrealMiddleRenderSetupSystem.h"
#include "game.h"
#include "MiddleUnrealInputSystem.h"

PRAGMA_DISABLE_OPTIMIZATION

MiddleEngineRuntime::MiddleEngineRuntime()
{
}

MiddleEngineRuntime::~MiddleEngineRuntime()
{
}


void MiddleEngineRuntime::Initialize(UWorld* World) {
	//SetTargetFPS(fps);
}

void MiddleEngineRuntime::Tick(UWorld* World, float deltaTime) {
	// Update
	//----------------------------------------------------------------------------------
	// TODO: Update your variables here
	//----------------------------------------------------------------------------------
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	const int fps = 120;
	GEngine->SetMaxFPS(fps);
	const float fixedTimeStep = 1.0f / (float)fps;
	inputState.screenWidth = ViewportSize.X;
	inputState.screenHeight = ViewportSize.Y;
	inputState.nearPlaneDistance = GNearClippingPlane;
	inputState.targetFrameTime = fixedTimeStep;
	inputState.frameTime = deltaTime;

	auto pc = World->GetFirstPlayerController();
	if (pc) {
		pc->SetShowMouseCursor(true);

		// 1. Get the camera's active view properties (handles tracking, blends, and cutscenes)
		FMinimalViewInfo ActiveView = pc->PlayerCameraManager->GetCameraCacheView();

		float fovy = 0.0f;

		// 2. Check if the engine is constraining the camera vertically or horizontally
		if (ActiveView.bConstrainAspectRatio || ActiveView.ProjectionMode == ECameraProjectionMode::Perspective)
		{
			// If the active camera scales vertically, the base FOV value IS already the FOV Y.
			if (ActiveView.AspectRatioAxisConstraint == EAspectRatioAxisConstraint::AspectRatio_MaintainYFOV)
			{
				fovy = ActiveView.FOV;
			}
			else
			{
				// If it maintains Horizontal (X) FOV, convert X to Y using the Aspect Ratio
				// Formula: FOV_Y = 2 * atan(tan(FOV_X / 2) / AspectRatio)
				float RadX = FMath::DegreesToRadians(ActiveView.FOV);
				float RadY = 2.0f * FMath::Atan(FMath::Tan(RadX / 2.0f) / ActiveView.AspectRatio);

				fovy = FMath::RadiansToDegrees(RadY);
			}

			inputState.cameraFOVY = fovy;
		}

	}

	inputSystem.Update(World, outputStatePtr, inputState);

	UpdateGame(inputState, &outputStatePtr);

	UnrealMiddleRenderSetupSystem::Update(World, outputStatePtr, &inputState);
}

void MiddleEngineRuntime::ShutDown() {
	inputState.closeGame = true;
	UpdateGame(inputState, &outputStatePtr);
}

PRAGMA_ENABLE_OPTIMIZATION

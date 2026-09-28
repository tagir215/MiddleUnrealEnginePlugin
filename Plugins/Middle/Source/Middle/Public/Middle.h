// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "MiddleEngineRuntime.h"
#include <memory>
#include "MiddlePresentationManager.h"

class FMiddleModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void OnWorldInitialized(UWorld* World, const UWorld::InitializationValues IVS);

private:
	std::unique_ptr<MiddleEngineRuntime>Engine;
	AMiddlePresentationManager* PresentationManager;
};

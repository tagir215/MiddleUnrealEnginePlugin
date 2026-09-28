// Copyright Epic Games, Inc. All Rights Reserved.

#include "Middle.h"

#define LOCTEXT_NAMESPACE "FMiddleModule"

void FMiddleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	Engine = std::make_unique<MiddleEngineRuntime>();

	FWorldDelegates::OnPostWorldInitialization.AddRaw(
		this,
		&FMiddleModule::OnWorldInitialized
	);
}

void FMiddleModule::OnWorldInitialized(UWorld* World,
	const UWorld::InitializationValues IVS) {
	if (!World) {
		return;
	}
	if (World->WorldType != EWorldType::Game &&
		World->WorldType != EWorldType::PIE) {
		return;
	}
	PresentationManager = World->SpawnActor<AMiddlePresentationManager>();
	Engine->Initialize(World);
	PresentationManager->SetRuntimeEngine(Engine.get());
}

void FMiddleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	Engine->ShutDown();
	Engine.reset();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMiddleModule, Middle)
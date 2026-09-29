// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Middle : ModuleRules
{
	public Middle(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
				"ImGui",
				"InputCore"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);


		// MIDDLE STUFF


		//============================= DIRECT COMPILE APPROACH ===========================

		//string MiddleRoot = Path.GetFullPath(
		//	Path.Combine(ModuleDirectory, "MiddleGame"));
		//PublicIncludePaths.Add(MiddleRoot);
		//PublicIncludePaths.Add(Path.Combine(MiddleRoot, "include"));
		//PublicIncludePaths.Add(Path.Combine(MiddleRoot, "game", "components"));
		//PublicIncludePaths.Add(Path.Combine(MiddleRoot, "game", "middleEntities"));


		//============================= DLL APPROACH ======================================

		string MiddleRoot = Path.GetFullPath(
			Path.Combine(ModuleDirectory, "../MiddleRepo", "middle"));

		PublicIncludePaths.Add(
			Path.Combine(MiddleRoot, "MiddleGame", "include"));

		string GameBuildDir = 
			Path.Combine(MiddleRoot, "build", "Release");
		PublicAdditionalLibraries.Add(
		    Path.Combine(GameBuildDir, "game.lib"));

		// copy dlls to win64 folder. 

		string Win64Dir = 
			Path.Combine(PluginDirectory, "Binaries", "Win64");
		RuntimeDependencies.Add(
			Path.Combine(Win64Dir, "game.dll"),
			Path.Combine(GameBuildDir, "game.dll")
			);
	}
}

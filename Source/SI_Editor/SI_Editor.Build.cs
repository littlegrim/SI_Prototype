﻿using UnrealBuildTool;

public class SI_Editor : ModuleRules
{
    public SI_Editor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "GameplayTags",
                "UMG",
                "UnrealEd",
                
                // Spade Investigations
                "SI_Prototype",
                "SI_CsvDataProcessor",

                // Little Grim
                "LGCoreLibrary",
                "LGCsvDataProcessor",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Blutility",
                "CoreUObject",
                "Engine",
                "InputCore",
                "LevelEditor",
                "PropertyEditor",
                "Slate",
                "SlateCore",
            }
        );
    }
}
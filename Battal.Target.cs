// Battal

using UnrealBuildTool;
using System.Collections.Generic;

public class BattalTarget : TargetRules
{
	public BattalTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "Battal" } );
	}
}

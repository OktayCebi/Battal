// Battal

using UnrealBuildTool;
using System.Collections.Generic;

public class BattalEditorTarget : TargetRules
{
	public BattalEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "Battal" } );
	}
}

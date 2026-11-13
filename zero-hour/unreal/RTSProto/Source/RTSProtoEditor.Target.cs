using UnrealBuildTool;

public class RTSProtoEditorTarget : TargetRules
{
	public RTSProtoEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("RTSProto");
	}
}

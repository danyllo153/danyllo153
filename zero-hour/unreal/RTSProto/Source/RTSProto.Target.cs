using UnrealBuildTool;

public class RTSProtoTarget : TargetRules
{
	public RTSProtoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("RTSProto");
	}
}

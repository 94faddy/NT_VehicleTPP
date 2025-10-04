class CfgPatches
{
	class VehicleTPP_Scripts
	{
		requiredAddons[]={};
		units[]={};
		weapons[]={};
	};
};
class CfgMods
{
	class VehicleTPP
	{
		type="mod";
		author="Nightro";
		dir="NT_VehicleTPP";
		name="VehicleTPP";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				files[]=
				{
					"NT_VehicleTPP/Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				files[]=
				{
					"NT_VehicleTPP/Scripts/4_World"
				};
			};
			class missionScriptModule
			{
				files[]=
				{
					"NT_VehicleTPP/Scripts/5_Mission"
				};
			};
		};
	};
};
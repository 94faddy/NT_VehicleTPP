class CfgPatches
{
	class VehicleTPP_Scripts
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = 
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class VehicleTPP
	{
		dir = "NT_VehicleTPP";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "VehicleTPP";
		credits = "Nightro";
		author = "Nightro";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		
		dependencies[] = 
		{
			"Game",
			"World",
			"Mission"
		};
		
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = 
				{
					"NT_VehicleTPP/Scripts/3_Game"
				};
			};
			
			class worldScriptModule
			{
				value = "";
				files[] = 
				{
					"NT_VehicleTPP/Scripts/4_World"
				};
			};
			
			class missionScriptModule
			{
				value = "";
				files[] = 
				{
					"NT_VehicleTPP/Scripts/5_Mission"
				};
			};
		};
	};
};
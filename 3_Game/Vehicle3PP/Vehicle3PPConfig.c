class Vehicle3PPConfig
{
	bool DriverOnly = true;
	ref array<string> Whitelist = new array<string>;

	[NonSerialized()]
	static const string ConfigDir = "$profile:NT-VehicleTPPConfig";
	[NonSerialized()]
	static const string ConfigPath = "$profile:NT-VehicleTPPConfig/VehicleConfig.json";

	void Vehicle3PPConfig()
	{
		// Initialize array
		Whitelist = new array<string>;
	}

	void Init()
	{
		if (GetGame().IsServer() || GetGame().IsDedicatedServer())
		{
			// Create directory if it doesn't exist
			if (!FileExist(ConfigDir))
			{
				Print("[VehicleTPP] Creating config directory: " + ConfigDir);
				MakeDirectory(ConfigDir);
			}

			// Check if config exists
			if (FileExist(ConfigPath))
			{
				// Load existing config
				JsonFileLoader<Vehicle3PPConfig>.JsonLoadFile(ConfigPath, this);
				Print("[VehicleTPP] Configuration loaded from: " + ConfigPath);
			}
			else
			{
				// Create default config
				Print("[VehicleTPP] Config file not found, creating default...");
				Default();
			}
		}
	}

	void Save()
	{
		if (GetGame().IsServer() || GetGame().IsDedicatedServer())
		{
			// Ensure directory exists
			if (!FileExist(ConfigDir))
			{
				MakeDirectory(ConfigDir);
			}

			JsonFileLoader<Vehicle3PPConfig>.JsonSaveFile(ConfigPath, this);
			Print("[VehicleTPP] Configuration saved to: " + ConfigPath);
		}
	}

	void Default()
	{
		Print("[VehicleTPP] Loading default configuration...");

		DriverOnly = true;
		
		Whitelist.Clear();
		Whitelist.Insert("OffroadHatchback");
		Whitelist.Insert("Hatchback_02");
		Whitelist.Insert("CivilianSedan");
		Whitelist.Insert("Sedan_02");
		Whitelist.Insert("Truck_01_Covered");

		Save();
	}

	array<string> GetWhitelist()
	{
		if (!Whitelist)
			Whitelist = new array<string>;
			
		return Whitelist;
	}

	bool IsDriverOnly()
	{
		return DriverOnly;
	}
}

// Global config instance
static ref Vehicle3PPConfig g_Vehicle3PPConfig;

static ref Vehicle3PPConfig GetVehicle3PPConfig()
{
	if (!g_Vehicle3PPConfig)
	{
		g_Vehicle3PPConfig = new Vehicle3PPConfig();
		g_Vehicle3PPConfig.Init();
	}

	return g_Vehicle3PPConfig;
}
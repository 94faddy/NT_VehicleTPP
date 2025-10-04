class Vehicle3PPConfig
{
	protected string DriverOnly;
	protected ref array<string> Whitelist = {};

	[NonSerialized()]
	protected const string ConfigPath = "$profile:NT-VehicleTPPConfig.json";

	void Init()
	{
		if (GetGame().IsDedicatedServer())
		{
			if (!FileExist(ConfigPath))
				Default();

			JsonFileLoader<Vehicle3PPConfig>.JsonLoadFile(ConfigPath, this);
		}
	}

	void Save()
	{
		JsonFileLoader<Vehicle3PPConfig>.JsonSaveFile(ConfigPath, this);
	}

	void Default()
	{
		Print("[VehicleTPP] Loading default configuration...");

		DriverOnly = "true";
		Whitelist = {
			"OffroadHatchback",
			"Hatchback_02",
			"CivilianSedan",
			"Sedan_02",
			"Truck_01_Covered"
		};

		Save();
	}

	array<string> GetWhitelist()
	{
		return Whitelist;
	}

	bool IsDriverOnly()
	{
		return DriverOnly != "false";
	}

	protected array<string> ReadFileLines(string path)
	{
		FileHandle file;
		string line;

		array<string> contents = {};
		file = OpenFile(path, FileMode.READ);
		while (FGets(file, line) > 0)
		{
			line.Trim();
			if (line != string.Empty)
			{
				contents.Insert(line);
				line = string.Empty;
			}
		}

		CloseFile(file);
		return contents;
	}
}

// global access config \o/
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
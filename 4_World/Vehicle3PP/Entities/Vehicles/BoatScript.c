modded class BoatScript
{
	protected bool m_Allow3PPCamera = false;
	protected bool m_DriverOnly = true;

	void BoatScript()
	{
		// Network sync variables for client-server communication
		RegisterNetSyncVariableBool("m_Allow3PPCamera");
		RegisterNetSyncVariableBool("m_DriverOnly");
	}

	override void EEInit()
	{
		super.EEInit();
		
		if (GetGame().IsServer() || GetGame().IsDedicatedServer())
		{
			Vehicle3PPConfig config = GetVehicle3PPConfig();
			if (!config)
			{
				Print("[VehicleTPP] ERROR: Config is null in BoatScript.EEInit()");
				return;
			}

			m_DriverOnly = config.IsDriverOnly();
			array<string> vehicles = config.GetWhitelist();

			// If no vehicles in whitelist, allow 3PP for all
			if (!vehicles || vehicles.Count() == 0)
			{
				m_Allow3PPCamera = true;
				Print("[VehicleTPP] Empty whitelist - allowing 3PP for: " + this.GetType());
			}
			else
			{
				// Check if this vehicle is in whitelist
				string vehicleType = this.GetType();
				
				foreach (string allowedVehicle : vehicles)
				{
					// Check by type name, inheritance, or KindOf
					if (vehicleType == allowedVehicle || 
					    IsInherited(allowedVehicle.ToType()) || 
					    KindOf(allowedVehicle))
					{
						m_Allow3PPCamera = true;
						Print("[VehicleTPP] Allowing 3PP for boat: " + vehicleType);
						break;
					}
				}
				
				if (!m_Allow3PPCamera)
				{
					Print("[VehicleTPP] Denying 3PP for boat: " + vehicleType);
				}
			}

			SetSynchDirty();
		}
	}

	bool Can3PPCamera()
	{
		return m_Allow3PPCamera;
	}

	bool IsDriverOnly()
	{
		return m_DriverOnly;
	}
}
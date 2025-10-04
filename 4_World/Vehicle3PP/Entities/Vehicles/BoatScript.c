modded class BoatScript
{
	protected bool m_Allow3PPCamera;
	protected bool m_DriverOnly;

	void BoatScript()
	{
		// i'm too lazy to do RPCs so lets network camera availability to all vehicles
		RegisterNetSyncVariableBool("m_Allow3PPCamera");
		RegisterNetSyncVariableBool("m_DriverOnly");
	}

	override void EEInit()
	{
		if (GetGame().IsDedicatedServer())
		{
			array<string> vehicles = GetVehicle3PPConfig().GetWhitelist();
			m_DriverOnly = GetVehicle3PPConfig().IsDriverOnly();

			// if no vehicles are specified all 3PP for all
			if (vehicles && vehicles.Count() < 1)
			{
				m_Allow3PPCamera = true;
			}
			else
			{
				foreach (string vehicle : vehicles)
				{
					if (IsInherited(vehicle.ToType()) || (vehicle == GetType() || KindOf(vehicle)))
					{
						m_Allow3PPCamera = true;
						break;
					}
				}
			}

			SetSynchDirty();
		}

		super.EEInit();
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

modded class DayZPlayerImplement
{
	protected bool m_Vehicle3rdPerson = false;

	override int CameraHandler(int pCameraMode)
	{
		HumanCommandVehicle vehicleCommand = GetCommand_Vehicle();
		
		if (vehicleCommand)
		{
			Transport vehicle = vehicleCommand.GetTransport();
			
			if (!vehicle)
				return super.CameraHandler(pCameraMode);

			// Check if first person only mode
			if (V3PP_IsFirstPersonOnly(vehicle))
			{
				return DayZPlayerCameras.DAYZCAMERA_1ST_VEHICLE;
			}

			// Handle car vehicles
			CarScript car;
			if (Class.CastTo(car, vehicle))
			{
				if (!car.Can3PPCamera())
					return DayZPlayerCameras.DAYZCAMERA_1ST_VEHICLE;
					
				if (!m_Vehicle3rdPerson && !m_Camera3rdPerson)
					return DayZPlayerCameras.DAYZCAMERA_1ST_VEHICLE;
				
				return vehicle.Get3rdPersonCameraType();
			}

			// Handle boat vehicles
			BoatScript boat;
			if (Class.CastTo(boat, vehicle))
			{
				if (!boat.Can3PPCamera())
					return DayZPlayerCameras.DAYZCAMERA_1ST_VEHICLE;
					
				if (!m_Vehicle3rdPerson && !m_Camera3rdPerson)
					return DayZPlayerCameras.DAYZCAMERA_1ST_VEHICLE;
				
				return vehicle.Get3rdPersonCameraType();
			}

			// Other vehicle types
			return vehicle.Get3rdPersonCameraType();
		}

		return super.CameraHandler(pCameraMode);
	}

	override void HandleView()
	{
		super.HandleView();

		HumanInputController hic = GetInputController();
		if (!hic)
			return;

		HumanCommandVehicle vehicleCommand = GetCommand_Vehicle();
		bool camChange = hic.CameraViewChanged();

		if (camChange && vehicleCommand)
		{
			Transport vehicle = vehicleCommand.GetTransport();
			if (!vehicle)
				return;

			// Don't allow camera change if first person only
			if (V3PP_IsFirstPersonOnly(vehicle))
				return;

			// Check if vehicle allows 3PP
			CarScript car;
			if (Class.CastTo(car, vehicle))
			{
				if (!car.Can3PPCamera())
					return;
			}

			BoatScript boat;
			if (Class.CastTo(boat, vehicle))
			{
				if (!boat.Can3PPCamera())
					return;
			}

			m_Vehicle3rdPerson = !m_Vehicle3rdPerson;
		}
	}

	void ChangeVehicleView(bool thirdPerson)
	{
		m_Vehicle3rdPerson = thirdPerson;
	}

	bool IsVehicleView3PP()
	{
		return m_Vehicle3rdPerson;
	}

	bool V3PP_IsDrivingSpecialHeli()
	{
		HumanCommandVehicle vehicleCmd = GetCommand_Vehicle();
		if (!vehicleCmd)
			return false;

		Transport vehicle = vehicleCmd.GetTransport();
		if (!vehicle)
			return false;

		// Check for special helicopter types (NW and RF)
		if (!vehicle.IsKindOf("HeliTest_SIB") && !vehicle.IsKindOf("RFFSHeli_base"))
			return false;

		// Check if this player is pilot or copilot
		DayZPlayerImplement pilot = DayZPlayerImplement.Cast(vehicle.CrewMember(0));
		DayZPlayerImplement copilot = DayZPlayerImplement.Cast(vehicle.CrewMember(1));

		return (pilot == this || copilot == this);
	}

	bool V3PP_IsFirstPersonOnly(Transport vehicle)
	{
		if (!vehicle)
			return true;

		bool isDriving = GetDrivingVehicle() || V3PP_IsDrivingSpecialHeli();

		// Check car
		CarScript car;
		if (Class.CastTo(car, vehicle))
		{
			return car.IsDriverOnly() && !isDriving;
		}

		// Check boat
		BoatScript boat;
		if (Class.CastTo(boat, vehicle))
		{
			return boat.IsDriverOnly() && !isDriving;
		}

		return false;
	}
}
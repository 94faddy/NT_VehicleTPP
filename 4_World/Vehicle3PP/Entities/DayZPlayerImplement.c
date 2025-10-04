modded class DayZPlayerImplement
{
	protected bool m_Vehicle3rdPerson;

	override int CameraHandler(int pCameraMode)
	{
		HumanCommandVehicle vehicleCommand = GetCommand_Vehicle();
		if (vehicleCommand) // check if in vehicle
		{
			Transport vehicle = vehicleCommand.GetTransport();

			// check if driver only mode is enabled, and force all passengers to first person
			if (V3PP_IsFirstPersonOnly(vehicleCommand.GetTransport()))
			{
				return DayZPlayerCameras.DAYZCAMERA_1ST_VEHICLE;
			}
			else
			{
				CarScript car;
				if (Class.CastTo(car, vehicle))
				{
					if ((!m_Vehicle3rdPerson && !m_Camera3rdPerson) || !car.Can3PPCamera())
						return DayZPlayerCameras.DAYZCAMERA_1ST_VEHICLE;
				}

				BoatScript boat;
				if (Class.CastTo(boat, vehicle))
				{
					if ((!m_Vehicle3rdPerson && !m_Camera3rdPerson) || !boat.Can3PPCamera())
						return DayZPlayerCameras.DAYZCAMERA_1ST_VEHICLE;
				}

				return vehicle.Get3rdPersonCameraType(); // get vehicle's specified 3rd person cam, custom vehicle friendly
			}
		}

		return super.CameraHandler(pCameraMode); // propagate hierarchy if our condition above isn't met
	}

	override void HandleView()
	{
		super.HandleView(); // propagate hierarchy for vanilla view handler

		HumanInputController hic = GetInputController();
		HumanCommandVehicle vehicleCommand = GetCommand_Vehicle();

		bool camChange = hic.CameraViewChanged();

		// only allow change if in vehicle
		if (camChange && vehicleCommand)
		{
			if (V3PP_IsFirstPersonOnly(vehicleCommand.GetTransport()))
				return;

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

	// for handling NW's and RF's sillyness of vehicle commanding
	bool V3PP_IsDrivingSpecialHeli()
	{
		if (!GetCommand_Vehicle())
			return false;

		Transport vehicle = GetCommand_Vehicle().GetTransport();
		if (!vehicle)
			return false;

		if (!vehicle.IsKindOf("HeliTest_SIB") && !vehicle.IsKindOf("RFFSHeli_base"))
			return false;

		DayZPlayerImplement pilot = DayZPlayerImplement.Cast(vehicle.CrewMember(0));
		DayZPlayerImplement copilot = DayZPlayerImplement.Cast(vehicle.CrewMember(1));

		return pilot == this || copilot == this;
	}

	bool V3PP_IsFirstPersonOnly(Transport vehicle)
	{
		CarScript car;
		if (Class.CastTo(car, vehicle))
		{
			return car.IsDriverOnly() && (!GetDrivingVehicle() && !V3PP_IsDrivingSpecialHeli());
		}

		BoatScript boat;
		if (Class.CastTo(boat, vehicle))
		{
			return boat.IsDriverOnly() && (!GetDrivingVehicle() && !V3PP_IsDrivingSpecialHeli());
		}

		return true;
	}
}

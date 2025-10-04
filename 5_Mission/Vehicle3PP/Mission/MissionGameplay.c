modded class MissionGameplay
{
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);

		PlayerBase player;
		if (PlayerBase.CastTo(player, GetGame().GetPlayer()))
		{
			HumanCommandVehicle vehicleCommand = player.GetCommand_Vehicle();

			if ((!vehicleCommand || vehicleCommand.IsGettingOut()) && player.IsVehicleView3PP())
				player.ChangeVehicleView(false);
		}
	}
}

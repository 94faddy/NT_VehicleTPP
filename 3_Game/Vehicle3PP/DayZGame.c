modded class DayZGame
{
	override void DeferredInit()
	{
		super.DeferredInit();
		
		// Initialize config on server
		if (IsServer())
		{
			GetVehicle3PPConfig();
		}
	}
}
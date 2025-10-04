modded class DayZGame
{
	// load our config upon game start / as early as possible
	override void DeferredInit()
	{
		super.DeferredInit();

		GetVehicle3PPConfig();
	}
}

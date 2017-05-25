#include <Wire.h>
#include <BH1750.h>

class LightSensor {
	public:
		int GetLightLevel();
		void Init();
	private:
		BH1750 lightMeter;
};

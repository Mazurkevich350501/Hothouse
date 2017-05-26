#include <Wire.h>
#include <BH1750.h>
//датчик освещенности все стандакртное из примеров
class LightSensor {
	public:
		int GetLightLevel();
		void Init();
	private:
		BH1750 lightMeter;
};

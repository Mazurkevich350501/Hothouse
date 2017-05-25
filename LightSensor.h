#include <Wire.h>
#include <BH1750.h>

class LightSensor {
	public:
		int GetLightLevel();
		LightSensor();
    ~LightSensor(){
      delete lightMeter;
    }
	private:
		BH1750* lightMeter;
};

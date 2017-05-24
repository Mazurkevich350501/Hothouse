#include <Wire.h>
#include <BH1750.h>

class LightSensor {
	public:
		int GetLightLevel();
		void Init();
    LightSensor(){
      lightMeter = new BH1750(0x23);
    }
    ~LightSensor(){
      delete lightMeter;
    }
	private:
		BH1750* lightMeter;
};

#include <stDHT.h>

#define DHTPIN 7

//практически стандартные настройки датчика
class TemperatureAndHumiditySensor{
	public:
		float GetLastTemperature();
		float GetLastHumidity();
		void UpdateValue();
	private:
		float temperature;
		float humidity;
};

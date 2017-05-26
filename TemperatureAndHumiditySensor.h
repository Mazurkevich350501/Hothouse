#include <SimpleDHT.h>

#define DHTPIN 7
//практически стандартные настройки датчика
class TemperatureAndHumiditySensor{
	public:
		float GetLastTemperature();
		float GetLastHumidity();
		void UpdateValue();
	private:
		SimpleDHT11 dht11;
		byte temperature;
		byte humidity;
};

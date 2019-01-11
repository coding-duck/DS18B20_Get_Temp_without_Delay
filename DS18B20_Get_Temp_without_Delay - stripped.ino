#include <OneWire.h>            // OneWire library to make the OneWire bus usable
#include <DallasTemperature.h>  // DS18B20 library for the DS18B20 temperature sensor

#define TEMPERATURE_SENSOR_PIN 11
#define MEASUREMENT_DELAY_MS 1000
#define TEMP_SENSOR_RESOLUTION 12

OneWire oneWireObject(TEMPERATURE_SENSOR_PIN);          // Create OneWire object
DallasTemperature tempSensor(&oneWireObject);           // Declare temperature sensor
DeviceAddress addressTempSensor;                        // Sensor address is ascertained in findAndSetupTempSensor()

int lastRequestTime = 0;

// Ueberpruefe ob Sensoren vorhanden sind
void findAndSetupTempSensor()
{
	// Initialize temperature sensor
	tempSensor.begin();
	tempSensor.getAddress(addressTempSensor, 0);
	tempSensor.setResolution(addressTempSensor, TEMP_SENSOR_RESOLUTION);
	tempSensor.setWaitForConversion(false);   // Enables temperature polling without blocking
	tempSensor.requestTemperatures();
	delay(10);                                // A short delay is recommended after requesting the current temperature
}

float getTemperature()
{
	float temperature = tempSensor.getTempCByIndex(0);  // The index must be changed if there are more than one sensor on the same wire/input pin.
														// Tell the sensor to make a temperature conversion. This may happen a bit later.
	tempSensor.requestTemperatures();
	return temperature;
}

void setup(void) {
	Serial.begin(9600);
	findAndSetupTempSensor();
	lastRequestTime = millis();
}

void loop(void) {
	// Check if enough time has passed since last temperature request
	if (millis() >= (lastRequestTime + MEASUREMENT_DELAY_MS))
	{
		lastRequestTime = millis();
		float currentTemp = getTemperature();

		Serial.println(currentTemp);
	}
}

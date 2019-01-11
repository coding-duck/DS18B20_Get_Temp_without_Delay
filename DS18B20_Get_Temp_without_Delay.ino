#include <OneWire.h>            // OneWire library to make the OneWire bus usable
#include <DallasTemperature.h>  // DS18B20 library for the DS18B20 temperature sensor

#define TEMPERATURE_SENSOR_PIN 11
#define MEASUREMENT_DELAY_MS 1000
#define TEMP_SENSOR_RESOLUTION 12
#define DEBUG_MODE_IS_ACTIVE true

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

	bool tempSensorFound = false;

	// Check if temperature sensor can be found
	if (tempSensor.getDeviceCount() == 1)
	{
		tempSensorFound = true;
	}
	else
	{
		tempSensorFound = false;
	}

	if (DEBUG_MODE_IS_ACTIVE)
	{
		Serial.print("Temperature sensor found? ");
		Serial.println(tempSensorFound ? "YES" : "NO");
	}
}

float getTemperature()
{
	// ATTENTION!
	// A 4.7k resistor must be installed between 5V and the sense wire (pull-up resistor).

	float temperature = tempSensor.getTempCByIndex(0);  // The index must be changed if there are more than one sensor on the same wire/input pin.

	// Tell the sensor to make a temperature conversion. This may happen a bit later.
	tempSensor.requestTemperatures();

  return temperature;
}

void setup(void) {
	if (DEBUG_MODE_IS_ACTIVE)
	{
    Serial.begin(9600);
  }
	findAndSetupTempSensor();
	lastRequestTime = millis();
}

void loop(void) {
	// Check if enough time has passed since last temperature request
	if (millis() >= (lastRequestTime + MEASUREMENT_DELAY_MS))
	{
		lastRequestTime = millis();
		float currentTemp = getTemperature();

    if (DEBUG_MODE_IS_ACTIVE)
    {
      Serial.print(currentTemp);
      Serial.print(" C - (");
      Serial.print(millis());
      Serial.println(" ms)");
    }
	}
}

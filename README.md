# Sample project to get temperatures from a DS18B20 temperature sensor

## Usage

You can adjust the "constants" at the top according to your needs (e.g. lower bit rate, other pin number, etc.). The address of the temperature sensor is ascertained inside of the "findAndSetupTempSensor()" function and the "waitForConversion" is set to "false". This enables a much faster request of the temperature from the sensor.

## Stripped version

Is basically the same as the other version but without some additional info. You just get the temperature printed to the serial monitor.
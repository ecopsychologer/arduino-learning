#include <CD74HC4067.h> // mux
#include <GyverOLED.h> // 128x32 oled
#include <Wire.h> // I2C
#include <SPI.h> // serial peripherals
#include <Arduino.h>
#include <Wire.h>
#include <BMx280I2C.h> // temperature and pressure
// example code and library (I'm guessing) is copyright (c) 2018 Gregor Christandl
#include <AnalogUVSensor.h> // UV (obv)
#include <Adafruit_AHTX0.h> // two temp/humidity sensors
#include <DFRobot_ENS160.h> // gas sensor
#include <Adafruit_Sensor.h> // compass
#include <Adafruit_HMC5883_U.h> // compass
#include <SoftwareSerial.h> // for gps
#include <TinyGPS.h> // by Mikal Hart

#define I2C_ADDRESS 0x76
#define GPS_RX 3
#define GPS_TX 4

// GPS Serial Connection
TinyGPS gps;
SoftwareSerial ss(GPS_TX, GPS_RX);

// OLED Setup
GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;

//create a BMx280I2C object using the I2C interface with I2C Address 0x76
BMx280I2C bmx280(I2C_ADDRESS);

void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);
  ss.begin(9600); // begin GPS serial
	//wait for serial connection to open (only necessary on some boards)
	while (!Serial);
	Wire.begin();

  /* OLED Code */
  oled.init();
  oled.clear();

  /* BMP280 Code */
	//begin() checks the Interface, reads the sensor ID (to differentiate between BMP280 and BME280)
	//and reads compensation parameters.
	if (!bmx280.begin())
	{
		Serial.println("begin() failed. check your BMx280 Interface and I2C Address.");
		while (1);
	}
	//reset sensor to default parameters.
	bmx280.resetToDefaults();
	//by default sensing is disabled and must be enabled by setting a non-zero
	//oversampling setting.
	//set an oversampling setting for pressure and temperature measurements. 
	bmx280.writeOversamplingPressure(BMx280MI::OSRS_P_x16);
	bmx280.writeOversamplingTemperature(BMx280MI::OSRS_T_x16);
}

void loop() {
  // put your main code here, to run repeatedly:
  get_gps();
  bmp280();
  oled.update();
}

void get_gps() {
  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      gps.encode(c);
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      //if () // Did a new valid sentence come in?
      //  Serial.println("");
    }
  }
  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);
  /* GPS Code */
  Serial.write("\nGPS DATA INCOMING\n");
  Serial.print("LAT=");
  Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
  Serial.print(" LON=");
  Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
  Serial.print(" SAT=");
  Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
  Serial.print(" PREC=");
  Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
  oled.clear();
  oled.setCursor(0, 0);
  oled.print("Lat: ");
  oled.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
  oled.setCursor(0, 1);
  oled.print("Lon:");
  oled.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
  oled.setCursor(0, 2);
  oled.print("# SATs:");
  oled.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
  oled.print(" Prcsn=");
  oled.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
}

void bmp280() {
  /* BMP280 Code */
  Serial.println("");
	//start a measurement
	if (!bmx280.measure())
	{
		Serial.println("could not start measurement, is a measurement already running?");
		return;
	}
	//wait for the measurement to finish
	do
	{
		delay(100);
	} while (!bmx280.hasValue());

  Serial.write("\nBMP280 DATA INCOMING\n");
  float tempF = 0;
  float tempC = bmx280.getTemperature();
  float pascals = bmx280.getPressure();
  float stdp = 1013.25;
  float hPaPsiRatio = 0.01450377;
  float hPa = pascals * 0.01;
  float bars = pascals * 0.00001;
  float psi = hPa * hPaPsiRatio;
  float stdpsi = stdp * hPaPsiRatio;
  tempF = (tempC*1.8)+32;
	Serial.print("Pressure: "); Serial.print(psi); Serial.print(" psi, ");
  Serial.print(hPa); Serial.print(" hPa, Standard: ");
  Serial.print(stdpsi); Serial.print("psi/");
  Serial.print(stdp); Serial.println("hPa"); 
	Serial.print("Temperature: "); Serial.println(tempF);
  oled.setCursor(0, 3);
  oled.print(bars); oled.print("bars | ");
  oled.print(tempF); oled.print("F");

}

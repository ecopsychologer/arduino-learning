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
#include "AnalogUVSensor.h"
#include <string.h>
#include <Adafruit_AHTX0.h>

#define I2C_ADDRESS 0x76
#define GPS_RX 4
#define GPS_TX 3

// OLED Screen Setup
enum ScreenState {
  SCREEN0, // Lat, Lon, No. Sats, Precision, Temp, Pressure
  SCREEN1,
  SCREEN_COUNT // Always last, used to know the count of screens
};

ScreenState currentScreen = SCREEN0;
unsigned long lastButtonPress = 0;
const int pagePin = 7;

// Temp/Humidity Sensor
Adafruit_AHTX0 aht;

// UV Sensor
AnalogUVSensor AUV;

// GPS Serial Connection
TinyGPS gps;
SoftwareSerial ss(GPS_TX, GPS_RX);

// OLED Setup
GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;
bool screen = true;

//create a BMx280I2C object using the I2C interface with I2C Address 0x76
BMx280I2C bmx280(I2C_ADDRESS);

void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);
  ss.begin(9600); // begin GPS serial
	//wait for serial connection to open (only necessary on some boards)
	while (!Serial);
	Wire.begin();

  /* UV Sensor */
  AUV.begin(A0, 5.0, 1023);     // connect sensor to A0
  AUV.setPowerPin(5);           //  connect power of sensor to digital pin 5
  AUV.switchOff();              // turn off the sensor for now

  /* AHT10 Temp/Humidity */
  if (! aht.begin()) {
    Serial.println("AHT not found. Check wiring.");
    while (1) delay(10);
  }
  Serial.println("AHT10 connected");

  /* OLED Code */
  oled.init();
  oled.clear();
  pinMode(pagePin, INPUT_PULLUP);

  /* BMP280 Code Temp/Pressure */
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
  // Collect and Store Data from Sensors
  String lat = "LAT:";
  String lon = "LON:";
  String sats = "SATS:";
  String prec = " | PREC:";
  String uv = get_uv();
  String tempressure = bmp280();
  String conditions = aht10();
  get_gps_vals(lat, lon, sats, prec);
  sats.concat(prec);

  if (digitalRead(pagePin) == LOW) {
    Serial.println("Button Press Detected");
  }

  // Handle button press to cycle through screens
  if (digitalRead(pagePin) == LOW && millis() - lastButtonPress > 500) { // Debouncing delay
    currentScreen = (ScreenState)((currentScreen + 1) % SCREEN_COUNT); // Cycle through screens
    lastButtonPress = millis();
  }
  
  oled.clear();

  // Based on the current screen, display relevant data
  switch (currentScreen) {
    case SCREEN0:
      oled.setCursor(0, 0);
      oled.print(conditions);
      oled.setCursor(0,1);
      oled.print(tempressure);
      oled.setCursor(0,2);
      oled.print(uv);
      break;
    case SCREEN1:
      oled.setCursor(0, 0);
      oled.print(lat);
      oled.setCursor(0, 1);
      oled.print(lon);
      oled.setCursor(0, 2);
      oled.print(sats);
      break;
    default:
      break;
  }

  oled.update();
  delay(100);
}

String get_uv() {
  AUV.switchOn();
  float uvi = AUV.read(10);       //  10 readings averaged
  AUV.switchOff();
  String uv_data = "";
  // Serial Print
  Serial.print("UV Index: ");
  Serial.println(uvi, 1);

  // Response Forming
  uv_data.concat("UV Index: ");
  uv_data.concat(String(uvi));
  return uv_data;
}

void get_gps_vals(String lat, String lon, String sats, String prec) {
  // For the timeframe we parse GPS data and report some key values
  int timeframe = 1200;
  for (unsigned long start = millis(); millis() - start < timeframe;)
  {
    while (ss.available())
    {
      char c = ss.read();
      gps.encode(c);
    }
  }
  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);

  /* GPS Code */
  // Serial Print
  Serial.write("\nGPS DATA INCOMING\n");
  Serial.print("LAT=");
  Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
  Serial.print(" LON=");
  Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
  Serial.print(" SAT=");
  Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
  Serial.print(" PREC=");
  Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());

  lat.concat(String(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6));
  //oled.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
  lon.concat(String(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6));
  //oled.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
  sats.concat(String(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites()));
  //oled.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
  prec.concat(String(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop()));
  //oled.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
}

String bmp280() {
  /* BMP280 Code */
  Serial.println("");
	//start a measurement
	if (!bmx280.measure()) {
		Serial.println("could not start bmp280 measurement");
		return;
	}
	//wait for the measurement to finish
	do {
		delay(100);
	} while (!bmx280.hasValue());

  // Temperature/Pressure Conversions
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

  // Serial Print
  Serial.write("\nBMP280 DATA INCOMING\n");
	Serial.print("Pressure: "); Serial.print(psi); Serial.print(" psi, ");
  Serial.print(hPa); Serial.print(" hPa, Standard: ");
  Serial.print(stdpsi); Serial.print("psi/");
  Serial.print(stdp); Serial.println("hPa"); 
	Serial.print("Temperature: "); Serial.println(tempF);

  String tempressure = "";
  tempressure.concat(String(tempF));
  tempressure.concat("F | ");
  tempressure.concat(String(bars));
  tempressure.concat("bars");
  return tempressure;
  //oled.print(tempF); oled.print("F | ");
  //oled.print(bars); oled.print("bars");
}

String aht10() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print("Temperature: "); 
  Serial.print(temp.temperature); 
  Serial.println(" degrees C");
  Serial.print("Humidity: "); 
  Serial.print(humidity.relative_humidity); 
  Serial.println("% rH");

  // Temperature/Pressure Conversions
  //float tempF = 0;
  //float tempC = temp.temperature;
  //float humidity = humidity.relative_humidity();
  //tempF = (tempC*1.8)+32;    

  String conditions = String(temp.temperature);
  conditions.concat("C | ");
  conditions.concat(String(humidity.relative_humidity));
  conditions.concat("% rH");
  return conditions;
}

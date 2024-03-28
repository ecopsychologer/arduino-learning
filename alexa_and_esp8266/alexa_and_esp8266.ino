/***************************************************
  Adafruit MQTT Library ESP8266 Example
  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino
  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include "ESP8266WiFi.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "IFTTTMaker.h"
#include "WiFiClientSecure.h"

// the OnOff button feed turns this RELAY on/off
#define RELAY 2  // EPS8266 GPIO2
#define KEY "mhrdOLuhDWJcxtvCSICcAwJIASduuRxa-W5iGq5FCob"
#define EVENT_NAME "device_on"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "SCU-Student"
#define WLAN_PASS       "gosantaclara"
//char WLAN_SSID[] = WLAN_SSID;
//char WLAN_PASS[] = WLAN_PASS;

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  8883                   // 1883 for http 8883 for https
#define AIO_USERNAME    "jcschoen"
#define AIO_KEY         "733640ed72464ebab46f9ae07200eabb"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
//WiFiClient client;  // Must set AIO_SERVERPORT to 1883
// or... use WiFiFlientSecure for SSL
WiFiClientSecure client;  // Must set AIO_SERVERPORT to 8883
IFTTTMaker ifttt(KEY, client);

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Subscribe OnOffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  pinMode(RELAY, OUTPUT);

  Serial.begin(115200);
  delay(10);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for OnOff feed.
  mqtt.subscribe(&OnOffbutton);

  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

}

uint32_t x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    // Check if its the OnOff button feed
    if (subscription == &OnOffbutton) {
      Serial.print(F("On-Off button: "));
      Serial.println((char *)OnOffbutton.lastread);
      IPAddress ip = WiFi.localIP();
      
      if (strcmp((char *)OnOffbutton.lastread, "0") == 0) {
        digitalWrite(RELAY, LOW);
        if(ifttt.triggerEvent("device_off", WLAN_SSID, ip.toString())){
          Serial.println("Successfully sent");
        } else {
          Serial.println("Failed!");
        }
      }
      if (strcmp((char *)OnOffbutton.lastread, "1") == 0) {
        digitalWrite(RELAY, HIGH);
        if(ifttt.triggerEvent("device_on", WLAN_SSID, ip.toString())){
          Serial.println("Successfully sent");
        } else {
          Serial.println("Failed!");
        }
      }
    }
  }

  // ping the server to keep the mqtt connection alive
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

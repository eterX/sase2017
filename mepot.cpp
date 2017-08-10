#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

//Local intialization. Once its business is done, there is no need to keep it around
WiFiManager wifiManager;
ESP8266WebServer server(80);


void handleRoot() {
  String cuerpo = "Consumo [W];";
 //cuerpo+=WiFi.localIP();
 //cuerpo+=";";
 cuerpo+=analogRead(A0) * (3.3/1024.0);;
 cuerpo+="\n";
 server.send(200, "text/plain", cuerpo);
}



void setup() {
 // initialize digital pin GPIO2/D9 as an output.
 pinMode(BUILTIN_LED, OUTPUT);
 Serial.begin(115200);
 Serial.println("esperando Serial...:");
 delay(10000);
  //WiFiManager
  //reset saved settings
  //wifiManager.resetSettings();
  
  //set custom ip for portal
  //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
  
  //fetches ssid and pass from eeprom and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("AutoConnectAP");
  //or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();
  
  
  //if you get here you have connected to the WiFi
  Serial.print("connected...yeey :)"); 
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("HTTP server started");
  server.on("/", handleRoot);
 }
 // the loop function runs over and over again forever
 void loop() {
 digitalWrite(BUILTIN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
 delay(1000);              // wait for a second
 digitalWrite(BUILTIN_LED, LOW);    // turn the LED off by making the voltage LOW
 int value = analogRead(A0);
 float voltage = (value) * (3.3/1024.0);
 Serial.print("IP;Consumo [W];");
 Serial.print(WiFi.localIP());
 Serial.print(";");
 Serial.println(voltage,2);
 server.handleClient();
 }

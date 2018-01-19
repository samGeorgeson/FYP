#include <ESP8266HTTPClient.h>

//test file for LCD display and Wifi functionality

#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
 
const char* ssid = "DMG";
const char* password = "TUBBYTOFFEE";
int myLocID = 0;
WiFiServer server(80);
StaticJsonBuffer<512> JSONBuffer;


// Construct an LCD object and pass it the 
// I2C address, width (in characters) and
// height (in characters). Depending on the
// Actual device, the IC2 address may change.
LiquidCrystal_I2C lcd(0x3F, 20, 4); // 0x3f is the correct (default) address- see checker

void setup() {

  // The begin call takes the width and height. This
  // Should match the number provided to the constructor.
  lcd.begin(20,4);
  lcd.init();

  // Turn on the backlight.
  lcd.backlight();
  
  Serial.begin(115200); // opens serial at the NodeMCU's baud rate (for testing)
  delay(10);
  
  // Move the cursor characters to the right and
  // zero characters down (line 1).
  lcd.setCursor(5, 0);
  lcd.print("Connecting to ");
  lcd.setCursor(5, 1);
  lcd.println(ssid);
 
  WiFi.begin(ssid, password); // connects to a local network
  int x = 2;
  while (WiFi.status() != WL_CONNECTED) { // wait for the connection to resolve
    delay(500);
    lcd.setCursor(5, x);
    lcd.print("           ");
    if (x == 2){
      x = 3;
    } else {
      x = 2;
    }
    lcd.setCursor(5, x);
    lcd.print("Waiting...");
  }

  lcd.setCursor(5, 2);
  lcd.print("           ");
  lcd.setCursor(5, 3);
  lcd.print("WiFi connected!");
   
  // Start the server
  server.begin();
  int i = 0;
  while (i < 4){
    lcd.setCursor(0, i);
    lcd.print("                    ");
    i++;
  }
  lcd.setCursor(0, 0);
  lcd.print("Server started");
 
  // Print the IP address
  lcd.setCursor(0, 1);
  lcd.print("Connect to:");
  lcd.setCursor(0, 2);
  lcd.print("http://");
  lcd.print(WiFi.localIP());
  lcd.print("/");
  delay(10000);

  /* API Get template
  HTTPClient http;

  http.begin("http://jsonplaceholder.typicode.com/users/1"); // dummy HTTP API for testin'
  int httpCode = http.GET();
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
 
    }
    // make this into getting the location of the IP address for later api interactions
  http.end();
  */
  HTTPClient http;
  char* myLoc = "";
  http.begin("http://ipinfo.io/geo?token=f1973cb5580bf8/json"); // gets data about the current IP
  int httpCode = http.GET();
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      JsonObject& parsed = JSONBuffer.parseObject(payload);
      myLoc = parsed["loc"]; // takes the location as a co-ordinate
    } else {
        lcd.setCursor(0, 3);
        lcd.print("Location find failed");
    }
    // make this into getting the location of the IP address for later api interactions
  http.end();
  String address = "https://www.metaweather.com/api/?query=" + String(myLoc);
  http.begin(address); // query for weather data for this location
  httpCode = http.GET();
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      JsonObject& parsed = JSONBuffer.parseObject(payload);
      myLocID = parsed["woeid"]; // woeid = "where on earth" id, used as an absolute reference to a place
    } else {
        lcd.setCursor(0, 3);
        lcd.print("Location find failed");
    }
  /*
  // Print HELLO to the screen, starting at 5,0.
  lcd.print("HELLO");

  // Move the cursor to the next line and print
  // WORLD.
  lcd.setCursor(5, 1);      
  lcd.print("WORLD");
  */
}

void loop() {
  // Put the stuff to decide which data to display here
  //displayWeather(); // displays the current weather & temp
  delay(120000);
}

void displayWeather() {
 /*
  HTTPClient http;

  http.begin("https://www.metaweather.com/api/" + myLocID); // query for weather data for this location
  int httpCode = http.GET();
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      JsonObject& parsed = JSONBuffer.parseObject(payload);
      myLoc = parsed["loc"]; // get the things here
 
    }
    // make this into getting the location of the IP address for later api interactions
  http.end();
  */
  }


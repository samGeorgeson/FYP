//test file for LCD display and Wifi functionality

#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
 
const char* ssid = "DMG";
const char* password = "TUBBYTOFFEE";
WiFiServer server(80);

// Construct an LCD object and pass it the 
// I2C address, width (in characters) and
// height (in characters). Depending on the
// Actual device, the IC2 address may change.
LiquidCrystal_I2C lcd(0x3F, 20, 4); // 0x3f is the correct (default) address- see checker

void setup() {
  /*
  Serial.begin(115200); // opens serial at the NodeMCU's baud rate
  delay(10);
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password); // connects to a local network

  while (WiFi.status() != WL_CONNECTED) { // wait for the connection to resolve
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
   
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  */
  // The begin call takes the width and height. This
  // Should match the number provided to the constructor.
  lcd.begin(20,4);
  lcd.init();

  // Turn on the backlight.
  lcd.backlight();

  // Move the cursor characters to the right and
  // zero characters down (line 1).
  lcd.setCursor(5, 0);

  // Print HELLO to the screen, starting at 5,0.
  lcd.print("HELLO");

  // Move the cursor to the next line and print
  // WORLD.
  lcd.setCursor(5, 1);      
  lcd.print("WORLD");
}

void loop() {
}

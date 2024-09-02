#include <ESP8266WiFi.h>          // Include the Wi-Fi library
#include <ESP8266WebServer.h>     // Include the WebServer library
#include <ESP8266mDNS.h>          // Include the mDNS library

ESP8266WebServer server(80);      // Create a webserver object that listens for HTTP request on port 80

const int buz_pin = 2;            // GPIO2 where the buzzer is connected
boolean buzzing_state = false;    // State of the buzzer (ON/OFF)
unsigned long lastBuzzTime = 0;   // Timestamp to manage the tone duration
const unsigned long buzzInterval = 200;  // Interval between buzzes in milliseconds

String html_code = "<!DOCTYPE html><html><head><style>"
                   "body {background-color: #6f2036; color: white; text-align: center;}"
                   ".button {border: none; padding: 12px 40px; text-align: center;"
                   "text-decoration: none; display: inline-block; font-size: 16px;"
                   "margin: 4px 2px; cursor: pointer;}"
                   ".button1 {background-color: black; color: white; border: 3px solid #d1fd1f; border-radius: 30px;}"
                   "</style></head><body><h2>Hi! I am your keychain</h2>"
                   "<p>I'm feeling lonely :(</p>"
                   "<form action=\"/BUZ\" method=\"POST\">"
                   "<button class=\"button button1\">Toggle buzz!</button>"
                   "</form>";

void handleRoot(); 
void handleBUZ(); 
void handleNotFound();
void setupAP();  // Setup ESP-01 as an access point

void setup(void) {
  Serial.begin(115200);  // Start the Serial communication
  delay(10);
  Serial.println('\n');
  
  pinMode(buz_pin, OUTPUT);  // Set buzzer pin as output

  setupAP();  // Set up ESP-01 as an access point
}

void loop(void) {
  server.handleClient();  // Handle HTTP requests

  if (buzzing_state) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastBuzzTime >= buzzInterval) {
      lastBuzzTime = currentMillis;
      tone(buz_pin, 1000, 200);  // Generate a 1kHz tone for 200 ms
      delay(200);  // Pause for a moment before the next tone
    }
  }
}

void setupAP() {
  WiFi.softAP("ESP01_AP", "12345678");  // Set the SSID and Password for the Access Point
  IPAddress IP = WiFi.softAPIP();       // Get the IP address of the Access Point
  Serial.print("AP IP address: ");
  Serial.println(IP);

  if (!MDNS.begin("mycarkey")) {  // Set up mDNS
    Serial.println("Error setting up MDNS responder!\n");
  }
  Serial.println("mDNS responder started. IP bye bye ≧◉◡◉≦\n");

  server.on("/", HTTP_GET, handleRoot);  // Handle root URL
  server.on("/BUZ", HTTP_POST, handleBUZ);  // Handle POST request to toggle buzzer
  server.onNotFound(handleNotFound);  // Handle unknown URLs

  server.begin();  // Start the web server
  Serial.println("Yippee!! ٩(˘◡˘)۶ HTTP server started\n");
}

void handleRoot() {
  server.send(200, "text/html", html_code + "Current state: <b>" + buzzing_state + "</b><br><br><i>0 - Not buzzing<br>1 - Buzzing</i></body></html>");
}

void handleBUZ() {
  buzzing_state = !buzzing_state;  // Toggle the buzzing state
  if (!buzzing_state) {
    noTone(buz_pin);  // Stop buzzing if state is off
  }
  server.sendHeader("Location", "/");  // Redirect to the home page
  server.send(303);  // Send HTTP status 303 (See Other)
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found");  // Handle 404 errors
}

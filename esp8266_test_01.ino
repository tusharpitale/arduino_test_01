#include <SoftwareSerial.h>

SoftwareSerial espSerial(2, 3); // RX, TX pins for communication with ESP8266 module

void setup() {
  Serial.begin(9600);        // Initialize serial communication with computer
  espSerial.begin(115200);   // Initialize serial communication with ESP8266 module

  connectToWiFi(); // Connect to Wi-Fi network
}

void loop() {
  if (!isConnected()) {
    connectToWiFi(); // Attempt reconnection if Wi-Fi connection is lost
  }

  // Your main program logic here
  
}

void connectToWiFi() {
  // Reset the ESP8266 module
  espSerial.println("AT+RST");
  delay(2000);  // Wait for the module to reset

  // Set the mode of the ESP8266 to station mode
  espSerial.println("AT+CWMODE=1");
  delay(1000);  // Wait for the mode to be set

  // Connect to the Wi-Fi network (WPA/WPA2-Personal)
  espSerial.print("AT+CWJAP=\"Tushar-HomeWifi\",\"Classic3#\"");
  delay(5000);  // Allow time for the module to connect to the network
}

bool isConnected() {
  espSerial.println("AT+CWJAP?"); // Check current connection status

  while (espSerial.available()) {
    String response = espSerial.readStringUntil('\n');
    if (response.indexOf("OK") != -1) {
      //Serial.write("Connected to My Wifi");
      return true; // Connected to Wi-Fi
    }
  }
  
  Serial.write("NOT Connected to My Wifi");
  return false; // Not connected to Wi-Fi
}


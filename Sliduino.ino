#include <WiFi101.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiSSLClient.h>
#include <WiFiUdp.h>
#include "MainWindow.h"

/*
 * This example is modified from the original file 
 * https://github.com/arduino-libraries/WiFi101/blob/master/examples/SimpleWebServerWiFi/SimpleWebServerWiFi.ino
 */
#include <SPI.h>
#include <WiFi101.h>

#define CLIENT_CHUNK_SIZE (1024)

// Utility declarations
char ParameterBuffer[50] = {0};
bool LookupParameter(char* ParameterName);


enum Commands
{
  
}

char ssid[] = "Avishay";      //  your network SSID (name)
char pass[] = "12345678";   // your network password
const int Led1 = 6;
const int Led2 = 7;

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void SendToClient(WiFiClient Client, String str)
{
  for(int i = 0; i < str.length(); i += CLIENT_CHUNK_SIZE)
  {
    String part = str.substring(i, i + CLIENT_CHUNK_SIZE - 1);
    Client.print(part);
    Serial.print(part);
  }
}

void setup() 
{
  Serial.begin(9600);      // initialize serial communication

  // Initizalize LED pins
  pinMode(Led1, OUTPUT);     
  pinMode(Led2, OUTPUT); 

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) 
  {
    digitalWrite(Led1, LOW);
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);
    digitalWrite(Led1, HIGH);
    
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    
    // Wait 1 second for connection:
    delay(1000);
  }

  // Turn off LED1
  digitalWrite(Led1, LOW);
  
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status  
}
void loop() 
{
  WiFiClient Client = server.available();   // listen for incoming clients
 
  if (Client) 
  {           
    Serial.println("Client Connected");                 // Print a message out the serial port
    String CurrentLine = "";                            // Make a String to hold incoming data from the client
    
    while (Client.connected())                          // Loop while the client's connected
    {            
      if (Client.available())                           // If there are bytes to read from the client,
      {             
        char c = Client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') // if the byte is a newline character
        {                    
          Serial.println("Got line: " + CurrentLine);
          // If the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (CurrentLine.length() == 0) 
          {
            
            Serial.println("Sending HTML");
            //String html = Html_Config();         
            //SendToClient(Client, html);
            
            break;
          }
          else 
          {      // if you got a newline, then clear currentLine:
            CurrentLine = "";
          }
        }
        else if (c != '\r')
        {    // if you got anything else but a carriage return character,
          CurrentLine += c;      // add it to the end of the currentLine
        }

        // Check the request parameters
        if (CurrentLine.endsWith("GET /?ToMotor")) {
          digitalWrite(Led1, HIGH);               // GET /H turns the LED on
        }
        if (CurrentLine.endsWith("GET /?ToNotMotor")) {
          digitalWrite(Led1, LOW);                // GET /L turns the LED off
        }
        if (CurrentLine.endsWith("GET /?Start")) {
          digitalWrite(Led2, HIGH);               // GET /H turns the LED on
        }
        if (CurrentLine.endsWith("GET /?Stop")) {
          digitalWrite(Led2, LOW);                // GET /L turns the LED off
        }
      }
    }
    
    // Close the connection:
    Client.stop();
    Serial.println("client disonnected");
  }
}

bool LookupParameter(char* ParameterName)
{
 //  if (currentLine.endsWith("GET /?ToMotor"))
}

void printWifiStatus() 
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}





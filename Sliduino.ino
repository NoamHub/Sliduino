#include <WiFi101.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiSSLClient.h>
#include <WiFiUdp.h>
#include "MainWindow.h"
#include <SPI.h>
#include <WiFi101.h>

#include "TimerInterface.h"
#include "MotorControl.h"

#define CLIENT_CHUNK_SIZE (1024)

// Utility declarations
char ParameterBuffer[50] = {0};
bool LookupParameter(char* ParameterName);

int FindSubstring(String haystack, String needle) 
{  
  for (int i = 0; i <= (int)(haystack.length() - needle.length()); i++) {    
    if (haystack.substring(i,needle.length()+i) == needle) {
      return i;
    }
  }
  return -1;
}

char ssid[] = "Avishay";      //  your network SSID (name)
char pass[] = "12345678";   // your network password
const int Led1 = 6;
const int Led2 = 7;

int status = WL_IDLE_STATUS;
WiFiServer server(80);

int Itamar = 1;

void MiliSecCallback()
{
  MotorControl.RegisterTimerInterrupt();
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
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);
    
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    
    // Wait 1 second for connection:
    delay(1000);
  }

  // Turn off LED1
  digitalWrite(Led1, LOW);
  
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status  

  MotorControl.Init(FULL_STEP, 7, 8, 8, 8, 8, 10, 12);

  Timer.Init();
  Timer.SetInterval(1);
  Timer.Start();
  Timer.SetCallback(MiliSecCallback);
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
       // Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') // if the byte is a newline character
        {
          bool SendHTML;
          
          // If the parameters line was received
          if (FindSubstring(CurrentLine, "GET") == 0)
          {
            
            Serial.println("Command");
            // Parse command
            SendHTML = ParseCommand(CurrentLine);
          }
              
          //Serial.println("Got line: " + CurrentLine);
          // If the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (CurrentLine.length() == 0) 
          {
            if (SendHTML)
            {
              Serial.println("Sending HTML");
              String html = Html_Config();         
              for(int i = 0; i < html.length(); i += CLIENT_CHUNK_SIZE)
              {
                String part = html.substring(i, i + CLIENT_CHUNK_SIZE - 1);
                Client.print(part);
               // Serial.print(part);
              }
            }
            else
            {
              Client.print(String(Itamar));
            }
            
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
      }
    } 
    
    // Close the connection:
    Client.stop();
    Serial.println("client disonnected");
  }
}

bool ParseCommand(String GetLine)
{
  Serial.println(GetLine);
  /*
  if (FindSubstring(GetLine, "?pollSteps") != -1)
  {
    return false;
  }
  
  if (FindSubstring(GetLine, "?ToMotor") != -1)
  {
    digitalWrite(Led1, HIGH);       
  }
  else if (FindSubstring(GetLine, "?ToNotMotor") != -1)
  {
   digitalWrite(Led1, LOW);     
  }
  else */
  Serial.println("?? + ");
  Serial.println(FindSubstring(GetLine, "/Start"));
  
  if(FindSubstring(GetLine, "/Start") > 0)
  {
    Serial.println("Start");
  MotorControl.Set(TO_MOTOR, 300, 0);
  MotorControl.Start();
  }
  else if (FindSubstring(GetLine, "/Stop") > 0 )
  {
    Serial.println("Stop");
  MotorControl.Stop();          
  }
   else if (FindSubstring(GetLine, "/Reset") > 0 )
  {
    Serial.println("Reset");
    MotorControl.Set(TO_NO_MOTOR, 1000, 0);
  MotorControl.Start();              
  }
  return true;
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









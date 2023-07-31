#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ESP8266FtpServer.h>
#include <Wire.h>
#include <GyverBME280.h>

#define WIFI_SSID "KU2D"
#define WIFI_PASS "D8DNydbWW22"

ESP8266WebServer HTTP(80);
FtpServer ftpSrv;
GyverBME280 bme;

bool handleFileRead(String path);
String getContentType(String filename);
void sendSensorData();

void setup() 
{
    Serial.begin(9600);                                                 
        
    SPIFFS.begin();                                                                    
    HTTP.begin();                                                        
    ftpSrv.begin("admin","admin");
    Wire.begin();
    bme.begin();                                   

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");
    Serial.println(WiFi.localIP());

    HTTP.on("/sensor-data", HTTP_GET, sendSensorData);

    // Handling the HTTP request
    HTTP.onNotFound([]()
    {                                                
    if(!handleFileRead(HTTP.uri()))                                  
        HTTP.send(404, "text/plain", "Not Found");                        
    });
}

void loop() 
{
    HTTP.handleClient();                                               
    ftpSrv.handleFTP();                                               
}

// Function to handle file reads from the SPIFFS file system and serve files over HTTP
bool handleFileRead(String path)
{          
    // If the path ends with "/", append "index.html" to it                             
    if(path.endsWith("/")) path += "index.html";     

    // Get the content type based on the file extension                    
    String contentType = getContentType(path);  

    // Check if the file exists in the SPIFFS                        
    if(SPIFFS.exists(path))
    { 
        // If the file exists, open it in read mode                                           
        File file = SPIFFS.open(path, "r");    

        // Send the file contents to the client using the appropriate content type                           
        size_t sent = HTTP.streamFile(file, contentType);       

        // Close the file           
        file.close();                                                     
        return true;                                                        
    }
    return false;                                                         
}

// Function to get the content type based on the file extension
String getContentType(String filename)
{                                 
    if (filename.endsWith(".html")) return "text/html";                   
    else if (filename.endsWith(".css")) return "text/css"; 
    else if (filename.endsWith(".js")) return "application/javascript";
    else if (filename.endsWith(".png")) return "image/png";
    else if (filename.endsWith(".svg")) return "image/svg+xml";           
    else if (filename.endsWith(".jpg")) return "image/jpeg";        
    else if (filename.endsWith(".gif")) return "image/gif";              
    else if (filename.endsWith(".ico")) return "image/x-icon";         
    return "text/plain";                                                 
}

// Function to send sensor data in JSON format as the HTTP response
void sendSensorData() 
{
    /*----------------------------BME280----------------------------*/
    float pressure = bme.readPressure(); // Read pressure in [Pa]
    int temperature = bme.readTemperature();
    double humidity = bme.readHumidity();
    double pressureMmHg = pressureToMmHg(pressure);
    double height = pressureToAltitude(pressure);

    // Prepare data in JSON format
    String sensorData = "{";
    sensorData += "\"temperature\": " + String(temperature) + ",";
    sensorData += "\"humidity\": " + String(humidity) + ",";
    sensorData += "\"pressure\": " + String(pressureMmHg) + ",";    // Output pressure in [mmHg. pillar]
    sensorData += "\"height\": " + String(height);      // Print height in [m a.s.l. seas]
    sensorData += "}";

    // Send the JSON data as the response to the client
    HTTP.send(200, "application/json", sensorData);
    /*--------------------------------------------------------------*/
}
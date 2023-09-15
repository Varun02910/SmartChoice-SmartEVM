#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "SPIFFS.h"
#include <Wire.h>

#define pin1 34
#define pin2 12
#define pin3 14
#define pin4 27
#define pin5 26
#define pin6 25
#define pin7 33
#define pin8 32
#define result 35
int buzzer = 15;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char* parameter_candidatep1 = "input_candidatep1";
const char* parameter_candidatep2 = "input_candidatep2";
const char* parameter_candidatep3 = "input_candidatep3";
const char* parameter_candidatep4 = "input_candidatep4";

const char* parameter_candidatevp1 = "input_candidatevp1";
const char* parameter_candidatevp2 = "input_candidatevp2";
const char* parameter_candidatevp3 = "input_candidatevp3";
const char* parameter_candidatevp4 = "input_candidatevp4";

const char* parameter_candidategs1 = "input_candidategs1";
const char* parameter_candidategs2 = "input_candidategs2";
const char* parameter_candidategs3 = "input_candidategs3";
const char* parameter_candidategs4 = "input_candidategs4";

const char* parameter_candidatejs1 = "input_candidatejs1";
const char* parameter_candidatejs2 = "input_candidatejs2";
const char* parameter_candidatejs3 = "input_candidatejs3";
const char* parameter_candidatejs4 = "input_candidatejs4";
const char* parameter_password = "input_password";
String password;

// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
const char* PARAM_INPUT_3 = "ip";
const char* PARAM_INPUT_4 = "gateway";


//Variables to save values from HTML form
String ssid;
String pass;
String ip;
String gateway;

// File paths to save input values permanently
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
const char* ipPath = "/ip.txt";
const char* gatewayPath = "/gateway.txt";

IPAddress localIP;
//IPAddress localIP(192, 168, 1, 200); // hardcoded

// Set your Gateway IP address
IPAddress localGateway;
//IPAddress localGateway(192, 168, 1, 1); //hardcoded
IPAddress subnet(255, 255, 0, 0);

// Timer variables
unsigned long previousMillis = 0;
const long interval = 10000;  // interval to wait for Wi-Fi connection (milliseconds)

// Set LED GPIO
const int ledPin = 2;

int person1 = 0; int person2 = 0; int person3 = 0; int person4 = 0;
int person5 = 0; int person6 = 0; int person7 = 0; int person8 = 0;
int person9 = 0; int person10 = 0; int person11 = 0; int person12 = 0;
int person13 = 0; int person14 = 0; int person15 = 0; int person16 = 0;
int x = 0;


void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

// Initialize SPIFFS
void initSPIFFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");
}

// Read File from SPIFFS
String readFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    Serial.println("- failed to open file for reading");
    return String();
  }

  String fileContent;
  while (file.available()) {
    fileContent = file.readStringUntil('\n');
    break;
  }
  return fileContent;
}

// Write file to SPIFFS
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("- failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
}

// Initialize WiFi
bool initWiFi() {
  if (ssid == "" || ip == "") {
    Serial.println("Undefined SSID or IP address.");
    return false;
  }

  WiFi.mode(WIFI_STA);
  localIP.fromString(ip.c_str());
  localGateway.fromString(gateway.c_str());


  if (!WiFi.config(localIP, localGateway, subnet)) {
    Serial.println("STA Failed to configure");
    return false;
  }
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("Connecting to WiFi...");

  unsigned long currentMillis = millis();
  previousMillis = currentMillis;

  while (WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Failed to connect.");
      return false;
    }
  }
  Serial.println(WiFi.localIP());
  return true;

}

// entrying the value of candidates
String processor(const String& var) {
  if (var == "input_candidatep1") {
    return readFile(SPIFFS, "/input_candidatep1.txt");
  }
  else if (var == "input_candidatep2") {
    return readFile(SPIFFS, "/input_candidatep2.txt");
  }
  else if (var == "input_candidatep3") {
    return readFile(SPIFFS, "/input_candidatep3.txt");
  }
  else if (var == "input_candidatep4") {
    return readFile(SPIFFS, "/input_candidatep4.txt");
  }

  else if (var == "input_candidatevp1") {
    return readFile(SPIFFS, "/input_candidatevp1.txt");
  }
  else if (var == "input_candidatevp2") {
    return readFile(SPIFFS, "/input_candidatevp2.txt");
  }
  else if (var == "input_candidatevp3") {
    return readFile(SPIFFS, "/input_candidatevp3.txt");
  }
  else if (var == "input_candidatevp4") {
    return readFile(SPIFFS, "/input_candidatevp4.txt");
  }

  else if (var == "input_candidategs1") {
    return readFile(SPIFFS, "/input_candidategs1.txt");
  }
  else if (var == "input_candidategs2") {
    return readFile(SPIFFS, "/input_candidategs2.txt");
  }
  else if (var == "input_candidategs3") {
    return readFile(SPIFFS, "/input_candidategs3.txt");
  }
  else if (var == "input_candidategs4") {
    return readFile(SPIFFS, "/input_candidategs4.txt");
  }

  else if (var == "input_candidatejs1") {
    return readFile(SPIFFS, "/input_candidatejs1.txt");
  }
  else if (var == "input_candidatejs2") {
    return readFile(SPIFFS, "/input_candidatejs2.txt");
  }
  else if (var == "input_candidatejs3") {
    return readFile(SPIFFS, "/input_candidatejs3.txt");
  }
  else if (var == "input_candidatejs4") {
    return readFile(SPIFFS, "/input_candidatejs4.txt");
  }
  return String();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  Wire.begin();
  initSPIFFS();

  // Set GPIO 2 as an OUTPUT
  pinMode(ledPin, OUTPUT);
  pinMode(4, INPUT);//used to send the password for result
  digitalWrite(ledPin, LOW);
  //pins for taking votes input-
  pinMode(buzzer, OUTPUT);
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(pin4, INPUT);
  pinMode(pin5, INPUT);
  pinMode(pin6, INPUT);
  pinMode(pin7, INPUT);
  pinMode(pin8, INPUT);
  pinMode(result, INPUT);

  // Load values saved in SPIFFS
  ssid = readFile(SPIFFS, ssidPath);
  pass = readFile(SPIFFS, passPath);
  ip = readFile(SPIFFS, ipPath);
  gateway = readFile (SPIFFS, gatewayPath);
  Serial.println(ssid);
  Serial.println(pass);
  Serial.println(ip);
  Serial.println(gateway);

  if (initWiFi()) {
    // Route for root / web page

    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(SPIFFS, "/candidate_entry.html", "text/html", false, processor);
    });
    server.serveStatic("/", SPIFFS, "/");

    server.on("/get", HTTP_GET, [](AsyncWebServerRequest * request) {
      String inputMessage;

      if (request->hasParam(parameter_candidatep1)) {
        inputMessage = request->getParam(parameter_candidatep1)->value();
        writeFile(SPIFFS, "/input_candidatep1.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatep2)) {
        inputMessage = request->getParam(parameter_candidatep2)->value();
        writeFile(SPIFFS, "/input_candidatep2.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatep3)) {
        inputMessage = request->getParam(parameter_candidatep3)->value();
        writeFile(SPIFFS, "/input_candidatep3.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatep4)) {
        inputMessage = request->getParam(parameter_candidatep4)->value();
        writeFile(SPIFFS, "/input_candidatep4.txt", inputMessage.c_str());
      }

      else if (request->hasParam(parameter_candidatevp1)) {
        inputMessage = request->getParam(parameter_candidatevp1)->value();
        writeFile(SPIFFS, "/input_candidatevp1.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatevp2)) {
        inputMessage = request->getParam(parameter_candidatevp2)->value();
        writeFile(SPIFFS, "/input_candidatevp2.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatevp3)) {
        inputMessage = request->getParam(parameter_candidatevp3)->value();
        writeFile(SPIFFS, "/input_candidatevp3.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatevp4)) {
        inputMessage = request->getParam(parameter_candidatevp4)->value();
        writeFile(SPIFFS, "/input_candidatevp4.txt", inputMessage.c_str());
      }

      else if (request->hasParam(parameter_candidategs1)) {
        inputMessage = request->getParam(parameter_candidategs1)->value();
        writeFile(SPIFFS, "/input_candidategs1.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidategs2)) {
        inputMessage = request->getParam(parameter_candidategs2)->value();
        writeFile(SPIFFS, "/input_candidategs2.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidategs3)) {
        inputMessage = request->getParam(parameter_candidategs3)->value();
        writeFile(SPIFFS, "/input_candidategs3.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidategs4)) {
        inputMessage = request->getParam(parameter_candidategs4)->value();
        writeFile(SPIFFS, "/input_candidategs4.txt", inputMessage.c_str());
      }

      else if (request->hasParam(parameter_candidatejs1)) {
        inputMessage = request->getParam(parameter_candidatejs1)->value();
        writeFile(SPIFFS, "/input_candidatejs1.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatejs2)) {
        inputMessage = request->getParam(parameter_candidatejs2)->value();
        writeFile(SPIFFS, "/input_candidatejs2.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatejs3)) {
        inputMessage = request->getParam(parameter_candidatejs3)->value();
        writeFile(SPIFFS, "/input_candidatejs3.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatejs4)) {
        inputMessage = request->getParam(parameter_candidatejs4)->value();
        writeFile(SPIFFS, "/input_candidatejs4.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_password)) {
        inputMessage = request->getParam(parameter_password)->value();
        password = inputMessage;
      }
      else {
        inputMessage = "No message sent";
      }
      Serial.println(inputMessage);
      request->send(SPIFFS, "/candidate_entry.html", "text/html", false, processor);
    });

    server.onNotFound(notFound);
    server.begin();

  }
  else {
    // Connect to Wi-Fi network with SSID and password
    Serial.println("Setting AP (Access Point)");
    // NULL sets an open Access Point
    WiFi.softAP("EVM_candidate_name", "var******");

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    // Web Server Root URL
//    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
//      request->send(SPIFFS, "/wifimanager.html", "text/html");
//    });
//
//    server.serveStatic("/", SPIFFS, "/");
//
//    server.on("/", HTTP_POST, [](AsyncWebServerRequest * request) {
//      int params = request->params();
//      for (int i = 0; i < params; i++) {
//        AsyncWebParameter* p = request->getParam(i);
//        if (p->isPost()) {
//          // HTTP POST ssid value
//          if (p->name() == PARAM_INPUT_1) {
//            ssid = p->value().c_str();
//            Serial.print("SSID set to: ");
//            Serial.println(ssid);
//            // Write file to save value
//            writeFile(SPIFFS, ssidPath, ssid.c_str());
//          }
//          // HTTP POST pass value
//          if (p->name() == PARAM_INPUT_2) {
//            pass = p->value().c_str();
//            Serial.print("Password set to: ");
//            Serial.println(pass);
//            // Write file to save value
//            writeFile(SPIFFS, passPath, pass.c_str());
//          }
//          // HTTP POST ip value
//          if (p->name() == PARAM_INPUT_3) {
//            ip = p->value().c_str();
//            Serial.print("IP Address set to: ");
//            Serial.println(ip);
//            // Write file to save value
//            writeFile(SPIFFS, ipPath, ip.c_str());
//          }
//          // HTTP POST gateway value
//          if (p->name() == PARAM_INPUT_4) {
//            gateway = p->value().c_str();
//            Serial.print("Gateway set to: ");
//            Serial.println(gateway);
//            // Write file to save value
//            writeFile(SPIFFS, gatewayPath, gateway.c_str());
//          }
//          Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
//        }
//      }
//      request->send(200, "text/plain", "Done. ESP will restart, connect to your router and go to IP address: " + ip);
//      delay(3000);
//      ESP.restart();
//    });
//    server.begin();
      server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(SPIFFS, "/candidate_entry.html", "text/html", false, processor);
    });
    server.serveStatic("/", SPIFFS, "/");

    server.on("/get", HTTP_GET, [](AsyncWebServerRequest * request) {
      String inputMessage;

      if (request->hasParam(parameter_candidatep1)) {
        inputMessage = request->getParam(parameter_candidatep1)->value();
        writeFile(SPIFFS, "/input_candidatep1.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatep2)) {
        inputMessage = request->getParam(parameter_candidatep2)->value();
        writeFile(SPIFFS, "/input_candidatep2.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatep3)) {
        inputMessage = request->getParam(parameter_candidatep3)->value();
        writeFile(SPIFFS, "/input_candidatep3.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatep4)) {
        inputMessage = request->getParam(parameter_candidatep4)->value();
        writeFile(SPIFFS, "/input_candidatep4.txt", inputMessage.c_str());
      }

      else if (request->hasParam(parameter_candidatevp1)) {
        inputMessage = request->getParam(parameter_candidatevp1)->value();
        writeFile(SPIFFS, "/input_candidatevp1.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatevp2)) {
        inputMessage = request->getParam(parameter_candidatevp2)->value();
        writeFile(SPIFFS, "/input_candidatevp2.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatevp3)) {
        inputMessage = request->getParam(parameter_candidatevp3)->value();
        writeFile(SPIFFS, "/input_candidatevp3.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatevp4)) {
        inputMessage = request->getParam(parameter_candidatevp4)->value();
        writeFile(SPIFFS, "/input_candidatevp4.txt", inputMessage.c_str());
      }

      else if (request->hasParam(parameter_candidategs1)) {
        inputMessage = request->getParam(parameter_candidategs1)->value();
        writeFile(SPIFFS, "/input_candidategs1.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidategs2)) {
        inputMessage = request->getParam(parameter_candidategs2)->value();
        writeFile(SPIFFS, "/input_candidategs2.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidategs3)) {
        inputMessage = request->getParam(parameter_candidategs3)->value();
        writeFile(SPIFFS, "/input_candidategs3.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidategs4)) {
        inputMessage = request->getParam(parameter_candidategs4)->value();
        writeFile(SPIFFS, "/input_candidategs4.txt", inputMessage.c_str());
      }

      else if (request->hasParam(parameter_candidatejs1)) {
        inputMessage = request->getParam(parameter_candidatejs1)->value();
        writeFile(SPIFFS, "/input_candidatejs1.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatejs2)) {
        inputMessage = request->getParam(parameter_candidatejs2)->value();
        writeFile(SPIFFS, "/input_candidatejs2.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatejs3)) {
        inputMessage = request->getParam(parameter_candidatejs3)->value();
        writeFile(SPIFFS, "/input_candidatejs3.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_candidatejs4)) {
        inputMessage = request->getParam(parameter_candidatejs4)->value();
        writeFile(SPIFFS, "/input_candidatejs4.txt", inputMessage.c_str());
      }
      else if (request->hasParam(parameter_password)) {
        inputMessage = request->getParam(parameter_password)->value();
        password = inputMessage;
      }
      else {
        inputMessage = "No message sent";
      }
      Serial.println(inputMessage);
      request->send(SPIFFS, "/candidate_entry.html", "text/html", false, processor);
    });

    server.onNotFound(notFound);
    server.begin();
  }
}

void transmission1()
{
  Wire.beginTransmission(9);
  x = 1;
  Wire.write(x); //send x
  Wire.endTransmission();
}

void transmission2()
{
  Wire.beginTransmission(9);
  x = 2;
  Wire.write(x); //send x
  Wire.endTransmission();
}


void loop() {
  digitalWrite(ledPin, HIGH);
  delay(500);

  String candidatep1 = readFile(SPIFFS, "/input_candidatep1.txt");
  Serial.print("candidatep1: ");
  Serial.println(candidatep1);

  String candidatep2 = readFile(SPIFFS, "/input_candidatep2.txt");
  Serial.print("candidatep2: ");
  Serial.println(candidatep2);

  String candidatep3 = readFile(SPIFFS, "/input_candidatep3.txt");
  Serial.print("candidatep3: ");
  Serial.println(candidatep3);

  String candidatep4 = readFile(SPIFFS, "/input_candidatep4.txt");
  Serial.print("candidatep4: ");
  Serial.println(candidatep4);

  digitalWrite(ledPin, LOW);
  delay(500);

  String candidatevp1 = readFile(SPIFFS, "/input_candidatevp1.txt");
  Serial.print("candidatevp1: ");
  Serial.println(candidatevp1);

  String candidatevp2 = readFile(SPIFFS, "/input_candidatevp2.txt");
  Serial.print("candidatevp2: ");
  Serial.println(candidatevp2);

  String candidatevp3 = readFile(SPIFFS, "/input_candidatevp3.txt");
  Serial.print("candidatevp3: ");
  Serial.println(candidatevp3);

  String candidatevp4 = readFile(SPIFFS, "/input_candidatevp4.txt");
  Serial.print("candidatevp4: ");
  Serial.println(candidatevp4);

  digitalWrite(ledPin, HIGH);
  delay(500);

  String candidategs1 = readFile(SPIFFS, "/input_candidategs1.txt");
  Serial.print("candidategs1: ");
  Serial.println(candidategs1);

  String candidategs2 = readFile(SPIFFS, "/input_candidategs2.txt");
  Serial.print("candidategs2: ");
  Serial.println(candidategs2);

  String candidategs3 = readFile(SPIFFS, "/input_candidategs3.txt");
  Serial.print("candidategs3: ");
  Serial.println(candidategs3);

  String candidategs4 = readFile(SPIFFS, "/input_candidategs4.txt");
  Serial.print("candidategs4: ");
  Serial.println(candidategs4);

  digitalWrite(ledPin, LOW);
  delay(500);

  String candidatejs1 = readFile(SPIFFS, "/input_candidatejs1.txt");
  Serial.print("candidatejs1: ");
  Serial.println(candidatejs1);

  String candidatejs2 = readFile(SPIFFS, "/input_candidatejs2.txt");
  Serial.print("candidatejs2: ");
  Serial.println(candidatejs2);

  String candidatejs3 = readFile(SPIFFS, "/input_candidatejs3.txt");
  Serial.print("candidatejs3: ");
  Serial.println(candidatejs3);

  String candidatejs4 = readFile(SPIFFS, "/input_candidatejs4.txt");
  Serial.print("candidatejs4: ");
  Serial.println(candidatejs4);

  digitalWrite(ledPin, HIGH);
  delay(500);


  const char* candip1 = candidatep1.c_str();
  const char* candip2 = candidatep2.c_str();
  const char* candip3 = candidatep3.c_str();
  const char* candip4 = candidatep4.c_str();
  const char* candivp1 = candidatevp1.c_str();
  const char* candivp2 = candidatevp2.c_str();
  const char* candivp3 = candidatevp3.c_str();
  const char* candivp4 = candidatevp4.c_str();
  const char* candigs1 = candidategs1.c_str();
  const char* candigs2 = candidategs2.c_str();
  const char* candigs3 = candidategs3.c_str();
  const char* candigs4 = candidategs4.c_str();
  const char* candijs1 = candidatejs1.c_str();
  const char* candijs2 = candidatejs2.c_str();
  const char* candijs3 = candidatejs3.c_str();
  const char* candijs4 = candidatejs4.c_str();
  const char* pass = password.c_str();

  int x = 5;
  send_char(candip1, x);

  x = 6;
  send_char(candip2, x);

  x = 7;
  send_char(candip3, x);

  x = 8;
  send_char(candip4, x);

  x = 9;
  send_char(candivp1, x);

  x = 10;
  send_char(candivp2, x);

  x = 11;
  send_char(candivp3, x);

  x = 12;
  send_char(candivp4, x);

  x = 13;
  send_char(candigs1, x);

  x = 14;
  send_char(candigs2, x);

  x = 15;
  send_char(candigs3, x);

  x = 16;
  send_char(candigs4, x);

  x = 17;
  send_char(candijs1, x);

  x = 18;
  send_char(candijs2, x);

  x = 19;
  send_char(candijs3, x);

  x = 20;
  send_char(candijs4, x);

  if ((digitalRead(pin1) == HIGH) && (digitalRead(pin2) == HIGH)) {
    x = 40;
    analogWrite(buzzer, 200);
    delay(1000);
    analogWrite(buzzer, 100);
    delay(1000);
    analogWrite(buzzer, 0);
    delay(100);
  }
  while (x == 40) {
    if (digitalRead(pin1) == HIGH)
    {
      person1 += 1;
      transmission1();
      analogWrite(buzzer, 255);
      delay(2000);
      analogWrite(buzzer, 0);
      x = 50;
    }

    else if (digitalRead(pin2) == HIGH)
    {
      person2 += 1;
      transmission1();
      analogWrite(buzzer, 255);
      delay(2000);
      analogWrite(buzzer, 0);
      x = 50;
    }

    else if (digitalRead(pin3) == HIGH)
    {
      person3 += 1;
      transmission1();
      analogWrite(buzzer, 255);
      delay(2000);
      analogWrite(buzzer, 0);
      x = 50;
    }

    else if (digitalRead(pin4) == HIGH)
    {
      person4 += 1;
      transmission1();
      analogWrite(buzzer, 255);
      delay(2000);
      analogWrite(buzzer, 0);
      x = 50;
    }
    delay(10);
    
    while (x == 50) {
      if (digitalRead(pin5) == HIGH)
      {
        person5 += 1;
        transmission2();
        analogWrite(buzzer, 255);
        delay(2000);
        analogWrite(buzzer, 0);
        x = 60;
      }

      else if (digitalRead(pin6) == HIGH)
      {
        person6 += 1;
        transmission2();
        analogWrite(buzzer, 255);
        delay(2000);
        analogWrite(buzzer, 0);
        x = 60;
      }

      else if (digitalRead(pin7) == HIGH)
      {
        person7 += 1;
        transmission2();
        analogWrite(buzzer, 255);
        delay(2000);
        analogWrite(buzzer, 0);
        x = 60;
      }

      else if (digitalRead(pin8) == HIGH)
      {
        person8 += 1;
        transmission2();
        analogWrite(buzzer, 255);
        delay(2000);
        analogWrite(buzzer, 0);
        x = 60;
      }
    }
    while (x == 60) {
      if (digitalRead(pin1) == HIGH)
      {
        person9 += 1;
        transmission1();
        analogWrite(buzzer, 255);
        delay(2000);
        analogWrite(buzzer, 0);
        x = 70;
      }

      else if (digitalRead(pin2) == HIGH)
      {
        person10 += 1;
        transmission1();
        analogWrite(buzzer, 255);
        delay(2000);
        analogWrite(buzzer, 0);
        x = 70;
      }

      else if (digitalRead(pin3) == HIGH)
      {
        person11 += 1;
        transmission1();
        analogWrite(buzzer, 255);
        delay(2000);
        analogWrite(buzzer, 0);
        x = 70;
      }

      else if (digitalRead(pin4) == HIGH)
      {
        person12 += 1;
        transmission1();
        analogWrite(buzzer, 255);
        delay(2000);
        analogWrite(buzzer, 0);
        x = 70;
      }
    }
    while (x == 70) {
      if (digitalRead(pin5) == HIGH)
      {
        person13 += 1;
        transmission2();
        analogWrite(buzzer, 255);
        delay(2000);
        analogWrite(buzzer, 0);
        x = 40;
      }

      else if (digitalRead(pin6) == HIGH)
      {
        person14 += 1;
        transmission2();
        analogWrite(buzzer, 255);
        delay(2000);
        analogWrite(buzzer, 0);
        x = 40;
      }

      else if (digitalRead(pin7) == HIGH)
      {
        person15 += 1;
        transmission2();
        analogWrite(buzzer, 255);
        delay(2000);
        analogWrite(buzzer, 0);
        x = 40;
      }

      else if (digitalRead(pin8) == HIGH)
      {
        person16 += 1;
        transmission2();
        analogWrite(buzzer, 255);
        delay(2000);
        analogWrite(buzzer, 0);
        x = 40;
      }
    }
    if (digitalRead(result) == HIGH)
    {
      analogWrite(buzzer, 255);
      Serial.print("no.of votes of 1st person :");
      Serial.println(person1);
      Serial.print("no.of votes of 2nd person :");
      Serial.println(person2);
      Serial.print("no.of votes of 3rd person :");
      Serial.println(person3);
      Serial.print("no.of votes of 4th person :");
      Serial.println(person4);
      Serial.print("no.of votes of 5th person :");
      Serial.println(person5);
      Serial.print("no.of votes of 6th person :");
      Serial.println(person6);
      Serial.print("no.of votes of 7th person :");
      Serial.println(person7);
      Serial.print("no.of votes of 8th person :");
      Serial.println(person8);
      Serial.print("no.of votes of 9th person :");
      Serial.println(person9);
      Serial.print("no.of votes of 10th person :");
      Serial.println(person10);
      Serial.print("no.of votes of 11th person :");
      Serial.println(person11);
      Serial.print("no.of votes of 12th person :");
      Serial.println(person12);
      Serial.print("no.of votes of 13th person :");
      Serial.println(person13);
      Serial.print("no.of votes of 14th person :");
      Serial.println(person14);
      Serial.print("no.of votes of 15th person :");
      Serial.println(person15);
      Serial.print("no.of votes of 16th person :");
      Serial.println(person16);

      x = 3;
      Wire.beginTransmission(9);
      Wire.write(x);
      Wire.write(person1);
      Wire.write(person2);
      Wire.write(person3);
      Wire.write(person4);
      Wire.write(person5);
      Wire.write(person6);
      Wire.write(person7);
      Wire.write(person8);
      Wire.write(person9);
      Wire.write(person10);
      Wire.write(person11);
      Wire.write(person12);
      Wire.write(person13);
      Wire.write(person14);
      Wire.write(person15);
      Wire.write(person16);

      Wire.endTransmission();

      delay(2000);
      analogWrite(buzzer, 0);
      x=0;
    }
  }

  if (digitalRead(4) == HIGH) {
    x = 21;
    send_char(pass, x);
    password = "0";
    delay(2000);
  }
  digitalWrite(ledPin, LOW);
  delay(500);
}


void send_char(const char* words, int x) {
  Wire.beginTransmission(9);
  Wire.write(x);
  Wire.write(words);
  Wire.endTransmission();
}

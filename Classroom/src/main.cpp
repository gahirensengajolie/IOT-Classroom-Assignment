#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char *SSID = "ANITAB LAB";
const char *Pass = "Akirachix@2011";

WebServer myserver(80);
const int LED_PIN = 2;
bool ledState = LOW;

String page()
{
  return "<!DOCTYPE html>"
         "<html>"
         "<body>"
         "<form action=\"/toggle\">"
         "<button type=\"submit\" style=\"font-size:30px;\">TURN LED ON</button>"
         "</form>"
         "</body></html>";
}

void handleRoot()
{
  myserver.send(200, "text/html", page());
}

void handleToggle()
{
  digitalWrite(LED_PIN, HIGH);
  myserver.sendHeader("Location", "/");
  myserver.send(303);
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, Pass);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println(WiFi.localIP());

  myserver.on("/", handleRoot);
  myserver.on("/toggle", handleToggle);
  myserver.begin();
}

void loop()
{
  myserver.handleClient();
}


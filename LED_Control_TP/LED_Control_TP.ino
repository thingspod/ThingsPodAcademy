#include <WiFi.h>
#include <Thingspod.h>

#define WIFI_SSID "ThingspodAcademy"
#define WIFI_PASSWORD "************"

const char *TOKEN = "jUeeZsc8CxVd06FTo57Z"; // Enter your Token Here
#define THINGSPOD_SERVER "thingspod.com"
#define THINGSPOD_MQTT_PORT 31883

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
Thingspod thingspod(wifiClient, &mqttClient);

int status = WL_IDLE_STATUS;
int ledPin = 2;
bool ledState;


void setup() {

  Serial.begin(115200);
  initWifi();
  mqttClient.setServer(THINGSPOD_SERVER, THINGSPOD_MQTT_PORT);
  mqttClient.setCallback(mqttCallback);

  pinMode(ledPin, OUTPUT);
}

void initWifi() {
  Serial.println("\nConnecting to AP ...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to AP");
}

void mqttCallback(char *topic, byte *payload, unsigned int length) {
  thingspod.onMessage(topic, payload, length);
}

RPCCallback setLedState("setLedState", ledStateCallback);
RPCResponse ledStateCallback(const RPCData &data) {
  ledState = data;
  digitalWrite(ledPin, ledState);
  thingspod.sendAttributeBool("ledState", ledState);

  RPCResponse response(NULL, ledState);
  return response;
}

void loop() {
  delay(600);

  if (WiFi.status() != WL_CONNECTED) {
    reconnectWifi();
  }

  if (!thingspod.connected()) {

    Serial.print("Connecting to: ");
    Serial.print(THINGSPOD_SERVER);
    Serial.print("with token ");
    Serial.println(TOKEN);

    if (!thingspod.connect(THINGSPOD_SERVER, THINGSPOD_MQTT_PORT, TOKEN)) {
      Serial.println("Failed to connect");
      return;
    }
    thingspod.RPCSubscribe(setLedState);
    

  }

  if (thingspod.connected())
  {
    thingspod.mqttClientLoop();
  }
}
  void reconnectWifi() {
    status = WiFi.status();

    if (status != WL_CONNECTED) {
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("\nConnected to AP");
    }
  }

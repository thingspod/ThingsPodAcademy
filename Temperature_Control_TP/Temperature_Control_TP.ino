#include "DHT.h"
#include <WiFi.h>
#include <Thingspod.h>


#define WIFI_SSID "ThingspodAcademy"
#define WIFI_PASSWORD "************"

const char *TOKEN = "72oCcaj765MsPWNx4E07";
#define THINGSPOD_SERVER "thingspod.com"
#define THINGSPOD_MQTT_PORT 31883

#define DHTPIN 5
#define DHTTYPE DHT11

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
Thingspod thingspod(wifiClient, &mqttClient);

DHT dht(DHTPIN, DHTTYPE);

int status = WL_IDLE_STATUS;

unsigned long lastMillis = 0;
int fanPin1 = 2;
int fanPin2 = 4;
float temperature;

bool fanState;
bool autoState = false;

void setup() {

  Serial.begin(115200);
  initWifi();
  mqttClient.setServer(THINGSPOD_SERVER, THINGSPOD_MQTT_PORT);
  mqttClient.setCallback(mqttCallback);

  dht.begin();
  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
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

RPCCallback setAutoState("setAutoState", setAutoStateCallback);
RPCResponse setAutoStateCallback(const RPCData &data) {
  autoState = data;
  thingspod.sendAttributeBool("autoState", autoState);
  if (autoState == false) {
    fanState = false;
    thingspod.sendAttributeBool("fanState", fanState);
    digitalWrite(fanPin1, LOW);
    digitalWrite(fanPin2, LOW);
  }
  RPCResponse response(NULL, autoState);
  return response;
}

RPCCallback getAutoState("getAutoState", getAutoStateCallback);
RPCResponse getAutoStateCallback(const RPCData &data) {

  RPCResponse response(NULL, autoState);
  return response;
}

RPCCallback setFanState("setFanState", setFanStateCallback);
RPCResponse setFanStateCallback(const RPCData &data) {
  fanState = data;
  if (autoState == true) {
    if (fanState == true) {
      digitalWrite(fanPin1, HIGH);
      digitalWrite(fanPin2, LOW);
    } else if (fanState == false) {
      digitalWrite(fanPin1, LOW);
      digitalWrite(fanPin2, LOW);
    }
  }
  thingspod.sendAttributeBool("fanState", fanState);
  RPCResponse response(NULL, fanState);
  return response;
}

RPCCallback getFanState("getFanState", getFanStateCallback);
RPCResponse getFanStateCallback(const RPCData &data) {
  fanState = digitalRead(fanPin1);
  RPCResponse response(NULL, fanState);
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

    thingspod.RPCSubscribe(setAutoState);
    thingspod.RPCSubscribe(getAutoState);
    thingspod.RPCSubscribe(setFanState);
    thingspod.RPCSubscribe(getFanState);
  }

  if (thingspod.connected()) {
    thingspod.mqttClientLoop();
  }

  if (millis() - lastMillis > 2000) {
    temperature = dht.readTemperature();
    if (isnan(temperature)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("°C ");

    StaticJsonDocument<JSON_OBJECT_SIZE(1)> jsonBuffer;
    JsonVariant object = jsonBuffer.template to<JsonVariant>();

    object["Temperature"] = temperature;
    thingspod.sendTelemetryJson(object);
    lastMillis = millis();
  }
  if (autoState == true) {
    if (temperature > 26) {
      digitalWrite(fanPin1, HIGH);
      digitalWrite(fanPin2, LOW);
      thingspod.sendAttributeBool("fanState", true);

    } else if (temperature < 26) {
      digitalWrite(fanPin1, LOW);
      digitalWrite(fanPin2, LOW);
      thingspod.sendAttributeBool("fanState", false);
    }
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

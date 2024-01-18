#include "DHT.h"
#include <WiFi.h>
#include <Thingspod.h>

#define DHTPIN 5
#define DHTTYPE DHT11

#define WIFI_SSID "Ronika"
#define WIFI_PASSWORD "*******************"

const char *TOKEN = "Xs616JWi229AWnTfKX4k";
#define THINGSPOD_SERVER "thingspod.com"
#define THINGSPOD_MQTT_PORT 31883

DHT dht(DHTPIN, DHTTYPE);

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
Thingspod thingspod(wifiClient, &mqttClient);

int status = WL_IDLE_STATUS;
unsigned long lastMillis = 0;

void setup() {

  Serial.begin(115200);
  initWifi();
  mqttClient.setServer(THINGSPOD_SERVER, THINGSPOD_MQTT_PORT);

  dht.begin();
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
  }
    if (thingspod.connected()) {
      thingspod.mqttClientLoop();
    }
    if (millis() - lastMillis > 2000) {

      float h = dht.readHumidity();
      float t = dht.readTemperature();
      float f = dht.readTemperature(true);

      if (isnan(h) || isnan(t) || isnan(f)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }
      Serial.print("Humidity: ");
      Serial.print(h);
      Serial.print("%  Temperature: ");
      Serial.print(t);
      Serial.print("°C ");
      Serial.print(f);
      Serial.println("°F");

      StaticJsonDocument<JSON_OBJECT_SIZE(2)> jsonBuffer;
      JsonVariant object = jsonBuffer.template to<JsonVariant>();

      object["Temperature"] = t;
      object["Humidity"] = h;
      thingspod.sendTelemetryJson(object);
      lastMillis = millis();
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
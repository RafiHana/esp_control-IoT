#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "NAMA_WIFI";
const char* password = "PASSWORD_WIFI";

const char* mqttBroker = "broker.emqx.io"; 
const int mqttPort = 1883;
const char* clientId = "esp32-client";
const char* temperatureTopic = "suhu";
const char* humidityTopic = "kelembapan";
const char* co2Topic = "karbon_dioksida";
const char* smokeTopic = "asap";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setup() {
  Serial.begin(115200);
  connectWiFi();
  mqttClient.setServer(mqttBroker, mqttPort);
}

void loop() {
  if (!mqttClient.connected()) {
    connectMQTT();
  }
  mqttClient.loop();

  float temperature = readTemperature(); 
  float humidity = readHumidity();       
  int co2 = readCO2();                 
  int smoke = readSmoke();              

  mqttClient.publish(temperatureTopic, String(temperature).c_str());
  mqttClient.publish(humidityTopic, String(humidity).c_str());
  mqttClient.publish(co2Topic, String(co2).c_str());
  mqttClient.publish(smokeTopic, String(smoke).c_str());

  delay(5000); 
}

float readTemperature() {
  return 30.5;
}

float readHumidity() {
  return 60.0;
}

int readCO2() {
  return 500;
}

int readSmoke() {
  return 200;
}

void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nTerhubung ke WiFi!");
}

void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Menghubungkan ke MQTT...");
    if (mqttClient.connect(clientId)) {
      Serial.println("Terhubung ke MQTT!");
    } else {
      Serial.print("Gagal, error code: ");
      Serial.print(mqttClient.state());
      Serial.println(" Coba lagi dalam 2 detik...");
      delay(2000);
    }
  }
}
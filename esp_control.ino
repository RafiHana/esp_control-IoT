#include <WiFi.h>
#include <FirebaseESP32.h>

#define WIFI_SSID " "
#define WIFI_PASSWORD " "
#define FIREBASE_HOST " "
#define FIREBASE_AUTH " "

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi");
  }

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  float temperature = readTemperature();
  float humidity = readHumidity();
  float co2 = readCO2();
  float smoke = readSmoke();

  if (Firebase.setFloat(firebaseData, "/suhu", temperature)) {
    Serial.println("Succes");
  } else {
    Serial.println("Failed");
  }

  if (Firebase.setFloat(firebaseData, "/kelembapan", humidity)) {
    Serial.println("Succes");
  } else {
    Serial.println("Failed");
  }

  if (Firebase.setFloat(firebaseData, "/karbon_dioksida", co2)) {
    Serial.println("Succes");
  } else {
    Serial.println("Failed");
  }

  if (Firebase.setFloat(firebaseData, "/asap", smoke)) {
    Serial.println("Succes");
  } else {
    Serial.println("Failed");
  }

  delay(5000); 
}

float readTemperature() {
  return 25.0; 
}

float readHumidity() {
  return 60.0; 
}

float readCO2() {
  return 400.0; 
}

float readSmoke() {
  return 0.0; 
}
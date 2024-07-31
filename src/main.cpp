
//Code Eckhard Gerwien - Dieser Code steht zur freien Verfügung
// Einbinden der erforderlichen Libraries
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_SHT31.h>
// WLAN-Einstellungen
const char* ssid = "DEIN_SSID";
const char* password = "DEIN_PASSWORT";
// Webserver-URL
const char* serverName = "http://Deine_IP/sensordaten/empfangsscript.php";
// Erstellen eines Objekts für den SHT31 Sensor
Adafruit_SHT31 sht31 = Adafruit_SHT31();
void setup() {
  // Initialisierung der seriellen Kommunikation für Debugging
  Serial.begin(115200);
  // Initialisierung des I2C-Bus
  Wire.begin();
  // Initialisierung des SHT31 Sensors
  if (!sht31.begin(0x44)) {  // 0x44 ist die I2C-Adresse des SHT31
    Serial.println("Konnte SHT31 nicht finden, überprüfe die Verkabelung!");
    while (1) delay(1);
  }
  Serial.println("SHT31 Sensor gefunden!");
  // Verbindung zum WLAN herstellen
  WiFi.begin(ssid, password);
  Serial.print("Verbinde mit WLAN");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //Ausgaben an die serielle Schnittstelle
  Serial.println("");
  Serial.println("WLAN verbunden");
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.localIP());
}
//Code der regelmäßig in einer Schleife ausgeführt wird
void loop() {
  // Auslesen der Temperatur
  float temperature = sht31.readTemperature();
  // Auslesen der Luftfeuchtigkeit
  float humidity = sht31.readHumidity();
  // Überprüfen, ob die Messwerte gültig sind
  if (!isnan(temperature)) {  // isnan überprüft, ob der Wert 'NaN' (Not a Number) ist
    Serial.print("Temperatur: ");
    Serial.print(temperature);
    Serial.println(" °C");
  } else {
    Serial.println("Fehler beim Auslesen der Temperatur!");
  }
  if (!isnan(humidity)) {
    Serial.print("Luftfeuchtigkeit: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {
    Serial.println("Fehler beim Auslesen der Luftfeuchtigkeit!");
  }
  // Senden der Daten an den Webserver
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    // Übernahme der Messwerte in den String zum Senden
    String postData = "temperature=" + String(temperature) + "&humidity=" + String(humidity);
    int httpResponseCode = http.POST(postData);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi nicht verbunden");
  }
  // Wartezeit von 10 Sekunden vor der nächsten Messung
  delay(10000);
}
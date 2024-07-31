Sensordaten an einen eigenen Webserver senden

In diesem DIYTechAdventure zeige ich dir, wie du mit einem ESP32 über WLAN einen HTTP-Request durchführen 
und die erhaltenen Sensordaten des SHT31 in eine Datenbank auf einem Webserver schreiben kannst. 
Der ESP ist ein Mikrocontroller, der sich ideal für IoT-Projekte eignet.
Hierbei sollen uns die Beiträge ESP8266 ins WLAN bringen und Temperaturmessung mit dem SH3x als Grundlagenbildung dienen. 
Lies gerne nach, wenn du unsicher bist.

Schaue dir auch unbedingt die Grundlagen zum Senden von Daten an einen Webserver an. Ich gehe hier nicht mehr auf die Verbindung zum WLAN ein.

Als Lerneffekt habe ich in diesem DIYTechAdventure die Möglichkeit einer Absicherung von Inserts an die Datenbank beschrieben.

Voraussetzungen
Eine NodeMCU (ESP8266) -> bekommst du günstig bei AzDelivery oder Aliexpress
Einen SHT31-> bekommst du günstig bei Aliexpress
Zugang zu einem WLAN-Netzwerk
Ein Webserver mit einer Datenbank (z.B. MySQL)
Grundkenntnisse in Arduino-Programmierung und SQL

#include <ESP8266WiFi.h>
extern "C" {
  #include <stdint.h>
  #include <espnow.h>
}

#define WIFI_CHANNEL 1


void setup() {
  Serial.begin(115200); Serial.println();

  if (esp_now_init()!=0) {
    Serial.println("*** ESP_Now init failed");
    ESP.restart();
  }

  Serial.print("This node AP mac: "); Serial.print(WiFi.softAPmacAddress());
  Serial.print(", STA mac: "); Serial.println(WiFi.macAddress());
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);

  esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len) {
    Serial.print("mac=");
    char macString[50] = {0};
    sprintf(macString, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.print(macString);
    Serial.print(";");
    getReading(data, len);
  });
}

void loop() {
}

void getReading(uint8_t *data, uint8_t len) {

  Serial.print("rx=");
  for(int i=0; i < len; i++) {
       Serial.print(data[i], HEX);
   }
   Serial.print(";");
   Serial.println();
}

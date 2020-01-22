
#include <ESP8266WiFi.h>
extern "C" {
  #include <espnow.h>
}



// this is the MAC Address of the remote ESP which this ESP sends its data too
uint8_t remoteMac[] = {0x6A, 0xC6, 0x3A, 0xC2, 0xFE, 0x7A};

#define WIFI_CHANNEL 1
#define SEND_TIMEOUT 500

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin();

  if (esp_now_init()!=0) {
    ESP.restart();
  }

  delay(1); 

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(remoteMac, ESP_NOW_ROLE_SLAVE, WIFI_CHANNEL, NULL, 0);

  esp_now_register_send_cb([](uint8_t* mac, uint8_t status) {
      Serial.print(0x00);
  });
}

void loop() {
  if(Serial.available() > 0) {
    delay(15);
    int available = Serial.available();

    uint8_t data2send[available];

    Serial.readBytes(data2send, available);
    esp_now_send(NULL, data2send, sizeof(data2send));
  }
}

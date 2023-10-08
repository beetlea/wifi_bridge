#include <WiFi.h>
#include <HTTPClient.h>
#include "post.h"
#include "web.h"
#include "mem.h"


#define TIMEOUT  11

String server = "http://45.141.101.38/web/api/data-incom?token=Z5W2Doip3HsyIDYei8qol2uh_CXp-g5W";
String send_string = "&DataTypes_id=1&Nodes_id=65535&GPIO_id=0&rssi=-94&snr=5&Station_id=1&ResetCount=0";

static const char* ssid = "Keenetic-3902";
static const char* password = "1234567890b";

static const char* ssid_AP = "ESP32";
static const char* password_AP = "00000000";

static data_wifi d_w;

void init_wifi() {
  Serial.begin(115200);

  init_mem(&d_w);
  Serial.println(d_w.wifi);
  Serial.println(d_w.pass);
  Serial.println(d_w.server);
  Serial.println(d_w.token);

  WiFi.begin(ssid, d_w.pass_route);
  Serial.println("Connecting");
  int cnt_connect = 0;
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    cnt_connect++;
    if(cnt_connect == TIMEOUT)
    {
        Serial.print("Setting AP (Access Point)…");
        // Remove the password parameter, if you want the AP (Access Point) to be open
        WiFi.softAP(d_w.wifi, d_w.pass);

        IPAddress IP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(IP);
        break;
    }
  }

  if(cnt_connect != TIMEOUT)
  {
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
  }
 }


void setup() {
  init_wifi();
  Serial2.begin(19200); 
  init_web();
}



void loop() {
  if(Serial2.available())
  {
    Serial.println("data_recieve");
    String data;
    data = Serial2.readString();

    int cnt_attempt = 10;
    while(!send_post(d_w.server, d_w.token, "data=" + data + send_string))
    {
      if(!cnt_attempt)
      break;
      cnt_attempt--;
    }
  }
    tick();
}

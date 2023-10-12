#include <WiFi.h>
#include <HTTPClient.h>
#include "post.h"
#include "web.h"
#include "mem.h"
#include <HardwareSerial.h>

#define TIMEOUT  22

///int reset_time = 20000;
int reset_time = 86400000;////сутки

HardwareSerial Ser2(2);

static data_wifi   d_w;
static data_parser d_p;


void set_ip(String ip_)
{
  IPAddress ip;
  
  ip.fromString(ip_);
  
  IPAddress local_IP(ip[0], ip[1], ip[2], ip[3]);
  IPAddress gateway(192, 168, 1, 1);
  
  IPAddress subnet(255, 255, 0, 0);
  IPAddress primaryDNS(8, 8, 8, 8);
}
void init_wifi() {
  Serial.begin(115200);

  init_mem(&d_w);
  Serial.println(d_w.wifi);
  Serial.println(d_w.pass);
  Serial.println(d_w.server);
  Serial.println(d_w.token);

  WiFi.begin(d_w.name_route, d_w.pass_route);
  Serial.println("Connecting");
  int cnt_connect = 0;
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    cnt_connect++;
    if(cnt_connect == TIMEOUT * 2)
    {
        Serial.print("\nSetting AP (Access Point)…");
        // Remove the password parameter, if you want the AP (Access Point) to be open
        WiFi.softAP(d_w.wifi, d_w.pass);

        IPAddress IP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(IP);
        Serial.println("WiFi  = " + String(d_w.wifi));
        Serial.println("PASS = " + String(d_w.pass));
        break;
    }
  }

  if(cnt_connect != TIMEOUT * 2)
  {
    ///set_ip(String(d_w.ip));
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println("WiFi  = " + String(d_w.name_route));
    Serial.println("PASS = " + String(d_w.pass_route));
  }
 }

void IRAM_ATTR serialEventRun(){
  while(Ser2.available())
  {
    char data = Ser2.read();
    d_p.input += (char)data;  
  }

}

void setup() {
  init_wifi();
  Ser2.begin(19200,SERIAL_8N1, 16, 17 ); 
  Ser2.onReceive(&serialEventRun);
  init_web();
}



void loop() {


  if(parser(&d_p) != 0)
  {

    String data_send = build_query(&d_p);

    int cnt_attempt = 10;

    while(!send_post(d_w.server, d_w.token, data_send))
    {
      if(!cnt_attempt)
      {
        ESP.restart();
      }
      cnt_attempt--;
      delay(100);
    }
  }

  if(millis() > reset_time)
  {
    ESP.restart();
  }
  tick();
}

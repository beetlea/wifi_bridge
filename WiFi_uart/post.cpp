
#include <WiFi.h>
#include <HTTPClient.h>

#define OK         1
#define NO_CONNECT 0




int send_post(String server, String token, String data) {


      WiFiClient client;
      HTTPClient http;   
      http.begin(client, server + "?token=" + token);
      
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      Serial.println(server + "?token=" +token + data);
      int httpResponseCode = http.POST(data);           
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      if(httpResponseCode != 201)
      {
        return NO_CONNECT;
      }
      http.end();
      return OK;
}

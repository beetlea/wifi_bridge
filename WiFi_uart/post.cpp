
#include <WiFi.h>
#include <HTTPClient.h>
#include "post.h"

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


int test_packet(int begin, int end)
{
  if(begin >= end)
  {
    Serial.println("Битый пакет. Неправильное поле.");
    return 0;
  }
  return 1;
}

int find_string(char symbol, String str, int len)
{
  for(int i = 0; i < len - 1; i++)
  {
    if(symbol == str[i])
    {
      return i;
    }
  }
  return -1;
}

int parser(data_parser * d_p)
{
  int begin_packet = 0;
  int end_packet   = 0;
  char temp[500];
  d_p->input.toCharArray(temp, 500);
  begin_packet = find_string('$', d_p->input, (sizeof(temp)) - 1);
  end_packet   = find_string(';', d_p->input, (sizeof(temp)) - 1);

  if(((sizeof(temp)) > 100) and (begin_packet == -1))
  {
    d_p->input.remove(0, (sizeof(temp)));
  }
  if((begin_packet != -1) and (end_packet != -1))
  {
    if(begin_packet < end_packet)
    {
      int end = d_p->input.indexOf(" ", begin_packet);
      if (!test_packet(begin_packet, end))
      {
        d_p->input.remove(0, end_packet + 1);
        return 0;
      }
      String num = d_p->input.substring(begin_packet + 1, end);

      d_p->id = num.toInt();
      d_p->input.remove(0, end);
      begin_packet = 1;

      num = String();
      end = d_p->input.indexOf(" ", begin_packet);
      if (!test_packet(begin_packet, end))
      {
        d_p->input.remove(0, end_packet + 1);
        return 0;
      }
      num = d_p->input.substring(begin_packet, end);

      d_p->data_1 = num.toInt();
      d_p->input.remove(0, end);
      begin_packet = 1;

      num = String();
      end = d_p->input.indexOf(" ", begin_packet);
      if (!test_packet(begin_packet, end))
      {
        d_p->input.remove(0, end_packet + 1);
        return 0;
      }
      num = d_p->input.substring(begin_packet, end);

      d_p->data_2 = num.toInt();
      d_p->input.remove(0, end);
      begin_packet = 1;     

      num = String();
      end = d_p->input.indexOf(" ", begin_packet);
      if (!test_packet(begin_packet, end))
      {
        d_p->input.remove(0, end_packet + 1);
        return 0;
      }
      num = d_p->input.substring(begin_packet, end);

      d_p->data_3 = num.toInt();
      d_p->input.remove(0, end);
      begin_packet = 1;  

      num = String();
      end = d_p->input.indexOf(" ", begin_packet);
      if (!test_packet(begin_packet, end))
      {
        d_p->input.remove(0, end_packet + 1);
        return 0;
      }
      num = d_p->input.substring(begin_packet, end);

      d_p->data_4 = num.toInt();
      d_p->input.remove(0, end);
      begin_packet = 1;  

      num = String();
      end = d_p->input.indexOf(" ", begin_packet);
      if (!test_packet(begin_packet, end))
      {
        d_p->input.remove(0, end_packet + 1);
        return 0;
      }
      num = d_p->input.substring(begin_packet, end);

      d_p->rssi = num.toInt();
      d_p->input.remove(0, end);
      begin_packet = 1;  

      num = String();
      end = d_p->input.indexOf(";", begin_packet);
      if (!test_packet(begin_packet, end))
      {
        d_p->input.remove(0, end_packet + 1);
        return 0;
      }
      num = d_p->input.substring(begin_packet, end);

      d_p->snr = num.toInt();
      d_p->input.remove(0, end + 1);
      begin_packet = 1;  

      d_p->cnt_mes += 1;
    }
    else
    {
      d_p->input.remove(0, end_packet + 1);
      Serial.println("Битый пакет");
    }
  }
  return d_p->cnt_mes;
}


String build_query(data_parser * d_p)
{
  String data = "data=" + String(d_p->data_1) + "|" + String(d_p->data_2) + "|" + String(d_p->data_3) + "|" \
                + String(d_p->data_4) + "&DataTypes_id=1&Nodes_id=" + String(d_p->id) + "&GPIO_id=0&rssi="       \
                + String(d_p->rssi) + "&snr=" + String(d_p->snr) + "&Station_id=1&ResetCount=0";
  Serial.println(data);
  d_p->cnt_mes = 0;
  return data;
}

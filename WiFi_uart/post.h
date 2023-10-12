#ifndef POST_H
#define POST_H

struct data_parser
{
  int cnt_mes;
  long id;
  long data_1;
  long data_2;
  long data_3;
  long data_4;
  int  rssi;
  int snr;
  String input;
};

int send_post(String server, String token, String data);
String build_query(data_parser * d_p);
int test_packet(int begin, int end);
int parser(data_parser * d_p);
int find_string(char symbol, String str);
#endif
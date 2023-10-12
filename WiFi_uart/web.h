#ifndef WEB_H
#define WEB_H
struct data_wifi{ 
  char wifi[100];
  char pass[100];
  char server[100];
  char token[100];
  char name_route[100];
  char pass_route[100];
  char ip[100];
};

void init_web();
void build();
void action();
void tick();
data_wifi get_wifi_setup();
int flag_get_data();
void init_mem();

#endif
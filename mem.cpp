#include "SPIFFS.h"
#include "web.h"
#include "mem.h"

char * default_server = "http://45.141.101.38/web/api/data-incom";
char * default_wifi   = "ESP32";
char * default_pass   = "00000000";
char * default_token  = "Z5W2Doip3HsyIDYei8qol2uh_CXp-g5W";
char * dafault_pass_r = "1234567890b";
char * dafault_ip     = "192.168.4.1";
#define OK         1
#define ERROR      0

static data_wifi d_w;

void init_mem(data_wifi * d_w)
{
    if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
  }

  if(!read_server(d_w->server))
  {
    write_server(default_server);

    for(int i = 0; i < strlen(default_server); i++)
    {
      d_w->server[i] = default_server[i];
    }
  }

  if(!read_wifi(d_w->wifi))
  {
    write_wifi(default_wifi);
    
    for(int i = 0; i < strlen(default_wifi); i++)
    {
      d_w->wifi[i] = default_wifi[i];
    }
  }

  if(!read_pass(d_w->pass))
  {
    write_pass(default_pass);
    
    for(int i = 0; i < strlen(default_pass); i++)
    {
      d_w->pass[i] = default_pass[i];
    }
  }

  if(!read_token(d_w->token))
  {
    write_token(default_token);
    
    for(int i = 0; i < strlen(default_token); i++)
    {
      d_w->token[i] = default_token[i];
    }
  }

  if(!read_pass_route(d_w->pass_route))
  {
    write_pass_route(dafault_pass_r);
    
    for(int i = 0; i < strlen(dafault_pass_r); i++)
    {
      d_w->pass_route[i] = dafault_pass_r[i];
    }
  }

  if(!read_ip(d_w->ip))
  {
    write_ip(dafault_ip);
    
    for(int i = 0; i < strlen(dafault_ip); i++)
    {
      d_w->ip[i] = dafault_ip[i];
    }
  }
}


void write_new_setting(data_wifi * d_w)
{
  if(strlen(d_w->server) > 0)
    write_server(d_w->server);

  if(strlen(d_w->wifi) > 0)  
    write_wifi(d_w->wifi);

  if(strlen(d_w->pass) > 0)  
    write_pass(d_w->pass);

  if(strlen(d_w->token) > 0) 
    write_token(d_w->token);
  
  if(strlen(d_w->pass_route) > 0) 
    write_token(d_w->pass_route);

  if(strlen(d_w->ip) > 0) 
    write_ip(d_w->ip);

  ESP.restart();
}



int write_wifi(char * str)
{
  File file = SPIFFS.open("/wifi.txt", FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for reading");
    return ERROR;
  }
  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return ERROR;
  }
  if (file.print(str)) {
    Serial.println("File was written");
  } else {
    Serial.println("File write failed");
  }
 
  file.close();

  return OK;
}


int write_ip(char * str)
{
  File file = SPIFFS.open("/ip.txt", FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for reading");
    return ERROR;
  }
  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return ERROR;
  }
  if (file.print(str)) {
    Serial.println("File was written");
  } else {
    Serial.println("File write failed");
  }
 
  file.close();

  return OK;
}

int write_pass(char * str)
{
  File file = SPIFFS.open("/pass.txt", FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for reading");
    return ERROR;
  }
  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return ERROR;
  }
  if (file.print(str)) {
    Serial.println("File was written");
  } else {
    Serial.println("File write failed");
  }
 
  file.close();

  return OK;
}

int write_pass_route(char * str)
{
  File file = SPIFFS.open("/pass_route.txt", FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for reading");
    return ERROR;
  }
  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return ERROR;
  }
  if (file.print(str)) {
    Serial.println("File was written");
  } else {
    Serial.println("File write failed");
  }
 
  file.close();

  return OK;
}

int write_token(char * str)
{
  File file = SPIFFS.open("/token.txt", FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for reading");
    return ERROR;
  }
  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return ERROR;
  }
  if (file.print(str)) {
    Serial.println("File was written");
  } else {
    Serial.println("File write failed");
  }
 
  file.close();

  return OK;
}

int write_server(char * str)
{
  File file = SPIFFS.open("/server.txt", FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for reading");
    return ERROR;
  }
  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return ERROR;
  }
  if (file.print(str)) {
    Serial.println("File was written");
  } else {
    Serial.println("File write failed");
  }
 
  file.close();

  return OK;
}

int read_server(char * str)
{
  File file = SPIFFS.open("/server.txt", FILE_READ);
  if(!file){
    Serial.println("Failed to open file for reading");
    return ERROR;
  }

  Serial.println("File Content:");
  int cnt_byte = 0;
  while(file.available()){
    
    str[cnt_byte] = file.read();
    Serial.write(str[cnt_byte]);
    cnt_byte++;
  }
  Serial.println();
  str[cnt_byte] = '\0';
  file.close();
  return cnt_byte;
}

int read_token(char * str)
{
  File file = SPIFFS.open("/token.txt", FILE_READ);
  if(!file){
    Serial.println("Failed to open file for reading");
    return ERROR;
  }
  Serial.println("File Content:");
  int cnt_byte = 0;
  while(file.available()){
    
    str[cnt_byte] = file.read();
    Serial.write(str[cnt_byte]);
    cnt_byte++;
  }
  Serial.println();
  str[cnt_byte] = '\0';
  file.close();
  return cnt_byte;
}

int read_pass(char * str)
{
  File file = SPIFFS.open("/pass.txt", FILE_READ);
  if(!file){
    Serial.println("Failed to open file for reading");
    return ERROR;
  }

  Serial.println("File Content:");
  int cnt_byte = 0;
  while(file.available()){
    
    str[cnt_byte] = file.read();
    Serial.write(str[cnt_byte]);
    cnt_byte++;
  }
  Serial.println();
  str[cnt_byte] = '\0';
  file.close();
  return cnt_byte;
}

int read_wifi(char * str)
{
  File file = SPIFFS.open("/wifi.txt", FILE_READ);
  if(!file){
    Serial.println("Failed to open file for reading");
    return ERROR;
  }

  Serial.println("File Content:");
  int cnt_byte = 0;
  while(file.available()){
    
    str[cnt_byte] = file.read();
    Serial.write(str[cnt_byte]);
    cnt_byte++;
  }
  Serial.println();
  str[cnt_byte] = '\0';
  file.close();
  return cnt_byte;
}


int read_pass_route(char * str)
{
  File file = SPIFFS.open("/pass_route.txt", FILE_READ);
  if(!file){
    Serial.println("Failed to open file for reading");
    return ERROR;
  }

  Serial.println("File Content:");
  int cnt_byte = 0;
  while(file.available()){
    
    str[cnt_byte] = file.read();
    Serial.write(str[cnt_byte]);
    cnt_byte++;
  }
  Serial.println();
  str[cnt_byte] = '\0';
  file.close();
  return cnt_byte;
}


int read_ip(char * str)
{
  File file = SPIFFS.open("/ip.txt", FILE_READ);
  if(!file){
    Serial.println("Failed to open file for reading");
    return ERROR;
  }

  Serial.println("File Content:");
  int cnt_byte = 0;
  while(file.available()){
    
    str[cnt_byte] = file.read();
    Serial.write(str[cnt_byte]);
    cnt_byte++;
  }
  Serial.println();
  str[cnt_byte] = '\0';
  file.close();
  return cnt_byte;
}

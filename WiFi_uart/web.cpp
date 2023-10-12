#include <GyverPortal.h>
#include "web.h"
#include "mem.h"



GyverPortal ui;

void build();
void action();

static data_wifi d_wifi;

static int flag_data = 0;

void init_web()
{
  ui.start();
  ui.attachBuild(build);
  ui.attach(action);
}

void build(void) {

  GP.BUILD_BEGIN(GP_DARK);
  GP.PAGE_TITLE("WI-FI BRIDGE"); 

  GP.FORM_BEGIN("/update");
  GP.LABEL("WIFI_AP"); 
  GP.TEXT("wifi", "", d_wifi.wifi);  
  GP.BREAK();
  
  GP.LABEL("PASS_AP"); 
  GP.TEXT("password", "", d_wifi.pass); 
  GP.BREAK();
  
  GP.LABEL("Server"); 
  GP.TEXT("server", "", d_wifi.server); 
  GP.BREAK();

  GP.LABEL("Token"); 
  GP.TEXT("token", "", d_wifi.token); 
  GP.BREAK();

  GP.LABEL("NAME_R"); 
  GP.TEXT("name_r", "", d_wifi.name_route); 
  GP.BREAK();

  GP.LABEL("PASS_R"); 
  GP.TEXT("pass", "", d_wifi.pass_route); 
  GP.BREAK();

  GP.LABEL("IP_R"); 
  GP.TEXT("ip", "", d_wifi.ip); 
  GP.BREAK();

  GP.SUBMIT("Сохранить");
  
  GP.BUILD_END();


}


void action() {
  if (ui.form()) {
    // проверяем, была ли это форма "/update"
    if (ui.form("/update")) {
        ui.copyStr("wifi", d_wifi.wifi);
        ui.copyStr("password", d_wifi.pass);
        ui.copyStr("server", d_wifi.server);
        ui.copyStr("token", d_wifi.token);
        ui.copyStr("name_r", d_wifi.name_route);
        ui.copyStr("pass", d_wifi.pass_route);
        ui.copyStr("ip", d_wifi.ip);
        
        Serial.println("Wifi " + String(d_wifi.wifi));
        Serial.println("password AP " + String(d_wifi.pass));
        Serial.println("server " + String(d_wifi.server));
        Serial.println("token " + String(d_wifi.token));
        Serial.println("name_r " + String(d_wifi.name_route));
        Serial.println("pass " + String(d_wifi.pass_route));
        Serial.println("ip " + String(d_wifi.ip));
        write_new_setting(&d_wifi);  
            
        flag_data = 1;
      }
  }
}

int flag_get_data()
{
  if(flag_data == 1)
  {
    flag_data = 0;
    return 1;
  }
  return 0;
}

data_wifi get_wifi_setup()
{
  return d_wifi;
}

void tick()
{
    ui.tick();
}

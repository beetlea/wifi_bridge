#ifndef MEM_H
#define MEM_H
void init_mem(data_wifi * d_w);
int write_wifi(char * str);
int write_pass(char * str);
int write_token(char * str);
int write_server(char * str);
int write_name_route(char * str);
int write_pass_route(char * str);
int write_ip(char * str);

int read_server(char * str);
int read_token(char * str);
int read_pass(char * str);
int read_wifi(char * str);
int read_pass_route(char * str);
int read_ip(char * str);
int read_name_route(char * str);

void write_new_setting(data_wifi * d_w);

#endif
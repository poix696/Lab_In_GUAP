#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <experimental/filesystem>
#include <iostream>
#include <string>
#include <cstring>

namespace fs = std::experimental::filesystem::v1;
using namespace std;
#define BUFFER_SIZE 1024

void search_file(string dir, string expan, char* buff)
{
try {
for (auto &p : fs::directory_iterator(dir))
{
if(!fs::is_regular_file(p.status())) {continue;}
std::string name_e(p.path().filename());
if(name_e.find(expan) == string::npos) {continue;}
bool match  =!name_e.compare(name_e.size() - expan.size(), expan.size(), expan);
if(!match) {continue ;}
name_e.append(" ");
const char *c = name_e.c_str();
strcat(buff, c);
}}
catch (exception &e) {
const char *b = "not find this directory";
strcat(buff, b);
return; }
int kolbyte;
memcpy(&kolbyte, buff, 4);
if(kolbyte == 0)
{const char *a = "not find files in directory";
strcat(buff, a);}
}

int main(int arcg, char *argv[])
{
struct sockaddr_in addr;
char buff_read1[BUFFER_SIZE]={};
char buff[BUFFER_SIZE]={};
string expan;
string dir;
int listener = socket (AF_INET, SOCK_STREAM, 0);
if(listener <0)
{
perror("socket");
exit(1);
}

addr.sin_family = AF_INET;
addr.sin_port = htons(1234);
addr.sin_addr.s_addr = htonl(INADDR_ANY);

int opt_val=1;
setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val));

if(bind(listener, (struct sockaddr*)&addr, sizeof(addr))<0)
{
perror("bind");
exit(2);
}

if(listen(listener, SOMAXCONN)<0)
{
perror("listen");
exit(3);
}
int err;
while (1)
{
int sock = accept(listener, 0, 0);

if(sock<0)
{
perror("accept");
return 0;
}
while(1) {
int bytes_read=recv(sock, buff_read1, BUFFER_SIZE, 0);
if(bytes_read<=0) {break;}
cout<<"Incoming data: "<<buff_read1<<endl;
try {
dir = string(buff_read1);
string::size_type pos = dir.find(".");
expan = dir.substr(pos);
dir.erase(pos); }
catch(...){
const char *a = "Incorrect input";
strcat(buff, a);
send (sock, buff, BUFFER_SIZE, 0);
memset(buff_read1, 0, BUFFER_SIZE);
memset(buff,0, BUFFER_SIZE);
break; }
search_file(dir, expan, buff);
int error = send (sock, buff, BUFFER_SIZE, 0);
if(err <0) {perror ("send"); }
memset(buff_read1, 0, BUFFER_SIZE);
memset(buff,0, BUFFER_SIZE);
}
}
return 0;
}

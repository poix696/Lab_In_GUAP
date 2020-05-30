#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

int main()
{
struct sockaddr_in addr;
char buff[1024];
int listener = socket (AF_INET, SOCK_STREAM, 0);
if(listener <0)
{
perror("socket");
exit(1);
}
int opt =1;
if(setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))==-1)
{
perror("setsockopt");
exit(2);
}
addr.sin_family = AF_INET;
addr.sin_port = htons(1234);
addr.sin_addr.s_addr = htonl(INADDR_ANY);
if(bind(listener, (struct sockaddr *) &addr, sizeof(addr))<0)
{
perror("bind");
exit(3);
}
listen(listener, 1);
while (1)
{
int sock =accept(listener, NULL, NULL);
if(sock<0)
{
perror("sock");
exit(4);
}
while (1)
{
int bytes_read=recv (sock, buff, sizeof(buff),0);
if(bytes_read<0)
{
break;
}
}
close(sock);
}
return 0;
}

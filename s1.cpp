#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
using namespace std;

#define MYPORT 8000
int main(){
int fd1;
struct sockaddr_in my_addr;
fd1 = socket(PF_INET,SOCK_DGRAM,0);
my_addr.sin_family = AF_INET;
my_addr.sin_port = htons(MYPORT);
my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
memset(&(my_addr.sin_zero),'\0',8);
bind(fd1,(struct sockaddr *) & my_addr,sizeof(struct sockaddr));

char buf[100];
struct sockaddr_in google_addr;

google_addr.sin_family = AF_INET;
google_addr.sin_port = htons(8000);
google_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
memset(&(google_addr.sin_zero),'\0',8);
socklen_t len = sizeof(my_addr);
sendto(fd1,"Hi Google",9,0,(struct sockaddr*)&google_addr,sizeof(google_addr));
int n = recvfrom(fd1,buf,99,0,(struct sockaddr*)&my_addr,&len);
 buf[n] = '\0';

    cout << "Received: " << buf << endl;
    cout << "Number of bytes: " << n << endl;

    close(fd1);
}
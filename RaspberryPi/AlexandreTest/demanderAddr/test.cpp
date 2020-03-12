#include <stdio.h> 
#include <unistd.h> 
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
  
   //char hostname[256];
 void PrintIp(const char * hostname)
{ 
    struct hostent * host; 
    struct in_addr addr; 
  
    if ((host = gethostbyname(hostname)) != NULL) 
    { 
        int i; 
  
        for(i = 0; host->h_addr_list[i] != NULL; i++) 
        { 
            memcpy(&addr.s_addr, host->h_addr_list[i], sizeof(addr.s_addr)); 
            printf("IP : %s\n", inet_ntoa(addr)); 
        } 
    } 
    else 
        printf("La fonction gethostbyname a echoue.\n"); 
	
}
 
int main(void) 
{ 
    char hostname[256]; 
  
    if (gethostname(hostname, sizeof(hostname)) == 0) 
        printf("%s\n", hostname); 
    else 
    {
        fprintf(stderr, "La fonction gethostname a echoue.\n"); 
        PrintIp(hostname);
	}
       
    return 0;
}
  



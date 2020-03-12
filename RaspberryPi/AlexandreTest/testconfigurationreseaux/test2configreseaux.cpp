#include <stdio.h> 
#include <unistd.h> 
  
int main(void) 
{ 
    char hostname[256]; 
  
    if (gethostname(hostname, sizeof(hostname)) == 0) 
        printf("%s\n", hostname); 
    else 
        fprintf(stderr, "La fonction gethostname a echoue.\n"); 
  
    return 0; 
}

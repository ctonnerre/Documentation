#define IFNAME "wlan0"
#include <iostream>


int fd;
struct ifreq ifr;
u_char *addr;
u_char *mask;

fd = socket (AF_INET, SOCK_DGRAM,IPPROTO_IP);
memset (&ifr, 0, sizeof (struct ifreq));
strcpy (ifr.ifr_name, IFNAME);
ifr.ifr_addr.sa_family = AF_INET;
ioctl(fd, SIOCGIFADDR, &ifr);

ioctl(fd, SIOCGIFADDR, &ifr);
addr=(u_char*)&(((struct sockaddr_in * )&ifr.ifr_addr)->sin_addr);
ioctl (fd, SIOCGIFNETMASK, &ifr);
mask=(u_char*)&(((struct sockaddr_in * )&ifr.ifr_netmask)->sin_addr);

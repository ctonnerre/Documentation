#include <iostream>
#include <fstream>
#include <string>
using namespace std; 

int main()
{
   ifstream fichier("/etc/dhcpcd.conf");
   string strCherche ("static ip_address");
   string strnew
   
   
   
   if(fichier)
   {
      //L'ouverture s'est bien passée, on peut donc lire

      string ligne; //Une variable pour stocker les lignes lues

      while(getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
      {
      
         cout << "longueur : " << ligne.length() << " " << ligne << endl;
         cout << "numero ou commance la chaine de charactere static ip address : " << ligne.find(strCherche) << " " << endl;
            

      }
   }
   else
   {
      cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
   }
   

   return 0;
}

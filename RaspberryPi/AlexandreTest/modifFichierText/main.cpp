#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    
    string a;
    string b;
    string strReplace = "static ip_address=192.168.1.145/24";       //ligne qui doit etre modifier ( ligne de base )
        
    cout << "votre nouvelle ip " << endl << "exemple : 192.168.1.125" << endl;                   //demande nouvell ip en x.x.x.x
    cin >> a ;
    
    cout << "votre nouveau mask " << endl <<"exemple : /8 /16 /24 ou /29" << endl ;                  //demande nouveau mask en /x
    cin >> b ;                                                      
    
    string strReplaceNew = strReplace;                              //creation d'une copie de strReplace ( qui s'appele strReplaceNew )
    strReplaceNew.erase(18,20);                                     //suprime les 20 caracteres aprés le 18 eme ( dans notre cas apres le = )
    string strNew = strReplaceNew + a + b ;                         //creation d'un nouveau string qui associe strReplaceNew et l'IP que l'utilisateur a entrer
    
    cout << "strReplace : " << strReplace << endl;                 //affiche  la ligne qui doit etre modifier ( ligne de base : static ip_address=192.168.1.145/24)
    cout << "strReplaceNew : " <<strReplaceNew << endl;            //affiche  la ligne apres la suppression de l'IP (static ip_address=)
    cout << "strNew : " <<strNew << endl;                          //affiche  la ligne qui doit remplacer l'acien ( ligne de base : static ip_address=x.x.x.x/x )
    
    
    
    ifstream filein("dhcpcd.conf"); //File to read from
    ofstream fileout("newdhcpcd.conf"); //Temporary file
    if(!filein || !fileout)
    {
        cout << "Error opening files!" << endl;
        return 1;
    }

    string strTemp;
    //bool found = false;
    while(getline(filein,strTemp))
    {
        if(strTemp == strReplace){
            strTemp = strNew;
            //found = true;
        }
        strTemp += "\n";
        fileout << strTemp;
        //if(found) break;
    }
    
      if( remove( "dhcpcd.conf" ) != 0 )
    perror( "Error deleting file" );
    
    else
    puts( "File successfully deleted" );

    
    if (rename("newdhcpcd.conf", "dhcpcd.conf")!=0) 
        perror( "Error deleting file" );
  else
    puts( "File successfully renamed" );
    
    return 0;
}

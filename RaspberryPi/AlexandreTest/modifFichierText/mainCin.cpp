#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    char strNew[100];

    cout << "Enter une address ip: ";
    cin >> strNew;
    cout << "You entered: " << strNew ;

    string strReplace = "static ip_address=192.168.1.143/24";
   // string strNew = "static ip_address=192.168.1.145/24";
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



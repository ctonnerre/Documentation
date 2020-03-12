#include<iostream>
using namespace std;

int main()
{

int a;
cout<<"Tapez un entier : ";cin>>a;
if((a>=56)&&(a<=78))cout<<"GAGNE"<<endl; else cout<<"PERDU"<<endl;

cout << "Appuyez sur une touche pour continuer ..." << endl;
cin.ignore();
cin.get();
return EXIT_SUCCESS;
}

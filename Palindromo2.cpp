#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {


int  n;
cout<<"Numero de palabras a verificar:";
cin>>n;
std::ofstream archivo("yes_or_no.txt",ios::app);

string y;
for(int N=1;N<=n;N++){



  string palabra;

  cout<<"Ingrese una palabra:" ;

  cin>>palabra;
  int j=0;
  int l=palabra.length();
  if (l%2==0){
	for(int i=0;i<=l/2-1;i++){
		 if(palabra[i]==palabra[l-i-1]){
				j++;
				continue;
               } else {
		                break;
                 }

		}
	if(j==l/2){
		std::cout<<"La palabra'"<< palabra<< "'es un palindromo"<<std::endl;

                y="SI";

      } else {
		std::cout<<"La palabra'"<< palabra<< "'no es un palindromo"<<std::endl;

		y="NO";
}
} else {
	for(int i=0;i<=(l-1)/2;i++){
                 if(palabra[i]==palabra[l-i-1]){
				j++;
                                continue;
               } else {
                                break;
                 }
}
	 if(j==(l+1)/2){
                std::cout<<"La palabra'"<< palabra<< "'es un palindromo"<<std::endl;

		y="SI";
      }  else {
                std::cout<<"La palabra'"<< palabra<< "'no es un palindromo"<<std::endl;

		y="NO";
}
}
archivo << palabra << "\t" << y << endl;
std::cout<<"Se a añadido la palabra al archivo"<<std::endl;
}
archivo.close();
}

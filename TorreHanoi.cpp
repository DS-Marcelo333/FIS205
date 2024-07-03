#include <iostream>
#include <string>
void Th(int n, char inicio, char final, char comodin) {
    if (n >0) {
    Th(n - 1, inicio, comodin, final);
    std::cout << "Mover disco " << n << " desde " << inicio << " a " << final << std::endl;
    Th(n - 1, comodin, final, inicio);
}
}
int main() {
    int discos;
    std::cout << "Ingrese el número de discos: ";
    std::cin >> discos;
    std::cout << "Los movimientos a seguir son:\n";
    std::string i,f,c;
    std::cout<<"Indique pilar de inicio(A,B,C):";
    std::cin>>i;
    std::cout<<"Indique pilar final(A,B,C):";
    std::cin>>f;
    std::cout<<"Indique pilar comodin(A,B,C):";
    std::cin>>c;
    Th(discos, i[0], f[0], c[0]);
    return 0;
}

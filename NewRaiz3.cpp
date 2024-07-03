#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main() {
    double x;
    double y;
    cout << "Escribe un valor inicial de x: ";
    cin >> x;
    double R = sqrt(2);
    double D;
    do {
        y = (0.5) * (x + 2.0 / x);
        D = abs(R - y);
        x = y;
    } while (D >= 0.000001);
cout << fixed <<setprecision(6);
    cout << "La aproximación para la raíz cuadrada de 2 mediante el método de Newton-Raphson es: " << y << endl;
    return 0;
}

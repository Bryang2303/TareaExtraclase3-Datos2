// Program to find the parity of a given number
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// Funcion para obtener la paridad de un numero
bool ParityCheck(int x)
{
    int y = x ^ (x >> 1);
    y = y ^ (y >> 2);
    y = y ^ (y >> 4);
    y = y ^ (y >> 8);
    y = y ^ (y >> 16);

    // 1 si la cantidad de unos del numero en forma binaria es par
    if (y & 1)
        return 1;
    return 0;
}


int main()
{
    int opcion;


    do {
        cout << "Seleccione cual de los tres algoritmos de deteccion de errores \ndesea ejemplificar: " << endl;
        cout << "1) ParityCeck" << endl;
        cin >> opcion;
        switch (opcion) {
        case 1:
            cout << "ParityCheck seleccionado" << endl;
            cout << "Seleccione 1 si quiere una demostracion de los casos de prueba 9 (1001), \n13 (1011) y 8 (1000), o 2 si desea probar con un numero diferente  " << endl;
            int opcionPC;
            cin >> opcionPC;
            if (opcionPC == 1){
                cout << "Ejecutando casos de prueba..." << endl;
                (ParityCheck(9)==0)?cout << "Paridad de " << 9 << ": Even (Par)" << endl:
                                        cout << "Paridad de " << 9 << ": Odd (Impar)" << endl;
                (ParityCheck(13)==0)?cout << "Paridad de " << 13 << ": Even (Par)" << endl:
                                        cout << "Paridad de " << 13 << ": Odd (Impar)" << endl;
                (ParityCheck(8)==0)?cout << "Paridad de " << 8 << ": Even (Par)" << endl:
                                        cout << "Paridad de " << 8 << ": Odd (Impar)" << endl;
            } else {
                int pruebaPC;
                cout << "Ingrese un numero entero: " << endl;
                cin >> pruebaPC;
                (ParityCheck(pruebaPC)==0)?cout << "Paridad de " << pruebaPC << ": Even (Par)" << endl:
                                        cout << "Paridad de " << pruebaPC << ": Odd (Impar)" << endl;
            }
            cout << "" << endl;
            break;
        case 5:
            opcion = 5;
            break;
        }
    }
    while (opcion != 5);


    return 0;
}

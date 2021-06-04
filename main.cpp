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


// XOR
string XOR(string a, string b)
{

    string resultado = "";

    int n = b.length();

    //Si los bits son iguales, entonces el retorno de XOR es 0, de lo contrario es 1
    for(int i = 1; i < n; i++)
    {
        if (a[i] == b[i]){
            cout << " XOR entre " << a[i] << " y " << b[i] << " : 0" << endl;
            resultado += "0";
        }else {
            cout << " XOR entre " << a[i] << " y " << b[i] << " : 1" << endl;
            resultado += "1";
        }
    }
    return resultado;
}

// Division de Modulo 2
string mod2D(string divident, string divisor)
{
    int pick = divisor.length();
    string tmp = divident.substr(0, pick);
    int n = divident.length();

    while (pick < n)
    {
        if (tmp[0] == '1')

            //Reemplazar el divisor por el resultado de XOR
            tmp = XOR(divisor, tmp) + divident[pick];
        else

            // En caso de que el bit mas a la izquierda sea 0
            tmp = XOR(std::string(pick, '0'), tmp) +
                  divident[pick];
        pick += 1;
    }
    if (tmp[0] == '1'){
        tmp = XOR(divisor, tmp);

    } else {
        tmp = XOR(std::string(pick, '0'), tmp);
    }
    return tmp;
}

//Función en el lado del remitente para codificar datos mediante la agregacion del residuo de la división modular al final de los datos.
void codificarData(string data, string key)
{
    int l_key = key.length();

    // Agregar n-1 ceros al final de la data
    string datosAdjuntos = (data +
                            std::string(
                                l_key - 1, '0'));

    string remainder = mod2D(datosAdjuntos, key);

    // Agregar el remainder a la data original
    string codeword = data + remainder;
    cout << "Remainder : "
         << remainder << "\n";
    cout << "Data Final (Data + Remainder) :"
         << codeword << "\n";
}


int main()
{
    int opcion;


    do {
        cout << "Seleccione cual de los tres algoritmos de deteccion de errores \ndesea ejemplificar: " << endl;
        cout << "1) CRC Code Generation" << endl;
        cout << "2) Parity Ceck" << endl;
        cin >> opcion;
        switch (opcion) {
        case 1:
            cout << "CRC Code Generation seleccionado" << endl;
            cout << "Seleccione 1 si quiere una demostracion de el caso de prueba key: 1101\nData inicial: 100100, o 2 si desea probar con diferentes valores." << endl;
            int opcionCRC;
            cin >> opcionCRC;
            if (opcionCRC == 1){
                cout << "Ejecutando caso de prueba..." << endl;
                string data = "100100";
                string key = "1101";
                codificarData(data, key);
            } else {
                string data;
                string key;
                cout << "Ingrese un valor de Data binario " << endl;
                cin >> data;
                cout << "Ingrese un valor de polinomio generador (key) binario " << endl;
                cin >> key;
                codificarData(data, key);
            }
            cout << "" << endl;
            break;

        case 2:
            cout << "Parity Check seleccionado" << endl;
            cout << "Seleccione 1 si quiere una demostracion de los casos de prueba 9 (1001), \n13 (1011) y 8 (1000), o 2 si desea probar con un numero diferente.  " << endl;
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

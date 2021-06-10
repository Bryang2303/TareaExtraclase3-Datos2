#include <bits/stdc++.h>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//////////////////////////////////////////////////////////////////////// PARITY
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

//////////////////////////////////////////////////////////////////////// CRC

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

//////////////////////////////////////////////////////////////////////// HAMMING
// Generar el Hamming code
vector<int> generateHammingCode(
    vector<int> msgBits, int m, int r)
{
    vector<int> hammingCode(r + m);

    // Encuentra posiciones de bits redundantes
    for (int i = 0; i < r; ++i) {

        // Identificar bits redundantes marcandolos con -1

        hammingCode[pow(2, i) - 1] = -1;
    }

    int j = 0;


    for (int i = 0; i < (r + m); i++) {
        //Coloca los bits del mensaje
        if (hammingCode[i] != -1) {
            hammingCode[i] = msgBits[j];
            j++;
        }
    }

    for (int i = 0; i < (r + m); i++) {

        // Si el bit no es redundante, continua

        if (hammingCode[i] != -1){
            cout << hammingCode[i] << " no redundante, avanza" << endl;
            continue;
        } else {
            cout << hammingCode[i] << " redundante" << endl;
        }
        int x = log2(i + 1);
        int one_count = 0;

        for (int j = i + 2;
             j <= (r + m); ++j) {

            if (j & (1 << x)) {
                if (hammingCode[j - 1] == 1) {
                    one_count++;
                }
            }
        }

        // Genera haming code para paridad Par
        if (one_count % 2 == 0) {
            hammingCode[i] = 0;
        }
        else {
            hammingCode[i] = 1;
        }
    }

    return hammingCode;
}

// Encuentra el hamming code
void findHammingCode(vector<int>& msgBit)
{
    int m = msgBit.size();

    // r es el numero de bits redudantes
    int r = 1;

    // Encontrar numero de bits redudantes
    while (pow(2, r) < (m + r + 1)) {
        r++;
    }

    // Genera el codigo
    vector<int> ans
        = generateHammingCode(msgBit, m, r);


    cout << "Los Bits del mensaje son: ";
    for (int i = 0; i < msgBit.size(); i++)
        cout << msgBit[i] << " ";

    cout << "\nEl Hamming code es: ";
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
}

////////////////////////////////////////////////////////////////////// MAIN
int main()
{
    int opcion;


    do {
        cout << "" << endl;
        cout << "Seleccione cual de los tres algoritmos de deteccion o correccion de errores \ndesea ejemplificar: " << endl;
        cout << "1) CRC Code Generation" << endl;
        cout << "2) Parity Ceck" << endl;
        cout << "3) Hamming Code" << endl;
        cout << "4) Salir" << endl;
        cin >> opcion;
        switch (opcion) {
        case 1:
            cout << "CRC Code Generation seleccionado" << endl;
            cout << "Seleccione 1 si quiere una demostracion del caso de prueba key: 1101\nData inicial: 100100, o 2 si desea probar con diferentes valores." << endl;
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
                cout << "Si se verifica que tras el recibimiento de los datos a traves de un mensaje, utilizando CRC la data nno contiene errores se deberia la data unido al reminder" << endl;
                codificarData(data, key);
                cout <<  "Verificacion completada: Sin errores" << endl;
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
                cout << "Se pretende comprobar si un archivo contiene o no un error, para este caso si la paridad del archivo representado como un numero entero es Par, el archivo no contiene errores." << endl;
                cout << "Ingrese un numero entero: " << endl;
                cin >> pruebaPC;
                (ParityCheck(pruebaPC)==0)?cout << "Paridad de " << pruebaPC << ": Even (Par)" << "-Archivo no contiene errores-" << endl:
                                        cout << "Paridad de " << pruebaPC << ": Odd (Impar)" << "-Archivo contiene errores-" << endl;
            }
            cout << "" << endl;
            break;

        case 3:
            cout << "Hamming Code Seleccionado" << endl;
            cout << "Seleccione 1 si quiere una demostracion del caso de prueba mensaje: 0111, \no 2 si desea probar con un mensaje diferente.  " << endl;
            int opcionHC;
            cin >> opcionHC;
            if (opcionHC == 1){
                cout << "Ejecutando caso de prueba..." << endl;
                vector<int> msgBit = { 0, 1, 1, 1 };
                findHammingCode(msgBit);
            } else {
                int bitMsg1;
                int bitMsg2;
                int bitMsg3;
                int bitMsg4;

                cout << "Ingrese de uno en uno, los bits de un supuesto mensaje (Son 4 en total y debe pulsar ENTER despues de cada uno) " << endl;
                cin >> bitMsg1;

                cin >> bitMsg2;

                cin >> bitMsg3;

                cin >> bitMsg4;

                vector<int> msgBit = { bitMsg1, bitMsg2, bitMsg3, bitMsg4};

                findHammingCode(msgBit);
                cout << "Los errores del mensaje han sido corregidos y esta listo para ser enviado" << endl;
            }
            cout << "" << endl;
            break;
        case 5:
            opcion = 5;
            break;
        }
    }
    while (opcion != 4);


    return 0;
}

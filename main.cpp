/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Oscar Azofeifa
 *
 * Created on 18 de agosto de 2016, 07:49 PM
 */

#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>
#include "SintetizadorDeTexto.h"
#include "AnalizadorDePalabras.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    bool flg = true;

    while (flg) {
        system("clear");
        cout << " _______________________________________________________" << endl;
        cout << "|                                                       |" << endl;
        cout << "|                                                       |" << endl;
        cout << "|                    PLAGIUS C++ 1.0                    |" << endl;
        cout << "|                                                       |" << endl;
        cout << "|_______________________________________________________|" << endl;
        sleep(2);
        system("clear");

        string in1, in2;
        cout << "Escriba la direccion del archivo fuente A: " << endl;
        cin >> in1;
        system("clear");

        cout << "Escribo la direccion del archivo fuente B: " << endl;
        cin >> in2;
        system("clear");

        AnalizadorDePalabras analizer( in1, in2 );

        list< string > analysis = analizer.analize();
        list< string >::iterator lines = analysis.begin();

        for (int i = 0; i < 6; i++) {
            cout << *lines << endl;
            lines++;
        }

        char c;
        cout << "\nDigite D para ver detalles | A para analizar otros archivos | X para salir" << endl;
        cin >> c;

        bool flgCommand = true;
        while (flgCommand) {
            switch ( c ) {
                case 'D':
                    for (; lines != analysis.end(); lines++) {
                        cout << *lines << endl;
                    }
                    cout << "\nDigite A para analizar otros archivos | X para salir" << endl;
                    cin >> c;
                    break;
                case 'A':
                    flgCommand = false;
                    break;

                case 'X':
                    flgCommand = false;
                    flg = false;
            }
        }
    }

    return 0;
}


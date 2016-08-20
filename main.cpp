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
#include <iostream>
#include <string>
#include "SintetizadorDeTexto.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    string in = "in.txt";
    string out = "out.txt";
    SintetizadorDeTexto prueba(in, out);
    cout << prueba.readLn() << endl;
    cout << prueba.readLn() << endl;
    cout << prueba.readLn() << endl;
    return 0;
}


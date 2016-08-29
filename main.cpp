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
    string in = "fibonacci.c";
    string out = "out.txt";
    SintetizadorDeTexto prueba(in, out);
    
    SintetizadorDeTexto prueba1("in.txt", "bla.txt");
    
    
    prueba.makeLowercase();
    //prueba.addLineNumbers();
    prueba.quitComments();
    prueba.quitSymbols();
    prueba.quitReserved();
    prueba.quitSpaces();
    
    
    
            
    int wordsNum = prueba.getWordsNumber();
    cout <<  wordsNum << endl;
    for (int i = 0; i < wordsNum; i++){
        cout << prueba.readWord()<< endl;;
    }
    return 0;
}


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SintetizadorDeTexto.h
 * Author: Oscar Azofeifa
 *
 * Created on 18 de agosto de 2016, 08:07 PM
 */


#ifndef SINTETIZADORDETEXTO_H
#define SINTETIZADORDETEXTO_H


#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

class SintetizadorDeTexto {
public:
    
    SintetizadorDeTexto();
    
    SintetizadorDeTexto(string fileIn, string fileOut);
    
    SintetizadorDeTexto(const SintetizadorDeTexto& orig);
    
    virtual ~SintetizadorDeTexto();
    
    void addLineNumbers();
    
    fstream* getFileIn();
    
    fstream* getFileOut();
    
    int getWordsNumber();
    
    void justComments();
    
    void makeLowercase();
    
    void quitComments();
    
    void quitReserved();
    
    void quitSpaces();
    
    string readLn();
    
    string readWord();
    
    void setFileIn(string fileIn);
    
    void setFileOut(string fileOut);
    
private:
    
    fstream* fileIn;
    
    fstream* fileOut;
    
    fstream* fileTemp;
    
    void saveTemp();
    
};

#endif /* SINTETIZADORDETEXTO_H */
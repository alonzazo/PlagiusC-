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

#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include "TrieTree.h"

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
    
    void quitSymbols();
    
    void quitSpaces();
    
    char* readLn();
    
    string readWord();
    
    void setFileInDir(string fileIn);
    
    void setFileOutDir(string fileOut);
    
    static int instanceCounter;
    
private:
    
    
    
    string fileInDir;
    
    string fileOutDir;
    
    string fileTempDir;
    
    fstream* fileIn;
    
    fstream* fileOut;
    
    fstream* fileTemp;
    
    char readBuffer[256];
    
    void resetStream();
    
    void saveTemp();
};

#endif /* SINTETIZADORDETEXTO_H */
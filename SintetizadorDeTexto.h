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
    
    SintetizadorDeTexto(const SintetizadorDeTexto& orig);
    
    virtual ~SintetizadorDeTexto();
    
    void SintetizadorDeTexto::addLineNumbers();
    
    fstream* SintetizadorDeTexto::getFileIn();
    
    fstream* SintetizadorDeTexto::getFileOut();
    
    int SintetizadorDeTexto::getWordsNumber();
    
    void SintetizadorDeTexto::justComments();
    
    void SintetizadorDeTexto::makeLowercase();
    
    void SintetizadorDeTexto::quitComments();
    
    void SintetizadorDeTexto::quitReserved();
    
    void SintetizadorDeTexto::quitSpaces();
    
    string SintetizadorDeTexto::readLn();
    
    string SintetizadorDeTexto::readWord();
    
    void SintetizadorDeTexto::setFileIn(string fileIn);
    
    void SintetizadorDeTexto::setFileOut(string fileOut);
    
private:
    
    fstream fileIn;
    fstream fileOut;
    fstream fileTemp;
    
    void SintetizadorDeTexto::saveTemp();
    
};

#endif /* SINTETIZADORDETEXTO_H */


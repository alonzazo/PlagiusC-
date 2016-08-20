/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SintetizadorDeTexto.cpp
 * Author: Oscar Azofeifa
 * 
 * Created on 18 de agosto de 2016, 08:07 PM
 */

#include "SintetizadorDeTexto.h"

SintetizadorDeTexto::SintetizadorDeTexto() {
}

SintetizadorDeTexto::SintetizadorDeTexto(string fileIn, string fileOut) {
    this->fileIn = new fstream();
    this->fileOut = new fstream();
    
    this->fileIn->open(fileIn);
    this->fileOut->open(fileOut);
}

SintetizadorDeTexto::SintetizadorDeTexto(const SintetizadorDeTexto& orig) {   
    
 }

SintetizadorDeTexto::~SintetizadorDeTexto() {

}

void SintetizadorDeTexto::addLineNumbers(){

}

fstream* SintetizadorDeTexto::getFileIn(){
}

fstream* SintetizadorDeTexto::getFileOut(){
}

int SintetizadorDeTexto::getWordsNumber(){
}

void SintetizadorDeTexto::justComments(){
}

void SintetizadorDeTexto::makeLowercase(){
}

void SintetizadorDeTexto::quitComments(){
}

void SintetizadorDeTexto::quitReserved(){
}

void SintetizadorDeTexto::quitSpaces(){
    char pointer;
    bool modeWriter = true;
    while (!fileIn->eofbit){
        
        pointer = fileIn->get();//Obtenemos un caracter
        if (modeWriter){
            if (pointer == ' '){
                modeWriter = true;
            }
            fileOut->put(pointer);//Escribimos el caracter en el nuevo archivo
        } 
        else if (pointer != ' '){
            modeWriter = false;
            fileOut->put(pointer);//Escribimos el caracter
        }
    }   
}

string SintetizadorDeTexto::readLn(){
}

string SintetizadorDeTexto::readWord(){
}

void SintetizadorDeTexto::setFileIn(string fileIn){
}

void SintetizadorDeTexto::setFileOut(string fileOut){
}

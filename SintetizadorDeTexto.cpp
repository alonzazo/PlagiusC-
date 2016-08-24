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
    //Definimos atributos
    this->fileInDir = fileIn;
    this->fileOutDir = fileOut;
    
    this->fileIn = new fstream();
    this->fileOut = new fstream();
    
    //Abrmos archivos
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
    
    //Inicia el algoritmo
    char pointer;                        // Apuntador de caracter
    bool modeWriter = true;              // Bandera de escritura
    while ( !fileIn->eof() ){
        
        pointer = fileIn->get();         //Obtenemos un caracter
        if ( modeWriter ){
            if (pointer == ' '){
                modeWriter = false;
            }
            fileOut->put( pointer );      //Escribimos el caracter en el nuevo archivo
        } 
        else if (pointer != ' '){
            modeWriter = true;
            fileOut->put( pointer );      //Escribimos el caracter
        }
    
    }
    
    //Cerramos archivos para guardar y abrimos
    fileOut->close();
    fileOut->open( fileOutDir );
}

char* SintetizadorDeTexto::readLn(){
    
    fileOut->getline(readBuffer, 256);
    
    return readBuffer;

}

string SintetizadorDeTexto::readWord(){
    
}

void SintetizadorDeTexto::setFileIn(string fileIn){

}

void SintetizadorDeTexto::setFileOut(string fileOut){
}

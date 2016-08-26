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
    
    //Abrimos archivos
    this->fileIn->open(fileIn);
    this->fileOut->open(fileOut);
    
    this->fileTempDir = "tmp";
    
    this->resetStream();
}

SintetizadorDeTexto::SintetizadorDeTexto(const SintetizadorDeTexto& orig) {   
    
}

SintetizadorDeTexto::~SintetizadorDeTexto() {

}

void SintetizadorDeTexto::addLineNumbers(){
    //Limpiamos el fileOut
    fileOut->close();
    fileOut->open(fileOutDir,ios::in | ios::out | ios::trunc);
    
    char pointer;
    int counter = 1;
    string counterStr;
    bool flagNewLine = true;
    
    pointer = fileTemp->get();
    if (pointer != '\n'){
        flagNewLine = false;
    }
    while(!fileTemp->eof()){
        
        pointer = fileTemp->get();
        
        //HACE FALTA
    }
    
    //Cerramos archivos para guardar y abrimos
    fileOut->close();
    fileOut->open( fileOutDir );
    
    saveTemp();
}

fstream* SintetizadorDeTexto::getFileIn(){
    return this->fileIn;
}

fstream* SintetizadorDeTexto::getFileOut(){
    return this->fileOut;
}

int SintetizadorDeTexto::getWordsNumber(){
    
}

void SintetizadorDeTexto::justComments(){
    
    //Limpiamos el fileOut
    fileOut->close();
    fileOut->open(fileOutDir,ios::in | ios::out | ios::trunc);
    
    //Inicializamos apuntadores y banderas.
    char pointer[3];
    bool lineFlag = false;
    bool paragraphFlag = false;
    long pos;
    //Analizamos el texto
    while ( !fileTemp->eof() ){
        
        pointer[2] = pointer[1];
        pointer[1] = pointer[0];
        pointer[0] = fileTemp->get();
        
        //Si se encuentra un */ con el paragraphFlag levantado terminamos de escribir
        if (paragraphFlag){
            if ( pointer[0] == '/' && pointer[1] == '*' ){
                paragraphFlag = false;
                fileOut->put(pointer[2]);
            }
        } 
        //Si se termina la linea con el lineFlag levantado terminamos de escribir
        else if (pointer[0] == '\n'){
            if (lineFlag == true){
                lineFlag = false; 
            }
            fileOut->put('\n');
        } else {
            
            if ( pointer[1] == '*' && pointer[2] == '/' ){
                paragraphFlag = true;
                
                pointer[2] = pointer[1];
                pointer[1] = pointer[0];
                pointer[0] = fileTemp->get();
                
                pointer[2] = pointer[1];
                pointer[1] = pointer[0];
                pointer[0] = fileTemp->get();
            }
            if ( pointer[1] == '/' && pointer[2] == '/' ){
                lineFlag = true;
            }
       
        }
        
        if ( paragraphFlag || lineFlag ){
            if (paragraphFlag){
                fileOut->put(pointer[2]);
            }
            else {
                fileOut->put(pointer[0]);
            }
        }
        
    }
    
    //Cerramos archivos para guardar y abrimos
    fileOut->close();
    fileOut->open( fileOutDir );
    
    saveTemp();
   
}

void SintetizadorDeTexto::makeLowercase(){
    
    //Limpiamos el fileOut
    fileOut->close();
    fileOut->open(fileOutDir,ios::in | ios::out | ios::trunc);
    
    char pointer;
    
    while (!fileTemp->eof()){
        
        pointer = fileTemp->get();
        
        if (pointer > 64 && pointer < 90){
            pointer += 32;
        }
        
        fileOut->put(pointer);
    }
    
    //Cerramos archivos para guardar y abrimos
    fileOut->close();
    fileOut->open( fileOutDir );
    
    saveTemp();
}

void SintetizadorDeTexto::quitComments(){
    
    
    //Limpiamos el fileOut
    fileOut->close();
    fileOut->open(fileOutDir,ios::in | ios::out | ios::trunc);
    
    //Inicializamos apuntadores y banderas.
    char pointer[3] = {0,0,0};
    bool lineFlag = false;
    bool paragraphFlag = false;
    long pos;
    //Analizamos el texto
    while ( !fileTemp->eof() ){
        
        pointer[2] = pointer[1];
        pointer[1] = pointer[0];
        pointer[0] = fileTemp->get();
        
        //Si se encuentra un */ con el paragraphFlag levantado terminamos de escribir
        if (paragraphFlag){
            if ( pointer[0] == '/' && pointer[1] == '*' ){
                paragraphFlag = false;
                
                pointer[2] = pointer[1];
                pointer[1] = pointer[0];
                pointer[0] = fileTemp->get();
                
                pointer[2] = pointer[1];
                pointer[1] = pointer[0];
                pointer[0] = fileTemp->get();
            }
        } 
        //Si se termina la linea con el lineFlag levantado terminamos de escribir
        else if (pointer[2] == '\n'){
            if (lineFlag == true){
                lineFlag = false; 
            }
        } else {
            
            if ( pointer[0] == '*' && pointer[1] == '/' ){
                paragraphFlag = true;
            }
            if ( pointer[0] == '/' && pointer[1] == '/' ){
                lineFlag = true;
            }
       
        }
        
        if ( !(paragraphFlag || lineFlag) && pointer[2] != 0 ){
            
            fileOut->put(pointer[2]);
            
        }
        
    }
    
    //Cerramos archivos para guardar y abrimos
    fileOut->close();
    fileOut->open( fileOutDir );
    
    saveTemp();
}

void SintetizadorDeTexto::quitReserved(){
}

void SintetizadorDeTexto::quitSpaces(){
    
    //Limpiamos el fileOut
    fileOut->close();
    fileOut->open(fileOutDir,ios::in | ios::out | ios::trunc);
    
    //Inicia el algoritmo
    char pointer;                        // Apuntador de caracter
    bool modeWriter = true;              // Bandera de escritura
    while ( !fileTemp->eof() ){
        
        pointer = fileTemp->get();         //Obtenemos un caracter
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
    
    saveTemp();
}

char* SintetizadorDeTexto::readLn(){
    
    fileOut->getline(readBuffer, 256);
    
    return readBuffer;

}

string SintetizadorDeTexto::readWord(){
    
    return "";
    
}

void SintetizadorDeTexto::setFileInDir(string fileIn){
    
    this->fileInDir = fileIn;
    
}

void SintetizadorDeTexto::setFileOutDir(string fileOut){
    
    this->fileOutDir = fileOut;
    
}

void SintetizadorDeTexto::resetStream(){
    
    //Creamos y vaciamos un archivo temporal
    this->fileTemp = new fstream(this->fileTempDir, ios::in | ios::out | ios::trunc);
    //this->fileTemp << flush;
    this->fileTemp->close();
    delete this->fileTemp;
    
    //Abrimos el nuevo archivo creado
    this->fileTemp = new fstream();
    this->fileTemp->open(this->fileTempDir);
    
    if ( this->fileIn->is_open() && this->fileTemp->is_open() ){
        
        //Copiamos el archivo de entrada al temporal
        while( !this->fileIn->eof() ){
            this->fileTemp->put( this->fileIn->get() );
        }
        
        //Reabrimos archivo temporal para que se actualice la informacion
        this->fileTemp->close();
        this->fileTemp->open(this->fileTempDir);
        
        //De igual manera el archivo de entrada
        this->fileIn->close();
        this->fileIn->open(this->fileInDir);
    }
}

void SintetizadorDeTexto::saveTemp(){
    
    //Creamos y vaciamos un archivo temporal
    this->fileTemp = new fstream(this->fileTempDir, ios::in | ios::out | ios::trunc);
    //this->fileTemp << flush;
    this->fileTemp->close();
    delete this->fileTemp;
    
    //Abrimos el nuevo archivo creado
    this->fileTemp = new fstream();
    this->fileTemp->open(this->fileTempDir);
    
    this->fileOut->close();
    this->fileOut->open(this->fileOutDir);
    
    if ( this->fileOut->is_open() && this->fileTemp->is_open() ){
        
        //Copiamos el archivo de entrada al temporal
        while( !this->fileOut->eof() ){
            this->fileTemp->put( this->fileOut->get() );
        }
        
        //Reabrimos archivo temporal para que se actualice la informacion
        this->fileTemp->close();
        this->fileTemp->open(this->fileTempDir);
        
        //De igual manera el archivo de entrada
        this->fileOut->close();
        this->fileOut->open(this->fileOutDir);
    }
}
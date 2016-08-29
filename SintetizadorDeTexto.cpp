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

#include <list>
#include "SintetizadorDeTexto.h"

int SintetizadorDeTexto::instanceCounter = 0;

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
    
    
    this->fileTempDir = "tmp" + std::to_string(instanceCounter);
    instanceCounter++;
    
    this->resetStream();
}

SintetizadorDeTexto::SintetizadorDeTexto(const SintetizadorDeTexto& orig) {   
    
}

SintetizadorDeTexto::~SintetizadorDeTexto() {
    fileIn->close();
    fileOut->close();
    fileTemp->close();
    
    delete fileIn;
    delete fileOut;
    delete fileTemp;
    
    char del[16] = "rm ";
    system(strcat(del, fileTempDir.data()));
    
}

void SintetizadorDeTexto::addLineNumbers(){
    //Limpiamos el fileOut
    fileOut->close();
    fileOut->open(fileOutDir,ios::in | ios::out | ios::trunc);
    
    //Inicializamos las variables necesarias:
    char pointer;                               //Apuntador
    int counter = 1;                            //Contador de linea
    bool flagNewLine = true;                    //Bandera: Indica que se hizo un 
                                                //      salto de linea en el 
                                                //      caracter anterior.
    
    //Caso de excepcion 1: El caso donde no hay linea predecesora.
    pointer = fileTemp->get();
    if (pointer != '\n'){
        flagNewLine = false;
        *fileOut << "1 ";
        fileOut->put(pointer);
    } 
    else {
        counter++;
    }
    
    //ALGORITMO
    while(!fileTemp->eof()){
        
        pointer = fileTemp->get();
        
        if (flagNewLine){
            //Se encuentra salto de linea y con salto predecesor.
            if (pointer == '\n'){
                counter++;
            } 
            //Con salto predecesor, se agrega numero de linea.
            else {
                flagNewLine = false;
                *fileOut << counter << " ";
                fileOut->put(pointer);
            }
            
        } else {
            //Se encuentra salto de linea pero sin salto predecesor.
            if (pointer == '\n'){
                flagNewLine = true;
                counter++;
            }
            
            //Caso generico
            fileOut->put(pointer);
        }
        
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
    //Reseteamos el apuntador del fileOut
    fileOut->close();
    fileOut->open(fileOutDir);
    
    char pointer = fileOut->get();
    int counter = 0;
    bool wordMode = false;
    
    while (!fileOut->eof()){
        
        if (!wordMode && pointer != ' ' && pointer != '\n' || pointer == '\t'){
            wordMode = true;
            counter++;
        } else if (wordMode && (pointer == ' ' || pointer == '\n' || pointer == '\t')){
            wordMode = false;
        }
        
        pointer = fileOut->get();
    }
    
    //Cerramos archivos para guardar y abrimos
    fileOut->close();
    fileOut->open( fileOutDir );
    
    return counter;
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
        
        //Si se encuentra un */ con el paragraphFlag levantado terminamos de 
        //   escribir.
        if (paragraphFlag){
            if ( pointer[0] == '/' && pointer[1] == '*' ){
                paragraphFlag = false;
                fileOut->put(pointer[2]);
            }
        } 
        //Si se termina la linea con el lineFlag levantado terminamos de 
        //  escribir
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
    
    //Analizamos el texto
    while ( !fileTemp->eof() ){
        
        pointer[2] = pointer[1];
        pointer[1] = pointer[0];
        pointer[0] = fileTemp->get();
        
        //Si se encuentra un */ con el paragraphFlag levantado terminamos de 
        //  escribir
        if (paragraphFlag){
            if ( pointer[0] == '/' && pointer[1] == '*' ){
                paragraphFlag = false;
                
                for (int i = 0; i < 3 ; i++){
                    pointer[2] = pointer[1];
                    pointer[1] = pointer[0];
                    pointer[0] = fileTemp->get();
                }
                
            }
        } 
        //Si se termina la linea con el lineFlag levantado terminamos de 
        //  escribir
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
    //Limpiamos el fileOut
    fileOut->close();
    fileOut->open(fileOutDir,ios::in | ios::out | ios::trunc);
    
    //Instanciamos el stream de palabras reservadas.
    fstream reservedWordsFile("rsvwrds");
    //reservedWordsFile->open();
    
    char pointer;
    string word;
    //Pasamos las reservedWords a una estructura de dato mas facil de manejar
    TrieTree reservedWords;
    
    while (!reservedWordsFile.eof()){
        // Inicializamos y definimos variables.
        pointer = reservedWordsFile.get();
        word = "";
        
        // Se busca una palabra.
        while( !reservedWordsFile.eof() && ( pointer == ' ' || pointer == '\n' || pointer == '\t' ) ){
            pointer = reservedWordsFile.get();
        }
        
        // Se escribe la palabra encontrada.
        while (!reservedWordsFile.eof() && ( pointer != ' ' && pointer != '\n' || pointer == '\t' ) ){
            word += pointer;
            pointer = reservedWordsFile.get();
        }
        
        // Se agrega la palabra
        reservedWords.insert(word);
    
    }
    
    //ALGORITMO
    bool flag = false;
    while (!fileTemp->eof()){
        
        //Actualizamos apuntador
        pointer = fileTemp->get();
        word = "";
        
        // Se busca una palabra.
        while( !fileTemp->eof() && ( pointer == ' ' || pointer == '\n' || pointer == '\t') ){
            fileOut->put(pointer);  //Se escriben los espacios y saltos de linea
            pointer = fileTemp->get();
        }
        
        // Se captura la palabra encontrada.
        while (!fileTemp->eof() && ( pointer != ' ' && pointer != '\n' || pointer == '\t') ){
            word += pointer;
            pointer = fileTemp->get();
        }
        
        //Verificamos si la palabra es una reservedWord
        flag = reservedWords.search(word);
        /*for (std::list< string >::iterator i = reservedWords.begin(); 
                i != reservedWords.end(); i++){
            string s = i->data();
            if ( !word.compare(s) ){
                flag = true;
                break;
            }
            
        }*/
        
        //Si la palabra no es una reserved la escribe
        if (!flag){
            fileOut->write(word.data(),word.length());
            fileOut->put(pointer);
        } else {
            flag = false;
        }
    }
    
    //Cerramos archivos para guardar y abrimos
    fileOut->close();
    fileOut->open( fileOutDir );
    
    saveTemp();
}

void SintetizadorDeTexto::quitSymbols(){
    //Limpiamos el fileOut
    fileOut->close();
    fileOut->open(fileOutDir,ios::in | ios::out | ios::trunc);
    
    //Inicializamos las variables indispensables
    char pointer = fileTemp->get();
    
    while (!fileTemp->eof()){
        if (pointer == '(' || pointer == ')' || pointer == '{' || pointer == '}' || pointer == ',' || pointer == ';' || pointer == '*' ){
            fileOut->put(' ');
        } else {
            fileOut->put(pointer);
        }
        
        pointer = fileTemp->get();
    }
    
    //Cerramos archivos para guardar y abrimos
    fileOut->close();
    fileOut->open( fileOutDir );
    
    saveTemp();
}

void SintetizadorDeTexto::quitSpaces(){
    
    //Limpiamos el fileOut
    fileOut->close();
    fileOut->open(fileOutDir,ios::in | ios::out | ios::trunc);
    
    //Inicia el algoritmo
    char pointer;                           // Apuntador de caracter
    bool modeWriter = true;                 // Bandera de escritura
    while ( !fileTemp->eof() ){
        
        pointer = fileTemp->get();          // Obtenemos un caracter
        if ( modeWriter ){
            if (pointer == ' ' || pointer == '\t'){
                modeWriter = false;
            }
            fileOut->put( pointer );        // Escribimos el caracter en el 
                                            //      nuevo archivo.
        } 
        else if (pointer != ' ' && pointer != '\t'){
            modeWriter = true;
            fileOut->put( pointer );        //Escribimos el caracter
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
    // Inicializamos y definimos variables.
    char pointer = fileOut->get();
    string word = "";
        
    // Se busca una palabra.
    while( !fileOut->eof() && ( pointer == ' ' || pointer == '\n' || pointer == '\t' ) ){
        pointer = fileOut->get();
    }
        
    // Se escribe la palabra encontrada.
    while (!fileOut->eof() && ( pointer != ' ' && pointer != '\n' || pointer == '\t' ) ){
        word += pointer;
        pointer = fileOut->get();
    }        
    return word;
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
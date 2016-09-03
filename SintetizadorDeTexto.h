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
    
    //**************************CONSTRUCTORES***********************************
    SintetizadorDeTexto();
    
    SintetizadorDeTexto(string fileIn, string fileOut);
    
    SintetizadorDeTexto(const SintetizadorDeTexto& orig);
    
    virtual ~SintetizadorDeTexto();
    
    //**************************OPERACIONES BASICA******************************
    
    /*
     * EFECTO:      Agrega los numeros de linea al texto de salida.
     * REQUIERE:    Archivo de texto inicializado
     * MODIFICA:    Texto de salida.
     */
    void addLineNumbers();
    
    /*
     * EFECTO:      Retorna el fstream asociado a la entrada clase
     * REQUIERE:    -
     * MODIFICA:    -
     */
    fstream* getFileIn();
    
    /*
     * EFECTO:      Retorna el fstream asociado a la salida de clase
     * REQUIERE:    -
     * MODIFICA:    -
     */
    fstream* getFileOut();
    
    /*
     * EFECTO:      Retorna el numero de palabras de un archivo
     * REQUIERE:    Inicializado
     * MODIFICA:    -
     */
    int getWordsNumber();
    
    /*
     * EFECTO:      Retorna el numero de lineas con caracteres, es decir, no cuenta lineas vacias.
     * REQUIERE:    Inicializado
     * MODIFICA:    -
     */
    int getFilledLinesNumber();
    
    /*
     * EFECTO:      Indica si el cursor del archivo de salida llego a su fin.
     * REQUIERE:    Inicializado
     * MODIFICA:    -
     */
    int eof();
    
    /*
     * EFECTO:      Reinicia el cursor del archivo de salida para hacer nuevas lecturas.
     * REQUIERE:    Inicializado
     * MODIFICA:    -
     */
    void setCursorBegin();
    
    /*
     * EFECTO:      Escribe en archivo de salida unicamente los comentarios de una fuente C++.
     * REQUIERE:    Inicializado.
     * MODIFICA:    Archivo de salida y archivo temporal.
     */
    void justComments();
    
    /*
     * EFECTO:      Reescribe el archivo de salida usando unicamente minusculas.
     * REQUIERE:    Inicializado.
     * MODIFICA:    Archivo de salida y archivo temporal.
     */
    void makeLowercase();
    
    /*
     * EFECTO:      Reescribe el archivo de salida omitiendo los comentarios.
     * REQUIERE:    Inicializado.
     * MODIFICA:    Archivo de salida y archivo temporal.
     */
    void quitComments();
    
    /*
     * EFECTO:      Reescribe el archivo de salida omitiendo palabras reservadas.
     * REQUIERE:    Inicializado.
     * MODIFICA:    Archivo de salida y archivo temporal.
     */
    void quitReserved();
    
    /*
     * EFECTO:      Reescribe el archivo de salida omitiendo los simbolos '(', ')', '{', '}', ',', ';' y '*'.
     * REQUIERE:    Inicializado.
     * MODIFICA:    Archivo de salida y archivo temporal.
     */
    void quitSymbols();
    
    /*
     * EFECTO:      Reescribe el archivo de salida omitiendo espacios mayores que 1.
     * REQUIERE:    Inicializado.
     * MODIFICA:    Archivo de salida y archivo temporal.
     */
    void quitSpaces();
    
    /*
     * EFECTO:      Retorna la linea siguiente del archivo de salida.
     * REQUIERE:    Inicializado.
     * MODIFICA:    -
     */
    char* readLn();
    
    /*
     * EFECTO:      Retorna la palabra siguiente del archivo de salida.
     * REQUIERE:    Inicializado.
     * MODIFICA:    -
     */
    string readWord();
    
    /*
     * EFECTO:      Setea el archivo de entrada.
     * REQUIERE:    Direccion valida.
     * MODIFICA:    fileInDir
     */
    void setFileInDir(string fileIn);
    
    /*
     * EFECTO:      Setea la direccion del archivo de salida.
     * REQUIERE:    Direccion valida.
     * MODIFICA:    fileOutDir
     */
    void setFileOutDir(string fileOut);
    
    /*
     * EFECTO:      Reseteamos el archivo temporal con base en archivo de entrada.
     * REQUIERE:    Inicializado.
     * MODIFICA:    Archivo temporal.
     */
    void resetStream();
    
    static int instanceCounter;     // Contador de instancias.
    
private:
    
    //****************************ATRIBUTOS*************************************
    string fileInDir;               // Direccion de archivo de entrada.
    
    string fileOutDir;              // Direccion de archivo de salida.
    
    string fileTempDir;             // Direccion de archivo temporal.
    
    fstream* fileIn;                // Archivo de entrada
    
    fstream* fileOut;               // Archivo de salida
    
    fstream* fileTemp;              // Archivo temporal
    
    char readBuffer[256];           // Buffer de lectura.
    
    /*
     * EFECTO:      Salva el archivo de salida en el archivo temporal.
     * REQUIERE:    Inicializado.
     * MODIFICA:    Archivo temporal.
     */
    void saveTemp();
};

#endif /* SINTETIZADORDETEXTO_H */
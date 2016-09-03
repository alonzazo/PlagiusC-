/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AnalizadorDePalabras.h
 * Author: Oscar Azofeifa
 *
 * Created on 18 de agosto de 2016, 08:07 PM
 */

#ifndef ANALIZADORDEPALABRAS_H
#define ANALIZADORDEPALABRAS_H

#include <list>
#include <string>
#include "SintetizadorDeTexto.h"
#include "TrieTree.h"

#include <iostream>
using namespace std;

class AnalizadorDePalabras {
public:
    //**************************CONSTRUCTORES***********************************
    
    
    AnalizadorDePalabras();
    
    AnalizadorDePalabras( string src1, string src2 );
    
    virtual ~AnalizadorDePalabras();
    
    //**************************OPERACIONES BASICA******************************
    /*
     * EFECTO:      Retorna una lista de hileras con los resultados de los analisis.
     * REQUIERE:    Archivos inicalizados.
     * MODIFICA:    similarityIndex
     */
    list< string > analize();
    
    /*
     * EFECTO:      Retorna el indice de similaridad total
     * REQUIERE:    Archivos inicializados.
     * MODIFICA:    similarityIndex
     */
    int getSimilarityIndex();
    
    /*
     * EFECTO:      Retorna el peso de un analisis en el analisis total.
     * REQUIERE:    -
     * MODIFICA:    -
     */
    int getWeight(int n);
    
    /*
     * EFECTO:      Modifica el peso del analisis n en el analisis total.
     * REQUIERE:    -
     * MODIFICA:    weights[]
     */
    void setWeight( int quantity, int n );

private:
    
    /*
     * EFECTO:      Retorna una lista con los comentarios similares entre los 
     *                  archivos.
     * REQUIERE:    -
     * MODIFICA:    -
     */
    list< string > commentsSimilarity();
    
    /*
     * EFECTO:      Retorna una lista con las lineas similares entre los 
     *                  archivos.
     * REQUIERE:    -
     * MODIFICA:    -
     */
    list< string > linesSimilarity();
    
    /*
     * EFECTO:      Retorna una lista con las palabras parciales similares 
     *                  entre los archivos.
     * REQUIERE:    -
     * MODIFICA:    -
     */
    list< string > partialSimilarity();
    
    /*
     * EFECTO:      Retorna una lista con las primeras palabras de lineas 
     *                  secuenciales que sean similares entre los archivos.
     * REQUIERE:    -
     * MODIFICA:    -
     */
    list< string > semanticSimilarity();
    
    /*
     * EFECTO:      Retorna una lista con los palabras similares entre los 
     *                  archivos.
     * REQUIERE:    -
     * MODIFICA:    -
     */
    list< string > wordsSimilarity();
    
    
    int weights[5];                             // Arreglo de pesos
    
    int similarityIndex;                        // Indice de similaridad total
    
    SintetizadorDeTexto* sintetizadores[2];     // Sintetizadores de texto
    
};

#endif /* ANALIZADORDEPALABRAS_H */


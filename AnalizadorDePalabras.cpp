/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AnalizadorDePalabras.cpp
 * Author: Oscar Azofeifa
 * 
 * Created on 18 de agosto de 2016, 08:07 PM
 */

#include "AnalizadorDePalabras.h"
#include "SintetizadorDeTexto.h"

AnalizadorDePalabras::AnalizadorDePalabras() {
    
    sintetizadores[0] = NULL;
    sintetizadores[1] = NULL;
    
}

AnalizadorDePalabras::AnalizadorDePalabras( string src1, string src2 ) {
    
    //Definimos los atributos de instancia
    sintetizadores[0] = new SintetizadorDeTexto(src1,"tmpOut1");
    sintetizadores[1] = new SintetizadorDeTexto(src2,"tmpOut2");
    
    weights[0] = 22;    // Similaridad de Palabras
    weights[1] = 12;    // Similaridad Parcial de Palabras
    weights[2] = 22;    // Similaridad de Lineas
    weights[3] = 22;    // Similaridad de Comentarios
    weights[4] = 22;    // Similaridad de Secuencia Semantica
    
}

AnalizadorDePalabras::~AnalizadorDePalabras() {
    delete sintetizadores[0];
    delete sintetizadores[1];
}

list< string > AnalizadorDePalabras::analize(){
    
    
    int totals[5];
    list< string > result;
    
    // Se realizan los analisis y los calculos de los conjuntos
    list< string > similarityList = wordsSimilarity();
    totals[0] = sintetizadores[0]->getWordsNumber();
    for (int i = 0; i < 2; i++) sintetizadores[i]->resetStream();
    
    list< string > partialList = partialSimilarity();
    totals[1] = sintetizadores[0]->getFilledLinesNumber();
    for (int i = 0; i < 2; i++) sintetizadores[i]->resetStream();
    
    list< string > linesList = linesSimilarity();
    totals[2] = sintetizadores[0]->getFilledLinesNumber();
    for (int i = 0; i < 2; i++) sintetizadores[i]->resetStream();
    
    list< string > commentsList = commentsSimilarity();
    totals[3] = sintetizadores[0]->getFilledLinesNumber();
    for (int i = 0; i < 2; i++) sintetizadores[i]->resetStream();
    
    list< string > semanticList = semanticSimilarity();
    totals[4] = sintetizadores[0]->getFilledLinesNumber();
    
    int totalWeights = weights[0] + weights[1] + weights[2] + weights[3] + weights[4];
    
    // Calculamos el indice de similaritdad
    similarityIndex = ( similarityList.size() * weights[0] * 100 ) / ( totalWeights * totals[0] )  + 
            ( partialList.size() * weights[1] * 100 ) / ( totalWeights * totals[1] )  +
            ( linesList.size() * weights[2] * 100 ) / ( totalWeights * totals[2] )  +
            ( commentsList.size() * weights[3] * 100) / ( totalWeights * totals[3] ) +
            ( semanticList.size() * weights[4] * 100) / ( totalWeights * totals[4] );
    
    //Agregamos el indice total a la salida
    result.push_back("Porcentaje de similaridad: " + std::to_string(similarityIndex));
    
    //Agregamos los indices independientes
    result.push_back("Indice de Similaridad de Palabras:\t\t" + to_string( similarityList.size() ) + "/" + to_string( totals[0] ) + "\tPonderacion: " + to_string( weights[0] ) );
    result.push_back("Indice de Similaridad Parcial de Palabras:\t" + to_string( partialList.size() ) + "/" + to_string( totals[1] ) + "\tPonderacion: " + to_string( weights[1] ) );
    result.push_back("Indice de Similaridad de Lineas:\t\t" + to_string( linesList.size() ) + "/" + to_string( totals[2] ) + "\tPonderacion: " + to_string( weights[2] ) );
    result.push_back("Indice de Similaridad de Comentarios:\t\t" + to_string( commentsList.size() ) + "/" + to_string( totals[3] ) + "\tPonderacion: " + to_string( weights[3] ) );
    result.push_back("Indice de Similaridad de Secuencia Semantica:\t" + to_string( semanticList.size()) + "/" + to_string( totals[4] ) + "\tPonderacion: " + to_string( weights[4] ) );
    
    //Agregamos los detalles de cada analisis
    result.push_back("\nDetalles de Similaridad de Palabras:");
    for (list< string >::iterator i = similarityList.begin(); i != similarityList.end(); i++) result.push_back(*i);
    
    result.push_back("\nDetalles de Similaridad Parcial de Palabras:");
    for (list< string >::iterator i = partialList.begin(); i != partialList.end(); i++) result.push_back(*i);
    
    result.push_back("\nDetalles de Similaridad de Lineas:");
    for (list< string >::iterator i = linesList.begin(); i != linesList.end(); i++) result.push_back(*i);
    
    result.push_back("\nDetalles de Similaridad de Comentarios:");
    for (list< string >::iterator i = commentsList.begin(); i != commentsList.end(); i++) result.push_back(*i);
    
    result.push_back("\nDetalles de Similaridad de Secuencia semantica:");
    for (list< string >::iterator i = semanticList.begin(); i != semanticList.end(); i++) result.push_back(*i);
    
    return result;
}
    
int AnalizadorDePalabras::getSimilarityIndex(){
    
    if (similarityIndex == -1)
        analize();
    
    return similarityIndex;
    
}
    
int AnalizadorDePalabras::getWeight( int n ){
    return weights[n];
}
    
void AnalizadorDePalabras::setWeight(int quantity, int n ){
    weights[n] = quantity;
}

list< string > AnalizadorDePalabras::commentsSimilarity(){
    
    string actualLine;
    TrieTree commentsLines;
    list< string > similarComments;
    
    //Dejamos solo los comentarios
    for (int i = 0; i < 2; i++) sintetizadores[i]->justComments();
    
    //Quitamos los espacios en blanco
    for (int i = 0; i < 2; i++) sintetizadores[i]->quitSpaces();
    
    //Hacemos minusculas
    for (int i = 0; i < 2; i++) sintetizadores[i]->makeLowercase();
    
    //Agregamos todos los comentarios del segundo archivo a una estructura facil
    //  de manejar
    for (actualLine = sintetizadores[1]->readLn(); !sintetizadores[1]->eof(); actualLine = sintetizadores[1]->readLn())
        if (actualLine != "" && actualLine != " ")
            commentsLines.insert(actualLine);
    
    sintetizadores[1]->setCursorBegin();
    
    //Buscamos cuales lines del archivo 1 estan en el 2.
    for (actualLine = sintetizadores[0]->readLn(); !sintetizadores[0]->eof(); actualLine = sintetizadores[0]->readLn()) 
        if (commentsLines.search(actualLine)) similarComments.push_back(actualLine);
    sintetizadores[0]->setCursorBegin();
    
    return similarComments;
}
    
list< string > AnalizadorDePalabras::linesSimilarity(){//Se le podria poner un contador de linea]
    
    string actualLine;
    TrieTree baseLines;
    list< string > similarLines;
    
    //Hacemos minusculas
    for (int i = 0; i < 2; i++) sintetizadores[i]->makeLowercase();
    
    //Quitamos los comentarios
    for (int i = 0; i < 2; i++) sintetizadores[i]->quitComments();
    
    //Quitamos los simbolos
    for (int i = 0; i < 2; i++) sintetizadores[i]->quitSymbols();
    
    //Quitamos todas la palabras reservadas
    for (int i = 0; i < 2; i++) sintetizadores[i]->quitReserved();
    
    //Quitamos los espacios en blanco
    for (int i = 0; i < 2; i++) sintetizadores[i]->quitSpaces();
    
    //Agregamos todas la lineas del segundo archivo a una estructura mas facil
    //  de manejar.
    for (actualLine = sintetizadores[1]->readLn(); !sintetizadores[1]->eof(); actualLine = sintetizadores[1]->readLn())
        if (actualLine != "" && actualLine != " " && actualLine != "\n" && actualLine != "\t")
            baseLines.insert(actualLine);
    sintetizadores[1]->setCursorBegin();
    
    //Buscamos cuales lines del archivo 1 estan en el 2.
    for (actualLine = sintetizadores[0]->readLn(); !sintetizadores[0]->eof(); actualLine = sintetizadores[0]->readLn()) 
        if (baseLines.search(actualLine)) similarLines.push_back(actualLine);
    sintetizadores[0]->setCursorBegin();
    
    return similarLines;
}
    
list< string > AnalizadorDePalabras::partialSimilarity(){//Se le podria agregar la funcionalidad de determinar en que linea lo encontro
    
    list< string > similarWords; //Contenedor para las palabras que se encontraran
    string wordA = "";
    //Hacemos minusculas
    for (int i = 0; i < 2; i++) sintetizadores[i]->makeLowercase();
    
    //Quitamos los comentarios
    for (int i = 0; i < 2; i++) sintetizadores[i]->quitComments();
    
    //Quitamos los simbolos
    for (int i = 0; i < 2; i++) sintetizadores[i]->quitSymbols();
    
    //Quitamos todas la palabras reservadas
    for (int i = 0; i < 2; i++) sintetizadores[i]->quitReserved();
    
    int numWordsA = sintetizadores[0]->getWordsNumber();
    int numWordsB = sintetizadores[1]->getWordsNumber();
    
    for (int i = 0; i < numWordsA; i++){
        
        wordA = sintetizadores[0]->readWord();
        int lenA = wordA.length();
        
        string wordB = "";
        for (int j = 0; j < numWordsB; j++){
            
            wordB = sintetizadores[1]->readWord(); 
            int lenB = wordB.length();
            
            //Comparamos solo si tiene mas de un caracter, si es mas corta que wordB.
            if ( lenA > 1 && lenA < lenB ){
                
                bool flg = false;
                int begin = 0;
                int limit = lenB - lenA;
                
                //Comparamos todos los substrings de wordB tamano lenA con wordA.
                while ( begin <= limit ){
                    if (!wordB.substr(begin, lenA).compare(wordA)){
                        similarWords.push_back(wordA.append(" @ ").append(wordB));
                    }
                    begin++;
                }
            }
            
        }
        sintetizadores[1]->setCursorBegin();
    }
    return similarWords;
    
}
    
list< string > AnalizadorDePalabras::semanticSimilarity(){
    
    bool flg = false;
    list< string > similarWords;
    string firstWordLnA = "";
    string firstWordLnB = "";
    
    // Quitamos los comentarios
    for (int i = 0; i < 2; i++) sintetizadores[i]->quitComments();
    
    // Quitamos espacios en blanco
    for (int i = 0; i < 2; i++) sintetizadores[i]->quitSpaces();
   
    // Quitamos los simbolos
    for (int i = 0; i < 2; i++) sintetizadores[i]->quitSymbols();
    
    while (!sintetizadores[0]->eof() && !sintetizadores[1]->eof() && !flg){
        
        firstWordLnA = sintetizadores[0]->readWord();
        sintetizadores[0]->readLn();
        
        firstWordLnB = sintetizadores[1]->readWord();
        sintetizadores[1]->readLn();
        
        if (!firstWordLnA.compare(firstWordLnB)) 
            similarWords.push_back(firstWordLnA);
        else 
            flg = true;
        
    }
    
    return similarWords;
    
}
    
list< string > AnalizadorDePalabras::wordsSimilarity(){
    
    //Quitamos los simbolos
    for (int i = 0; i < 2; i++) sintetizadores[i]->quitSymbols();
    
    //Quitamos palabras reservadas
    for (int i = 0; i < 2; i++) sintetizadores[i]->quitReserved();
    
    //Hacemos lowercase todas las palabras para la comparacion.
    for (int i = 0; i < 2; i++) sintetizadores[i]->makeLowercase();
    
    list< string > similarWords;
    int numWords0 = sintetizadores[0]->getWordsNumber();
    int numWords1 = sintetizadores[1]->getWordsNumber();
    
    //Agregamos las palabras del archivo 2 a una estructura mas comoda. 
    TrieTree wordsFile1;
    for (int i = 0; i < numWords1; i++){
        wordsFile1.insert(sintetizadores[1]->readWord());
    }
    
    for (int i = 0; i < numWords0; i++){
        string word = sintetizadores[0]->readWord();
        if (wordsFile1.search(word)){
            similarWords.push_back(word);
        }
    }
    return similarWords;
}
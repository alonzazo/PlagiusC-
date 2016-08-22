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

using namespace std;

class AnalizadorDePalabras {
public:
    
    AnalizadorDePalabras();
    
    AnalizadorDePalabras(const AnalizadorDePalabras& orig);
    
    list< string > analize();
    
    int getSimilarityIndex();
    
    int* getWeights();
    
    void setWeights(int wWords, int wPartial, int wComments,int wLines, int wSemantic);
    
    virtual ~AnalizadorDePalabras();

private:
    
    list< string > commentsSimilarity();
    
    list< string > linesSimilarity();
    
    list< string > partialSimilarity();
    
    list< string > semanticSimilarity();
    
    list< string > wordsSimilarity();
    
};

#endif /* ANALIZADORDEPALABRAS_H */


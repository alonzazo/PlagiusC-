/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TrieTree.cpp
 * Author: oazofeifa
 * 
 * Created on 27 de agosto de 2016, 10:17 PM
 */

#include <list>

#include "TrieTree.h"

TrieTree::TrieTree() {
    header = NULL;
}

TrieTree::TrieTree(const char * word){
    insert(word);
}

TrieTree::TrieTree(const string word){
    insert(word);
}

TrieTree::~TrieTree() {
    TrieTree::deleteRecursive_aux(header);
}

void TrieTree::insert(const char * word){
    
    if (word == "") return;
    
    if (header == NULL ){
        
        header = new trieNode;
        header->c = word[0];
        
        header->leftChild = new trieNode;
        trieNode * finger = header->leftChild;
        int lenght = strlen(word);
        
        for (int i = 1; i < lenght; i++){
            finger->c = word[i];
            finger->leftChild = new trieNode;
            finger = finger->leftChild;
        }
        finger->c = 127;
        
    } 
    else {
        
        trieNode * finger = header;
        int lenght = strlen(word);
        
        for (int i = 0; i < lenght; i++){
            if (finger->c != 0){
                while (finger->rightBrother != NULL && finger->c != word[i]){
                    finger = finger->rightBrother; 
                }
                if (finger->c == word[i]){
                    finger = finger->leftChild;
                } 
                else {
                    finger->rightBrother = new trieNode;
                    finger = finger->rightBrother;
                    finger->c = word[i];
                    finger->leftChild = new trieNode;
                    finger = finger->leftChild;
                }
            } else {
                finger->c = word[i];
                finger->leftChild = new trieNode;
                finger = finger->leftChild;
            }
        }
        finger->c = 127;
    }
}

void TrieTree::insert(const string &word){
    
    if (word == "") return;
    
    if (header == NULL ){
        
        header = new trieNode;
        header->leftChild = NULL;
        header->rightBrother = NULL;
        header->c = word[0];
        
        header->leftChild = new trieNode;
        trieNode * finger = header->leftChild;
        int lenght = word.length();
        
        for (int i = 1; i < lenght; i++){
            finger->c = word[i];
            finger->leftChild = new trieNode;
            finger->rightBrother = NULL;
            finger = finger->leftChild;
        }
        finger->c = 127;
        finger->rightBrother = NULL;
        finger->leftChild = NULL;
    } 
    else {
        
        trieNode * finger = header;
        int lenght = word.length();
        
        for (int i = 0; i < lenght; i++){
            if (finger->c != 0){
                while (finger->rightBrother != NULL && finger->c != word[i]){
                    finger = finger->rightBrother; 
                }
                if (finger->c == word[i]){
                    finger = finger->leftChild;
                } 
                else {
                    finger->rightBrother = new trieNode;
                    finger = finger->rightBrother;
                    finger->rightBrother = NULL;
                    finger->c = word[i];
                    
                    finger->leftChild = new trieNode;
                    finger = finger->leftChild;
                    finger->leftChild = NULL;
                    finger->rightBrother = NULL;
                    finger->c = 0;
                }
            } else {
                finger->c = word[i];
                finger->leftChild = new trieNode;
                finger = finger->leftChild;
                finger->leftChild = NULL;
                finger->rightBrother = NULL;
                finger->c = 0;
            }
        }
        finger->c = 127;
    }
}

bool TrieTree::search(const char * word){
    if (header == NULL){
        return 0;
    }
    
    int i = 0;
    int lenght = strlen(word);
    trieNode * finger = header;
    char state = 1;                     //  There are three states: 
                                        //      0-No 1-Waiting 2-Yes
    
    while ( i < lenght && state == 1 ){
        while (finger != NULL && word[i] != finger->c){
            finger = finger->rightBrother;
        }
        if (finger == NULL){
            state == 0;
        }
        else {
            finger = finger->leftChild;
        }
        i++;
    }
    if (state != 0){
        while (finger != NULL && finger->c != 127){
            finger = finger->rightBrother;
        }
        if (finger != NULL){
            return true;
        }
    }
    return false;
}

bool TrieTree::search(const string &word){
    if (header == NULL){
        return 0;
    }
    
    int i = 0;
    int lenght = word.length();
    trieNode * finger = header;
    char state = 1;                     //  There are three states: 
                                        //      0-No 1-Waiting 2-Yes
    
    while ( i < lenght && state == 1 ){
        while (finger != NULL && word[i] != finger->c){
            finger = finger->rightBrother;
        }
        if (finger == NULL){
            state == 0;
        }
        else {
            finger = finger->leftChild;
        }
        i++;
    }
    if (state != 0){
        while (finger != NULL && finger->c != 127){
            finger = finger->rightBrother;
        }
        if (finger != NULL){
            return true;
        }
    }
    return false;
}

int TrieTree::erase(const char * word){
    if (header == NULL){
        return 0;
    }
    
    list< pair< trieNode *, trieNode * > > pointersLst;
    
    int i = 0;
    int lenght = strlen(word);
    trieNode * finger = header;
    trieNode * prevFinger = NULL;
    char state = 1;                     //  There are three states: 
                                        //      0-No 1-Waiting 2-Yes
    
    while ( i < lenght && state == 1 ){
        while (finger != NULL && word[i] != finger->c){
            prevFinger = finger;
            finger = finger->rightBrother;
        }
        if (finger == NULL){
            state == 0;
        }
        else {
            pair< trieNode *, trieNode * > pointers;
            pointers.first = finger;
            pointers.second = prevFinger;
      
            pointersLst.push_back(pointers);
            
            prevFinger = NULL;
            finger = finger->leftChild;
        }
        i++;
    }
    if (state != 0){
        while (finger != NULL && finger->c != 127){
            finger = finger->rightBrother;
        }
        if (finger != NULL){
            pair< trieNode *, trieNode * > pointers;
            pointers.first = finger;
            pointers.second = prevFinger;
      
            pointersLst.push_back(pointers);
            state = 2;
        }
    }
    
    // Se inicia el borrado de los elementos
    if (state == 2){
        
        list< pair< trieNode *, trieNode * > >::iterator i = pointersLst.end(), begin = pointersLst.begin();
        
        std::reverse_iterator< list< pair< trieNode *, trieNode * > >::iterator > rev_i(i);
        std::reverse_iterator< list< pair< trieNode *, trieNode * > >::iterator > rev_begin(begin);
        
        while ( rev_i != rev_begin  && rev_i->second == NULL && rev_i->first->rightBrother == NULL){
            rev_i->first->leftChild = NULL;
            delete rev_i->first;
            rev_i++;
        }
        if ( rev_i->second != NULL){
            rev_i->second->rightBrother = rev_i->first->rightBrother;
            delete rev_i->first;
        } else {
            trieNode * newChild = rev_i->first->rightBrother;
            delete rev_i->first;
            rev_i++;
            rev_i->first->leftChild = newChild;
        }
        
        
    }
    return 0;
}

int TrieTree::erase(const string word){
    if (header == NULL){
        return 0;
    }
    
    list< pair< trieNode *, trieNode * > > pointersLst;
    
    int i = 0;
    int lenght = word.length();
    trieNode * finger = header;
    trieNode * prevFinger = NULL;
    char state = 1;                     //  There are three states: 
                                        //      0-No 1-Waiting 2-Yes
    
    while ( i < lenght && state == 1 ){
        while (finger != NULL && word[i] != finger->c){
            prevFinger = finger;
            finger = finger->rightBrother;
        }
        if (finger == NULL){
            state == 0;
        }
        else {
            pair< trieNode *, trieNode * > pointers;
            pointers.first = finger;
            pointers.second = prevFinger;
      
            pointersLst.push_back(pointers);
            
            prevFinger = NULL;
            finger = finger->leftChild;
        }
        i++;
    }
    if (state != 0){
        while (finger != NULL && finger->c != 127){
            finger = finger->rightBrother;
        }
        if (finger != NULL){
            pair< trieNode *, trieNode * > pointers;
            pointers.first = finger;
            pointers.second = prevFinger;
      
            pointersLst.push_back(pointers);
            state = 2;
        }
    }
    
    // Se inicia el borrado de los elementos
    if (state == 2){
        
        list< pair< trieNode *, trieNode * > >::iterator i = pointersLst.end(), begin = pointersLst.begin();
        
        std::reverse_iterator< list< pair< trieNode *, trieNode * > >::iterator > rev_i(i);
        std::reverse_iterator< list< pair< trieNode *, trieNode * > >::iterator > rev_begin(begin);
        
        while ( rev_i != rev_begin  && rev_i->second == NULL && rev_i->first->rightBrother == NULL){
            rev_i->first->leftChild = NULL;
            delete rev_i->first;
            rev_i++;
        }
        if ( rev_i->second != NULL){
            rev_i->second->rightBrother = rev_i->first->rightBrother;
            delete rev_i->first;
        } else {
            trieNode * newChild = rev_i->first->rightBrother;
            delete rev_i->first;
            rev_i++;
            rev_i->first->leftChild = newChild;
        }
        
        
    }
    return 0;
}

void TrieTree::deleteRecursive_aux(trieNode * node){
    if (node->leftChild != NULL){
        deleteRecursive_aux(node->leftChild);
    }
    if (node->rightBrother != NULL){
        deleteRecursive_aux(node->rightBrother);
    }
    delete node;
}
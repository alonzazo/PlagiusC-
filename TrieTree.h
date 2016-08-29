/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TrieTree.h
 * Author: oazofeifa
 *
 * Created on 27 de agosto de 2016, 10:17 PM
 */

#ifndef TRIETREE_H
#define TRIETREE_H

#include <string.h>
#include <string>

using namespace std;

class TrieTree {
public:
    /*
     * *****************************CONSTRUCTORS********************************
     */
    TrieTree();
    TrieTree(const char * word);
    TrieTree(const string word);
    ~TrieTree();
    
    /*
     * *****************************BASIC OPERATORS***************************** 
     */
    
    /*
     * EFFECT: Insert a word to diccionary.
     * REQUIRE: Type of entrance char*.
     * MODIFY: Diccionary
    */
    void insert(const char * word);
    void insert(const string &word);
    
    /*
     * EFFECT: Returns 1 if the word is in diccionary, otherwise returns 0.
     * REQUIRE: Type of entrance char*, with printable chars.
     * MODIFY: -
    */
    bool search(const char * word);
    bool search(const string &word);
    
    /*
     * EFFECT: Delete a word of the diccionary, returns 1 if the try is correct 
     *          or 0 if not.
     * REQUIRE: Type of entrance char*, with printable chars.
     * MODIFY: Diccionary
    */
    int erase(const char * word);
    int erase(const string word);
    
private:
    
    struct trieNode {
        trieNode* rightBrother;
        trieNode* leftChild;
        char c;
    };
    
    trieNode* header;
    
    void deleteRecursive_aux(trieNode * node);
};

#endif /* TRIETREE_H */
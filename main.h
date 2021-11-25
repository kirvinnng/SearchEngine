//* this file contains the general structures, defines, includes  ฅʕ·ᴥ·　ʔฅ
#pragma once

#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

// UTF-8 characters
#define EXCLAMATION 173
#define QUESTION 168
#define A_ACCENT 160
#define E_ACCENT 130
#define I_ACCENT 161
#define O_ACCENT 162
#define U_ACCENT 163
#define COM 175 // '>>'
#define ENIE 164

// Keyboard keys
#define KEY_UP 72
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_LEFT 75

#define ESC 27
#define UP 24
#define DOWN 25
#define RIGHT 26

//* number of documents and words
typedef struct TreeInfo {

    int allDocument;     // Total number of documents
    int documentsID[10]; // Document IDs : [ 1 , 2 , 5 , 6 , 8 ]
    int words;           // Total number of words

} TreeInfo;

typedef struct Get {
    char word[50];
    int idDOC;
    int position;
} Get;

typedef struct Node {
    int idDOC;
    int position;
    struct Node *next;
} Node;

typedef struct Tree {
    char word[50];
    int length;
    Node *list;
    struct Tree *right;
    struct Tree *left;
} Tree;

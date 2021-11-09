//* this file contains the general structures, defines, includes  ฅʕ·ᴥ·　ʔฅ
#pragma once

#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef struct Get {
    char word[20];
    int idDOC;
    int position; // incrementa palabra por palabra, y no letra por letra
} Get;

typedef struct Node {
    int idDOC;
    int position;
    struct Node *next;
} Node;

typedef struct Tree {
    char word[20];
    int length; // representa la cantidad de nodos de la lista
    Node *list; // ordenada por idDOC, luego por pos
    struct Tree *right;
    struct Tree *left;
} Tree;

enum Orientations { UP, RIGHT, DOWN, LEFT };

// Keyboard keys
#define KEY_UP 72
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_LEFT 75

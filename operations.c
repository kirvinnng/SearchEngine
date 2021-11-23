#include "operations.h"
#include "algorithm.h"
#include "gui.h"
#include "main.h"
#include "read_file.h"

//* 1) Search for all occurrences of a term in a document (operation or).
void operation1(Tree *tree) {
    char word[500];
    int id1, id2;
    Tree *auxID1 = NULL, *auxID2 = NULL;

    printf(" Termino a buscar: ");
    fflush(stdin);
    scanf("%s", word);
    printf(" ID Documento Nro. 1: ");
    fflush(stdin);
    scanf("%d", &id1);
    printf(" OR\n");
    printf(" ID Documento Nro. 2: ");
    fflush(stdin);
    scanf("%d", &id2);
    auxID1 = findWordByDoc(tree, word, id1);
    auxID2 = findWordByDoc(tree, word, id2);
    if (auxID1 && auxID2) {
        printf("\nSe encontro el termino '%s' tanto en el documento Nro. %d como en el Nro. %d.\n", word, id1, id2);
        showTreeWithoutWord(auxID1);
        showTreeWithoutWord(auxID2);

    } else if (!auxID1 && !auxID2) {
        printf("No se encontro el termino '%s' ni en el documento Nro. %d ni en el Nro. %d.\n", word, id1, id2);
    } else {
        printf("Se encontro el termino '%s' en el documento Nro. %d, pero no en el documento Nro. %d.\n", word, (auxID1) ? id1 : id2,
               (!auxID1) ? id1 : id2);
        showTreeWithoutWord((auxID1) ? auxID1 : auxID2);
    }
}

//* 2) Search for all occurrences of a term in one document and another (and operation).
void operation2(Tree *tree){
    char word[500];
    int id1, id2;
    Tree *auxID1 = NULL, *auxID2 = NULL;

    printf(" Termino a buscar: ");
    fflush(stdin);
    scanf("%s", word);
    printf(" ID Documento Nro. 1: ");
    fflush(stdin);
    scanf("%d", &id1);
    printf("AND\n");
    printf(" ID Documento Nro. 2: ");
    fflush(stdin);
    scanf("%d", &id2);
    auxID1 = findWordByDoc(tree, word, id1);

    auxID2 = findWordByDoc(tree, word, id2);

    if (auxID1 && auxID2) {
        printf("\nSe encontro el termino '%s' tanto en el documento Nro. %d como en el Nro. %d.\n", word, id1, id2);
        showTreeWithoutWord(auxID1);
        showTreeWithoutWord(auxID2);

    } else {
        printf("No se encontro el termino '%s' en ambos documentos (Nro. %d y Nro. %d).\n",
               word, id1, id2);
    }
}

//* 3) Search for the occurrence of more than one term in the same document.
void operation3(Tree *tree){

    const int ESC = 27;
    char word[500];
    int id = 0;
    Tree *auxID1 = NULL;
    char choice;
   
    printf(" ID Documento : ");
    scanf("%d", &id);
    
    do { 
        printf(" Termino a buscar: ");
        fflush(stdin);
        scanf("%s", word);
        auxID1 = findWordByDoc(tree, word, id);

        if(auxID1){
            showTree(auxID1);
        }else{
            printf(" No se encontro el termino '%s' en el documento (Nro. %d).\n",word,id);
        }
        printf(" Pulse una tecla para realizar otra busqueda o ESC para salir\n");
        fflush(stdin);
        choice = getch();

    }while(choice != ESC);
}

//* 4) Search for a complete sentence (words must be contiguous in one of the documents).
void operation4(Tree *tree) {
    char phrase[500];
    int id;
    Tree *auxID = NULL;

    printf(" Ingrese una frase a buscar: ");
    fflush(stdin);
    gets(phrase);

    printf(" ID Documento: ");
    scanf("%d", &id);

    SearchResult result = searchPhraseOnTree(tree, phrase, id);

    if(!result.foundAllWords){
        printf(" No se encontraron todas las palabras de la frase '%s', ", phrase);
    } else {
        printf(" Se encontraron todas las palabras de la frase '%s'\n ", phrase);
        if(result.allWordsInOrder){
            printf(" y se encontraron en orden en el documento %d a partir de la posicion %d.\n", id, result.wordInitialPosition);
        } else {
            printf(" pero no se encontraron en orden.\n");
        }
    }
}

//* 5) Search for the most frequent word that appears in one of the documents.
void operation5(Tree *tree){
    // TODO: Hacer el scanf y esas cosas :)
    FrequentWord fw = frequentWordByDocumentID(tree, 1);
    printf("%s, %d", fw.word, fw.frequency);
} 

//* 6) Use the levenshtein distance in the input of a word and suggests similar words from a distance <= 3
void operation6(Tree *tree){


}
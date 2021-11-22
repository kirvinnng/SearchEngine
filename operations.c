#include "operations.h"
#include "algorithm.h"
#include "main.h"
#include "gui.h"

void operation1(Tree *tree){
    char word[30];
    int id1, id2;
    Tree *auxID1 = tree, *auxID2=tree;

    printf("Termino a buscar: ");
    fflush(stdin);
    gets(word);
    printf("ID Documento Nro. 1: ");
    scanf("%d", &id1);
    printf("OR\n");
    printf("ID Documento Nro. 2: ");
    scanf("%d", &id2);
    auxID1 = findWordByDoc(auxID1, word, id1);
    auxID2 = findWordByDoc(auxID2, word, id2);
    
    
    showTree(tree);

    if(auxID1 && auxID2){
        showTree(auxID1);
        showTree(auxID2);
    } else if(!auxID1 && !auxID2){
        printf("No se encontro el termino '%s' ni en el documento Nro. %d ni en el Nro. %d.\n", word, id1, id2);
    } else {
        printf("Se encontro el termino '%s' en el documento Nro. %d, pero no en el documento Nro. %d.\n", word, (auxID1) ? id1 : id2, (!auxID1) ? id1 : id2);
        showTree((auxID1) ? auxID1 : auxID2);
    }
}
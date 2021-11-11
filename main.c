#include "main.h"
#include "algorithm.h"
#include "file_function.h"
#include "gui.h"

int main() {

    Tree *tree = NULL;

    //* these functions are to read the files and pass them to the tree,
    //* then create the dictionary.
    // selectMenuOption();
    // readAllFiles(&tree);
    // showTree(tree);
    // FILE *buff = openFile();
    // createDictionary(tree, buff);
    // closeFile(buff);
    //*----------------------------------

    Tree *treeTwo = NULL;

    readDictionary(&treeTwo);
    // showTree(treeTwo);

    return 0;
}

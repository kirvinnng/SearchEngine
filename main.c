#include "main.h"
#include "algorithm.h"
#include "create_file.h"
#include "gui.h"
#include "operations.h"
#include "read_file.h"

int main(int argc, char **argv) {

    setWindow(150, 30, 150, 1000);

    Tree *tree = NULL;

    //* this function is to read the files and pass them to the tree
    readAllFiles(&tree);

    //* then create the dictionary.
    createFiles(tree);

    //* and read the dictionary
    Tree *treeDic = NULL;
    TreeInfo treeInfo = readDictionary(&treeDic);

    //* 'switch' with the user options
    userChoice(treeDic, treeInfo);

    //*------------------------------------------
    return 0;
}

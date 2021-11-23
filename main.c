#include "main.h"
#include "algorithm.h"
#include "create_file.h"
#include "gui.h"
#include "operations.h"
#include "read_file.h"

int main(int argc, char **argv) {

    Tree *tree = NULL;
    // selectMenuOption();

    setWindow(150, 35, 150, 1000);
    //* these functions are to read the files and pass them to the tree,
    //* then create the dictionary.
    readAllFiles(&tree);
    createBinary(tree);
    //*----------------------------------
    // system("cd document && dictionary.html");

    Tree *treeDic = NULL;
    TreeInfo treeInfo = readDictionary(&treeDic);
    // showTree(treeDic);

    //* 🤩 User operations 🤩
    // operation1(treeDic);
    // operation2(treeDic);
    // operation3(treeDic);
    // operation4(treeDic);
    operation5(treeDic, treeInfo);
    // Tree *foo = findWord(treeDic, "go");

    // showTree(foo);
    // showTree(treeDic);
    return 0;
}

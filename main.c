#include "main.h"
#include "algorithm.h"
#include "create_file.h"
#include "gui.h"
#include "read_file.h"

int main(int argc, char **argv) {

    Tree *tree = NULL;
    // selectMenuOption();

    //* these functions are to read the files and pass them to the tree,
    //* then create the dictionary.
    readAllFiles(&tree);
    // showTree(tree);
    // createTXT(tree);
    // createHTML(tree);
    // createBinary(tree);
    // createJSON(tree);
    //*----------------------------------
    system("pause");
    // system("cd document && dictionary.html");

    readDictionary(&tree);
    showTree(tree);

    return 0;
}

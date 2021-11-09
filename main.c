#include "main.h"
#include "algorithm.h"
#include "file_function.h"
#include "gui.h"

int main() {

    Tree *tree = NULL;

    readAllFiles(&tree);

    showTree(tree);

    return 0;
}

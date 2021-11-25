#include "create_file.h"
#include "algorithm.h"
#include "gui.h"
#include "main.h"
#include "read_file.h"

#define HTML 1
#define TXT 2
#define JSON 3

void createHTML(Tree *tree) {

    FILE *buff = openFile(".html", "w");
    createDictionary(tree, buff, ".html");
    closeFile(buff);
}

void createTXT(Tree *tree) {

    FILE *buff = openFile(".txt", "w");
    createDictionary(tree, buff, ".txt");
    closeFile(buff);
}

void createBinary(Tree *tree) {

    FILE *buff = openFile(".bin", "wb");
    createDictionary(tree, buff, ".bin");
    closeFile(buff);
}

int countWords;
void createJSON(Tree *tree) {

    countTreeNode(tree, &countWords);

    FILE *buff = openFile(".json", "w");
    fprintf(buff, "[\n");
    createDictionary(tree, buff, ".json");
    fprintf(buff, "\n]");
    closeFile(buff);
}

void createFiles(Tree *tree) {

    createBinary(tree);
    createTXT(tree);
    createJSON(tree);
}

//* Open file once to avoid reopening multiple times during recursion.
FILE *openFile(char *extensionFile, char *mode) {

    char dir[30];

    addExtension(dir, extensionFile);

    FILE *buff = fopen(dir, mode);

    if (buff) {

        return buff;
    }
    gotoxy(0, 0);
    printf(" ERROR OPENING '%s' \n ( FILE : %s - LINE : %d )\n", dir, __FILE__, __LINE__);
}

void closeFile(FILE *buff) {

    if (buff) {
        fclose(buff);
    }
}

//* Creates the file where the words are stored.
void createDictionary(Tree *tree, FILE *buff, char *extensionFile) {

    if (tree) {

        listToFile(tree->list, tree->word, buff, extensionFile, tree);
        createDictionary(tree->right, buff, extensionFile);
        createDictionary(tree->left, buff, extensionFile);
    }
}

//* Get flag (used to create the file and its parts) depending on file extension.
int getFlag(char *extensionFile) {
    int flag = 0;
    if (strcmpi(extensionFile, ".html") == 0) {
        flag = 1;
    } else if (strcmpi(extensionFile, ".txt") == 0) {
        flag = 2;
    } else if (strcmpi(extensionFile, ".json") == 0) {
        flag = 3;
    }

    //* return 0 if is ext binary
    return flag;
}

int count;
//* Insert the linked list & Tree data to specific files
void listToFile(Node *list, char *word, FILE *buff, char *extensionFile, Tree *tree) {

    int flag = getFlag(extensionFile);
    printFirstPart(flag, buff, word);
    Get info = {0};
    while (list) {

        info = fillStructField(word, list->position, list->idDOC);
        printMiddlePart(flag, buff, info, list);
        list = list->next;
    }

    printLastPart(flag, buff);
}

//* Create the header of the file, specifying the word and the count of tree nodes.
void printFirstPart(int extensionID, FILE *buff, char *word) {

    switch (extensionID) {
        case HTML:
            fprintf(buff, "<h2 style=\"font-family:Georgia; color:#FD4961\">WORD : %s </h>", word);
            fprintf(buff, "<h2 style=\"font-family:Monospace; padding:20px ; color:#9A60FF\">");
            break;
        case TXT:
            for (int i = 0; i < (15 - (strlen(word) / 2)); i++) {
                fprintf(buff, " ");
            }
            fprintf(buff, "%s\n\n", word);
            break;
        case JSON:
            fprintf(buff, "{\n    \"Word\": \"%s\",\n \"Info\": [", word);
            break;
    }
}

//* Create the body of the file, specifying the number where the word is allocated and its position.
void printMiddlePart(int extensionID, FILE *buff, Get info, Node *list) {
    switch (extensionID) {
        case HTML:
            fprintf(buff, "Document : %d     Position : %d<br>", info.idDOC, info.position);
            break;
        case TXT:
            fprintf(buff, " Document : %d     Position : %d \n", info.idDOC, info.position);
            break;
        case JSON:

            fprintf(buff, "\n{\n      \"Document\": \"%d\", ", info.idDOC);
            fprintf(buff, "\n      \"Position\": \"%d\"\n}%s", info.position, (list->next != NULL) ? "," : "");
            break;
        default:
            fwrite(&info, sizeof(Get), 1, buff);
            break;
    }
}

//* Create the footer of the file, just line breakers.
void printLastPart(int extensionID, FILE *buff) {

    switch (extensionID) {
        case HTML:
            fprintf(buff, "</h2>");
            break;
        case TXT:
            fprintf(buff, "\n --------------------------------- \n\n");
            break;
        case JSON:
            count++;
            fprintf(buff, "\n]\n}%s\n", (count == countWords) ? " " : ",");

            break;
    }
}

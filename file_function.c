#include "file_function.h"
#include "algorithm.h"
#include "gui.h"
#include "main.h"

//* Read all the files in the database
void readAllFiles(Tree **tree) {

    DIR *d;
    struct dirent *dir;

    int id = 0;
    d = opendir("database");
    if (d) {

        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {

                id++;

                readFile(dir->d_name, tree, id);
            }
        }

        closedir(d);
    }
}

//* Add the folder with "/" in the file name
void addFolder(char *file) {

    char directory[30];
    strcpy(directory, "database/");
    strcat(directory, file);

    printf(" Path : '%s' \n", directory);
    printf(" File : '%s' \n", file);

    strcpy(file, directory);
}

//* Open a file and pass the data to the tree
void readFile(char *fileName, Tree **tree, int fileID) {

    addFolder(fileName);

    FILE *buff = fopen(fileName, "rb");

    char *auxWord = (char *)calloc(sizeof(char), 20);
    verifyError(auxWord, __LINE__);
    char *word = (char *)calloc(sizeof(char), 20);
    verifyError(word, __LINE__);

    Get info = {0};
    char character;
    int position = 0;
    int i = 0;

    if (buff != NULL) {
        while (fread(&character, sizeof(char), 1, buff) > 0) {

            if (!verifyCharAlpha(character)) {

                //* if the next character is not charAlpha or Numeric
                if (i == 0) {

                    continue;
                }
                strncpy(word, auxWord, i + 1);

                word[i] = '\0';
                info = fillStructField(word, position, fileID);

                saveInfoIntoTree(tree, info);

                i = 0;
            } else {
                character = tolower(character);
                auxWord[i] = character;
                i++;
            }
            position++;
        }
        fclose(buff);
        free(word);
        free(auxWord);

    } else {
        printf(" ERROR OPENING '%s' \n ( FILE : %s - LINE : %d )\n", fileName, __FILE__, __LINE__);
    }
}

//* Insert the information in the tree & list
void saveInfoIntoTree(Tree **tree, Get info) {

    int valid = insertTree(tree, info);
}

Get fillStructField(char *word, int position, int fileID) {

    Get info;
    position -= strlen(word); //* start of the word

    // printf(" WORD : %s \n", word);

    strcpy(info.word, word);
    info.position = position;
    info.idDOC = fileID;

    return info;
}

//* Verify if it's a letter or a number
int verifyCharAlpha(char caracter) {

    return IsCharAlpha(caracter) || IsCharAlphaNumeric(caracter);
}

FILE *openFile() {

    FILE *buff = fopen(DICTIONARY, "wb");

    if (buff) {

        return buff;
    }
    printf(" ERROR OPENING '%s' \n ( FILE : %s - LINE : %d )\n", DICTIONARY, __FILE__, __LINE__);
}

void closeFile(FILE *buff) {
    if (buff) {
        fclose(buff);
    }
}

//* Creates the file where the words are stored.
void createDictionary(Tree *tree, FILE *buff) {

    if (tree) {

        listToFile(tree->list, tree->word, buff);
        createDictionary(tree->right, buff);
        createDictionary(tree->left, buff);
    }
}

void listToFile(Node *list, char *word, FILE *buff) {

    Get info = {0};
    while (list) {

        info = fillStructField(word, list->position, list->idDOC);

        fwrite(&info, sizeof(Get), 1, buff);

        list = list->next;
    }
}

void readDictionary(Tree **tree) {
    FILE *buffer = fopen(DICTIONARY, "rb");

    Get info;
    if (buffer) {
        while (fread(&info, sizeof(Get), 1, buffer) > 0) {

            saveInfoIntoTree(tree, info);
        }
        fclose(buffer);
    } else {
        printf(" ERROR OPENING '%s' \n ( FILE : %s - LINE : %d )\n", DICTIONARY, __FILE__, __LINE__);
    }
}

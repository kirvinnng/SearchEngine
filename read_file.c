#include "read_file.h"
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

                info.position -= strlen(word); //* start of the word
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

    insertTree(tree, info);
}

//* Define the fields of the structure 'Get'
Get fillStructField(char *word, int position, int fileID) {

    Get info;

    strcpy(info.word, word);
    info.position = position;
    info.idDOC = fileID;

    return info;
}

//* Verify if it's a letter or a number
int verifyCharAlpha(char caracter) {
    return IsCharAlpha(caracter) || IsCharAlphaNumeric(caracter);
}

//* Read the file dictionary.bin & save into tree
void readDictionary(Tree **tree) {

    char dir[30];
    addExtension(dir, ".bin");

    FILE *buffer = fopen(dir, "rb");

    Get info;
    if (buffer) {
        while (fread(&info, sizeof(Get), 1, buffer) > 0) {

            if (!ifWordExists(*tree, info)) { //* If not exists

                saveInfoIntoTree(tree, info);
            }
        }
        fclose(buffer);
    } else {
        printf(" ERROR OPENING '%s' \n ( FILE : %s - LINE : %d )\n", DICTIONARY, __FILE__, __LINE__);
    }
}

//* Verify that a specific word is not repeated
int ifWordExists(Tree *tree, Get info) {

    int exits = 1;
    if (tree) {
        if (strcmpi(tree->word, info.word) == 0 && tree->list->idDOC == info.idDOC && tree->list->position == info.position) {

            return 0;
        } else {

            exits = ifWordExists(tree->left, info);
            if (exits == 0) {
                exits = ifWordExists(tree->right, info);
            }
        }
    }
    return exits;
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

//* Add the file extension for the files
void addExtension(char *dir, char *extension) {

    size_t length = strlen(DICTIONARY) + strlen(extension) + 1; //* '+1' is for the '/0'

    strcpy(dir, DICTIONARY);
    strcat(dir, extension);
}

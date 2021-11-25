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
    verifyError(auxWord, __FILE__, __LINE__);
    char *word = (char *)calloc(sizeof(char), 20);
    verifyError(word, __FILE__, __LINE__);

    Get info = {0};
    char character;
    int position = 0;
    int i = 0;

    if (buff != NULL) {
        while (fread(&character, sizeof(char), 1, buff) > 0) {

            if (!isValidCharacter(character)) {

                //* if the next character is not charAlpha or Numeric, it would jump to the next iteration
                if (i == 0) {
                    continue;
                }
                position++;

                strncpy(word, auxWord, i + 1);

                word[i] = '\0';
                info = fillStructField(word, position, fileID);

                // info.position -= strlen(word); //* start of the word
                saveInfoIntoTree(tree, info);

                i = 0;
            } else {
                character = tolower(character);
                auxWord[i] = character;
                i++;
            }
            // position++; for character positions
        }
        fclose(buff);
        free(word);
        free(auxWord);
    } else {
        gotoxy(0, 0);
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
int isValidCharacter(char character) {

    return IsCharAlpha(character) || IsCharAlphaNumeric(character);
}

//* Read the file dictionary.bin & save the data collected in the tree
TreeInfo readDictionary(Tree **tree) {

    char dir[30];
    addExtension(dir, ".bin");
    FILE *buffer = fopen(dir, "rb");

    TreeInfo treeInfo = {0};
    Get info;
    int size = 0;

    if (buffer) {
        while (fread(&info, sizeof(Get), 1, buffer) > 0) {

            saveInfoIntoTree(tree, info);

            if (documentExists(treeInfo.documentsID, info.idDOC, size)) {

                treeInfo.documentsID[size] = info.idDOC; //* save the id documents
                size++;

                treeInfo.allDocument = size;
            }
            treeInfo.words++;
        }
        fclose(buffer);
    } else {
        gotoxy(0, 0);
        printf(" ERROR OPENING '%s' \n ( FILE : %s - LINE : %d )\n", DICTIONARY, __FILE__, __LINE__);
    }

    return treeInfo;
}

//* Check if the document exists
int documentExists(int documentID[], int newID, int size) {

    for (int i = 0; i < size; i++) {

        if (documentID[i] == newID) { //* if exist return 0 , else 1
            return 0;
        }
    }
    return 1;
}

//* Add the folder with "/" in the file name
void addFolder(char *file) {

    char directory[30];
    strcpy(directory, "database/");
    strcat(directory, file);

    strcpy(file, directory);
}

//* Add the file extension for the files
void addExtension(char *dir, char *extension) {

    size_t length = strlen(DICTIONARY) + strlen(extension) + 1; //* '+1' is for the '/0'

    strcpy(dir, DICTIONARY);
    strcat(dir, extension);
}

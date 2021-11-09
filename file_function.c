#include "file_function.h"
#include "algorithm.h"
#include "gui.h"
#include "main.h"

void readAllFiles(Tree **tree) {

    DIR *d;
    char file[50];
    struct dirent *dir;

    Get info;
    int id = 0;
    d = opendir("database");
    if (d) {

        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {

                id++;

                readFile(info, dir->d_name, tree, id);
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

void readFile(Get info, char *fileName, Tree **tree, int fileID) {

    addFolder(fileName);

    FILE *buff = fopen(fileName, "rb");

    char *auxWord = (char *)calloc(sizeof(char), 20);
    verifyError(auxWord, __LINE__);
    char *word = (char *)calloc(sizeof(char), 20);
    verifyError(word, __LINE__);

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
                fillStructField(&info, word, position, fileID);

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
    }
}

void saveInfoIntoTree(Tree **tree, Get info) {

    int valid = insertTree(tree, info);
}

void fillStructField(Get *info, char *word, int position, int fileID) {

    position -= strlen(word); //* start of the word

    // printf(" WORD : %s \n", word);

    strcpy((*info).word, word);
    (*info).position = position;
    (*info).idDOC = fileID;
}

//* Verify if it's a letter or a number
int verifyCharAlpha(char caracter) {

    return IsCharAlpha(caracter) || IsCharAlphaNumeric(caracter);
}
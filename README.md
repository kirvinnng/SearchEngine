
# Search Engine  <img align="center" alt="Fer-C" height="40" width="50" src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg">

**Final project of the second four-month period UTN**

## _Contributors_

* Kevin Reyna
* Matias Aceval 
* Lisandro Bidegain


## Compile

### To compile, we add the following line to `settings.json` in Visual Studio Code
```json
"cd $dir && gcc *.c -o $fileNameWithoutExt.exe && $dir$fileNameWithoutExt.exe"
```

## Basic Explanation of the Files
[```algorithm.c```](https://github.com/kirvinnng/SearchEngine/blob/main/algorithm.c)
**Internal program logic using trees and LinkedList + levenshtein algorithm**

```c
// Obtain a position in the list
int getListPositionAtIndex(Node *list, int pos);

// Search for a word by document
// ( return a tree with no child nodes )
Tree *findWordByDoc(Tree *tree, char *word, int idDoc);

// Search for a specific document
// Returns a new list if the document ID is found, otherwise returns NULL
Node *matchIdDoc(Node *list, int idDoc);

// Separate the list by different ids
// Returns a new list if the document ID is found, otherwise returns NULL
Node *splitList(Node *list, int idDoc);

// Search for a phrase in the tree
// return a "SearchResult structure" with the data obtained.

SearchResult searchPhraseOnTree(Tree *tree, char *phrase, int id);

// Search for the most frequent word in a document by id
// Returns a "FrequentWord structure" with the data recollected
FrequentWord frequentWordByDocumentID(Tree *tree, int idDOC);

// Searches for the word similar to the word passed by parameter
WordSimilarity _didYouMean(Tree *tree, char *word);

```

[```create_file.c```](https://github.com/kirvinnng/SearchEngine/blob/main/create_file.c)
**Creation of the dictionary in different extensions** 
```c
void createJSON(Tree *tree);
void createHTML(Tree *tree);
void createTXT(Tree *tree);
void createBinary(Tree *tree);
void createFiles(Tree *tree);

// Create the file where the words are stored
void createDictionary(Tree *tree, FILE *buff, char *extensionFile);

// Insert linked list and tree data into specific files
void listToFile(Node *list, char *word, FILE *buff, char *extensionFile, Tree *tree);
```

[```read_file.c```](https://github.com/kirvinnng/SearchEngine/blob/main/read_file.c)
**Processing of database files + dictionary reading** 
```c
// Reads all database files
void readAllFiles(Tree **tree);

// Open a file and passes the data to the tree
void readFile(char *fileName, Tree **tree, int fileID);

// Insert the information in the tree and in the list
void saveInfoIntoTree(Tree **tree, Get info);

// Add the folder with "/" in the filename
void addFolder(char *file);

// Add the file extension
void addExtension(char *dir, char *extension);

// Read the dictionary.bin file and saves the obtained data in the tree
TreeInfo readDictionary(Tree **tree);
```

[```operations.c```](https://github.com/kirvinnng/SearchEngine/blob/main/operations.c)
**Interactive functions with user operations** 
```c
void operation1(Tree *tree, TreeInfo treeInfo);
void operation2(Tree *tree, TreeInfo treeInfo);
void operation3(Tree *tree, TreeInfo treeInfo);
void operation4(Tree *tree, TreeInfo treeInfo);
void operation5(Tree *tree, TreeInfo treeInfo);
void openHTML(Tree *tree);
```
[```gui.c```](https://github.com/kirvinnng/SearchEngine/blob/main/gui.c)
**User interface functions + Other utilities** 
```c
int didYouMean(Tree *tree, char *word);
int userChoice(Tree *tree, TreeInfo treeInfo);
int selectMenuOption();
void keyMovement(const int _x, const int _y);
```


<br /><br />

# Motor De Busqueda <img align="center" alt="Fer-C" height="40" width="50" src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg">

**Trabajo Final del segundo cuatrimestre de Programacion UTN**

## _Contribuidores_

* Kevin Reyna
* Matias Aceval 
* Lisandro Bidegain


## Compilacion

### Para compilar, agregamos la siguiente línea a `settings.json` de VSCode.
```json
"cd $dir && gcc *.c -o $fileNameWithoutExt.exe && $dir$fileNameWithoutExt.exe"
```

## Explicacion General de los Archivos 
[```algorithm.c```](https://github.com/kirvinnng/SearchEngine/blob/main/algorithm.c)
**Internal program logic using trees and LinkedList + levenshtein algorithm**

```c
// Obtener una posición en la lista
int getListPositionAtIndex(Node *list, int pos);

// Buscar una palabra por documento
// ( devuelve un árbol sin nodos hijos )
Tree *findWordByDoc(Tree *tree, char *word, int idDoc);

// Buscar un documento específico
// Devuelve una nueva lista si se encuentra el ID del documento, en caso contrario devuelve NULL
Node *matchIdDoc(Node *list, int idDoc);

// Separa la lista por diferentes ids
// Devuelve una nueva lista si se encuentra el ID del documento, en caso contrario devuelve NULL
Node *splitList(Node *list, int idDoc);

// Buscar una frase en el árbol
// devuelve una "estructura SearchResult" con los datos obtenidos
SearchResult searchPhraseOnTree(Tree *tree, char *phrase, int id);

// Buscar la palabra más frecuente en un documento por id
// Devuelve una "estructura FrequentWord" con los datos obtenidos
FrequentWord frequentWordByDocumentID(Tree *tree, int idDOC);

//Busca la palabra similar a la palabra pasada por parametro
WordSimilarity _didYouMean(Tree *tree, char *word);

```

[```create_file.c```](https://github.com/kirvinnng/SearchEngine/blob/main/create_file.c)
**Creation of the dictionary in different extensions** 
```c
void createJSON(Tree *tree);
void createHTML(Tree *tree);
void createTXT(Tree *tree);
void createBinary(Tree *tree);
void createFiles(Tree *tree);

// Crea el archivo donde se almacenan las palabras
void createDictionary(Tree *tree, FILE *buff, char *extensionFile);

// Insertar los datos de la lista enlazada y del árbol en archivos específicos
void listToFile(Node *list, char *word, FILE *buff, char *extensionFile, Tree *tree);
```

[```read_file.c```](https://github.com/kirvinnng/SearchEngine/blob/main/read_file.c)
**Processing of database files + dictionary reading** 
```c
// Lee todos los archivos de la base de datos
void readAllFiles(Tree **tree);

// Abre un archivo y pasa los datos al árbol
void readFile(char *fileName, Tree **tree, int fileID);

// Inserta la información en el árbol y en la lista
void saveInfoIntoTree(Tree **tree, Get info);

// Añade la carpeta con "/" en el nombre del archivo
void addFolder(char *file);

// Añade la extensión de los archivos
void addExtension(char *dir, char *extension);

// Lee el archivo dictionary.bin y guarda los datos obtenidos en el árbol
TreeInfo readDictionary(Tree **tree);
```

[```operations.c```](https://github.com/kirvinnng/SearchEngine/blob/main/operations.c)
**Interactive functions with user operations** 
```c
void operation1(Tree *tree, TreeInfo treeInfo);
void operation2(Tree *tree, TreeInfo treeInfo);
void operation3(Tree *tree, TreeInfo treeInfo);
void operation4(Tree *tree, TreeInfo treeInfo);
void operation5(Tree *tree, TreeInfo treeInfo);
void openHTML(Tree *tree);
```
[```gui.c```](https://github.com/kirvinnng/SearchEngine/blob/main/gui.c)
**User interface functions + Other utilities** 
```c
int didYouMean(Tree *tree, char *word);
int userChoice(Tree *tree, TreeInfo treeInfo);
int selectMenuOption();
void keyMovement(const int _x, const int _y);
```

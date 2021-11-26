
# Motor De Busqueda

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
```algorithm.c```
**Logica interna del programa con el uso de arboles y listas + Algoritmo de levenshtein** 

```create_file.c```
**Creacion del diccionario en distintas extensiones** 

```read_file.c```
**Procesamiento de los archivos en la base de datos + la lectura del diccionario** 

```operations.c```
**Funciones interactivas con las operaciones del usuario** 

```gui.c```
**Funciones de la interfaz del usuario + Otras utilidades** 


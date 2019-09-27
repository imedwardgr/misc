# Simulador de Maquina de Turing

Durante mi segundo semestre en ESCOM-IPN, en la materia de "Teoría Computacional", desarrollé un simulador de maquina de turing con el objetivo de poder aprender de forma dinámica los objetivos del curso.

## Funcionamiento

El programa fue programado en C++11, por E. Gómez. 
El programa funciona únicamente para windows debido a que usa la librería <windows.h> para poder reubicar el cursor dentro de la consola. Si alguien gusta portarlo a linux, lo agradeceré mucho :)
 
Para ejecutar el programa es necesario ejecutar el siguiente comando:
```bash
g++ -o mt mt.cpp -std=c++11 && mt.exe < sumaBinaria.csv
```
Donde "sumaBinaria.csv" puede ser reemplazado con alguno de los otros archivos en este repositorio.

## Archivo de Entrada

La entrada es un archivo de descripción de las operaciones que hará la maquina de Turing, por lo que elegí archivos CSV debido a que son editables en excel, sin embargo la sintaxis para la creación de un nuevo archivo hay que seguir ciertos lineamientos en la sintaxis para asegurarnos que funcionará correctamente.

Por ejemplo, en este archivo CSV

```csv
*,0,1,X,B,Z
f
z,(a:0:D),(a:1:D),(a:X:D),(z:B:D),(a:Z:D)
a,(a:0:D),(a:1:D),-,(b:Z:I),-
b,(b:0:I),(c:X:D),(b:X:I),(e:B:D),-
c,(c:0:D),(c:1:D),(c:X:D),(d:1:I),(c:Z:D)
d,-,(d:1:I),-,-,(b:Z:I)
e,(e:B:D),(e:1:D),(e:B:D),(f:B:D),(e:B:D)
f,,,,,
,,,,,
01101101

```
#### Analizemos la primera fila

```csv
*,0,1,X,B,Z
```
La primera fila corresponde al alfabeto que será ocupado para la MT, los cuales pueden ser caracteres ASCII con excepción del '(', ')', ',' y '-', pero es recomendable utilizar dígitos o alfabeto inglés en mayúsculas.

#### Segunda fila

```csv
f
```
La segunda fila corresponde al estado de aceptación, siendo este estado el único en el cual la cadena será aceptada.

#### Filas de Descripción

```csv
z,(a:0:D),(a:1:D),(a:X:D),(z:B:D),(a:Z:D)
```
Las filas de aceptación, comienzan con un estado, el cual indica que todas las operaciones a su derecha sólo podrán ejecutarse si se encuentra en ese estado la maquina de Turing. 
Cada acción esta representada por (PE:CC:DC), donde:
PE = Estado al que cambiará la maquina de usar dicha acción.
CC = Caracter que buscará leer para usar dicha acción.
DC = Dirección a la cual se moverá la Maquina de Turing, este valor puede ser I para Izquierda o D para Derecha
También puede ocuparse el símbolo "-" para indicar que dicho estado es nulo.

#### Estado de Aceptación

```csv
f,,,,,
```
La lectura de las filas de descripción termina cuando se llega a una fila que contenga el estado de aceptación como primer caracter.

#### Fila de División

```csv
,,,,,
```
Una fila de comas debe ser incluida con el fin de separar la descripción de la maquina de Turing de su cadena de entrada.


#### Cadena a Evaluar

```csv
01101101
```
La ultima fila del archivo CSV debe de ser una sola cadena que contenga la prueba sobre la cual se evaluará la Maquina de Turing.

## Licencia

Autorizo la reproducción y modificación del código fuente siempre y cuando en su distribución se mantenga el mensaje de autoría de la presente maquina. 
Espero de todo corazón que este programa no sea entregado como proyecto final con el objetivo de cumplir con el programa de estudios, ya que el verdadero aprendizaje vendría de usar este código únicamente como guía para que cada persona pueda construir su propia versión de una Maquina de Turing.
Si tienes alguna duda sobre el funcionamiento de esta maquina, o te gustaría contribuir a la misma mediante la optimización del código, o portandola a sistemas GNU. Agradeceré que me contacten vía mail a egomezr1300@alumno.ipn.mx

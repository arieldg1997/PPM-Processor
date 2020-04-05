## PPM Processor 
## Trabajo Final de Seminario de Lenguajes opción C
## Ariel Dapia Graziani


### Parámetros:

* `-i entrada.ppm`: archivo origen. Opción requerida
* `-o salida.ppm`: archivo salida. Opción requerida
* `-n`: calcula el negativo
* `-r`: rota a 90 grados
* `-h`: espejo horizontal
* `-v`: espejo vertical
* `-b NUM`: desenfoque con radio NUM mayor a cero.
* `-?`: ayuda del programa
---------------------------------------------------------------------------------------------------------------
* `-s`: filtro de colores saturados
* `-d`: imagen en blanco y negro
* `-f`: intento de modo retrato, forma un circulo en el centro de la imagen y lo que esta afuera lo desenfoca, cuanto mas lejos esta del circulo mayor es el desenfoque
* `-p NUM`: pixela la imagen con un pixel NUM*NUM. NUM tiene que ser mayor a cero.
* `-g`: imagen en escala de grises
* `-l NUM `: cambia el brillo de la imagen, si NUM es positivo el brillo aumenta y si NUM es negativo la imagen se oscurece. Los valores de NUM permitidos son de -254 a 254
* `-k RGB`: quita los colores que se especifiquen como argumento siendo r o R rojo, g o G verde y b o B azul. Se pueden usar varios colores como argumento.

### Return values:

	0: Program ended as expected.
	1: Called ‘?’ for help.
	2: Missing -o parameter.
	3: -i must be the first parameter.
	4: No parameters detected.
	5: Error opening the input file.
	6: Error opening the output file.
	7: Wrong argument type.
	8: Parameter not recognized.

### Se compila con:
```
$ gcc -o ppm-processor *c -Wall -lm
```	
### Sentencia de ejemplo:
```
$ ./ppm-processor -i samples/couple.ppm  -o samples/output.ppm -r -p 4 -g
```
Lo que hace la sentencia es rotar la imagen 90°, pixelarla con un  pixel de 4x4, y por último transformarla en escala de grises.


#ifndef LIBS
#define LIBS
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"
#include "ppm-operations.h"
#include <getopt.h>
#include <math.h>
#endif

int errno;
FILE *f, * op;
t_ppm p_op;
char output_filename[1024];

//Function that administrates arguments and parameters 
int options_handling(int argc,char*argv[]){

    if (argc==1) error(4,0,"The program require -i and -o parameters with their respective aguments\n");

    //Checking if -? is the first argument 
    if (strcmp(argv[1],"-?")==0) {
                printf("Este programa es un gestor de imágenes en formato [PPM de tipo P6]\nFunciones:\n\t*`-i entrada.ppm`: archivo origen\n\t*`-o salida.ppm`: archivo salida\n\t*`-n`: calcula el negativo\n\t*`-r`: rota a 90 grados\n\t*`-h`: espejo horizontal\n\t*`-v`: espejo vertical\n\t* `-b NUM`: desenfoque con radio NUM\n\t* `-?`: ayuda del programa\n\t*`-s`: filtro de colores saturados\n\t*`-d`: imagen en blanco y negro\n\t*`-f`: intento de modo retrato, forma un circulo en el centro de la imagen y lo que esta afuera lo desenfoca, cuanto mas lejos esta del circulo mayor es el desenfoque\n\t*`-p NUM`: pixela la imagen con un pixel NUM*NUM\n\t*`-g`: imagen en escala de grises\n\t*`-l NUM `: cambia el brillo de la imagen, si NUM es positivo el brillo aumenta y si NUM es negativo la imagen se oscurece. Los valores de NUM permitidos son de -254 a 254\n\t*`-k RGB`: quita los colores que se especifiquen como argumento siendo r o R rojo, g o G verde y b o B azul. Se pueden usar varios colores como argumento.\n");
                exit(1);
        }
    
    //Checking if -o is missing
    int valid=1;
    for(int i=1;i<argc;i++) if (strcmp(argv[i],"-o")==0) valid=0;
    if (valid) error(2,0,"-o is an obligatory parameter\n");
    
    //Checking if -i is the first argument
    if(strcmp(argv[1],"-i")){
        error(3, 0, "-i must be the first parameter\n");
    }

    //Declaring and setting local variables 
    int opt;
    unsigned long r;
    int level;
    int colors_to_remove[3]; //RGB
    char * ptr;
    
    while((opt=getopt(argc,argv,"i:o:nrgvsp:fdhcb:l:?k:"))!=-1){
        switch(opt){
            case 'i':
                if ((f = fopen(optarg, "rb")) == NULL) error(5,errno, "Error opening file %s\n", argv[1]);
                p_op = ppm_from_file(f);
                break;
            case 'o':
                strcpy(output_filename,optarg);
                if ((op = fopen(output_filename, "wb")) == NULL) error(6,errno, "Error opening file %s\n", output_filename);
                break;
            case 'n': 
                p_op = ppm_operation_negative(p_op);     
                break;
            case 'r':
                p_op = ppm_operation_rotate90(p_op);     
                break;
            case 'h': 
                p_op = ppm_operation_flip_horizontal(p_op);     
                break;
            case 'v':
                p_op = ppm_operation_flip_vertical(p_op);     
                break;
            case 'b':
                for (int i=0;i<strlen(optarg);i++) if (! ((optarg[i]>='0') && (optarg[i]<='9'))  ) error(7,errno,"Argument must be a number greater than zero\n");
                r = strtoul(optarg, &ptr, 10);
                p_op = ppm_operation_blur(p_op , r);
                break;
            case '?':
                printf("Este programa es un gestor de imágenes en formato [PPM de tipo P6]\nFunciones:\n\t*`-i entrada.ppm`: archivo origen\n\t*`-o salida.ppm`: archivo salida\n\t*`-n`: calcula el negativo\n\t*`-r`: rota a 90 grados\n\t*`-h`: espejo horizontal\n\t*`-v`: espejo vertical\n\t* `-b NUM`: desenfoque con radio NUM\n\t* `-?`: ayuda del programa\n\t*`-s`: filtro de colores saturados\n\t*`-d`: imagen en blanco y negro\n\t*`-f`: intento de modo retrato, forma un circulo en el centro de la imagen y lo que esta afuera lo desenfoca, cuanto mas lejos esta del circulo mayor es el desenfoque\n\t*`-p NUM`: pixela la imagen con un pixel NUM*NUM\n\t*`-g`: imagen en escala de grises\n\t*`-l NUM `: cambia el brillo de la imagen, si NUM es positivo el brillo aumenta y si NUM es negativo la imagen se oscurece. Los valores de NUM permitidos son de -254 a 254\n\t*`-k RGB`: quita los colores que se especifiquen como argumento siendo r o R rojo, g o G verde y b o B azul. Se pueden usar varios colores como argumento.\n");
                break;
            case 's':
                p_op = ppm_operation_saturate(p_op);
                break;
            case 'd':
                p_op = ppm_operation_binarie(p_op);
                break;
            case 'f':
                p_op=ppm_operation_portait(p_op);
                break;
            case 'p':
                for (int i=0;i<strlen(optarg);i++) if (! ((optarg[i]>='0') && (optarg[i]<='9'))  ) error(7,errno,"Argument must be a number greater than zero\n");
                r = strtoul(optarg, &ptr, 10);
                if (r==0) error(7,0,"Argument must be greater that zero\n");
                p_op=ppm_operation_pixelate(p_op,r);
                break;
            case 'g':
                p_op=ppm_operation_greyscale(p_op);
                break;
            case 'l':
                for (int i=0;i<strlen(optarg);i++) if ( ! ( (optarg[i]>='0') && (optarg[i]<='9') ) ) if ( ! (i==0 && (optarg[0]=='-' || optarg[0]=='+')) ) error(7,errno,"Argument must be a number\n");
                level = atoi(optarg);
                if (level>255 || level<-255) error(7,0,"The number must be between -255 and 255\n");
                p_op = ppm_operation_brightness(p_op , level);
                break;
            case 'k':
                for (int i=0; i<strlen(optarg); i++) {
                    switch(optarg[i]){
                        case 'r':
                        case 'R':
                            colors_to_remove[0]++;
                            break;
                        case 'g':
                        case 'G':
                            colors_to_remove[1]++;
                            break;
                        case 'b':
                        case 'B':
                            colors_to_remove[2]++;
                            break;
                        default:
                            error(7,0,"%s character not recognized, rRgGbB only admited",optarg);
                            break;
                    }
                }
                p_op = ppm_operation_removecolors(p_op,colors_to_remove);
                break;
            default:    
                error(8, 0, "Operation not recognized\n");
                break;
        }
    }
    
    return(EXIT_SUCCESS);
}

int max(int a,int b){
  return (a>b)?a:b;
}

int min(int a,int b){
  return(a<b)?a:b;
}

void color_saturate(t_ppm_pixel*p){
  p->red=((p->red-128)<0)?0:255;
  p->green=((p->green-128)<0)?0:255;
  p->blue=((p->blue-128)<0)?0:255;
}

short int check_overflow(unsigned char c, int sum){
  sum+=c;
  if (sum>255) return 255;
  if (sum<0) return 0;
  return sum;
}

void ppm_modify_brightness(t_ppm_pixel *p, int level){
  p->red=check_overflow(p->red,level);
  p->green=check_overflow(p->green,level);
  p->blue=check_overflow(p->blue,level);
}

void ppm_invert_colours(t_ppm_pixel *p){
  p->red=255-p->red;
  p->green=255-p->green;
  p->blue=255-p->blue;
}

void set_black(int * r,int * g,int * b){
  *r=0;
  *g=0;
  *b=0;
}

void rgb_div_number(int*r,int*g,int*b,int number){
  *r/=number;
  *b/=number;
  *g/=number;
}

void assign_rgb_to_pixel(int r,int g,int b,t_ppm_pixel*p){
  p->red=r;
  p->green=g;
  p->blue=b;
}

void rgb_sum_pixel(int*r,int*g,int*b,t_ppm_pixel p){
  *r+=p.red;
  *b+=p.blue;
  *g+=p.green;
}

void pixel_to_const(t_ppm_pixel*p, int c){
  p->red=c;
  p->green=c;
  p->blue=c;
}
#ifndef LIBS
#define LIBS
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"
#include "aux_operations.h"
#include "ppm-operations.h"
#include <getopt.h>
#include <math.h>
#endif


t_ppm ppm_operation_rotate90(t_ppm p){
  unsigned int row,col; 
  t_ppm new = ppm_create(p.width, p.height, p.depth);
  for(row=0; row < p.width; row++) for(col=0; col < p.height ; col++){
    new.pixels[row][col] = p.pixels[p.height-col-1][row];
  }
  return new;
}

t_ppm ppm_operation_flip_horizontal(t_ppm p){
  unsigned int row,col; 
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    new.pixels[row][col] = p.pixels[row][p.width-col-1];
  }
  return new;
}

t_ppm ppm_operation_flip_vertical(t_ppm p){
  unsigned int row,col; 
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    new.pixels[row][col] = p.pixels[p.height-row-1][col];
  }
  return new;
}

t_ppm ppm_operation_blur(t_ppm p, unsigned long r){
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  int row,col,xi,xj,yi,yj,red,green,blue,dim,ratio;
  t_ppm_pixel total; 
  ratio=(int)r;
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    xi=max(row-ratio,0);
    xj=max(col-ratio,0);
    yi=min(row+ratio,p.height-1);
    yj=min(col+ratio,p.width-1);
    set_black(&red,&green,&blue);
    dim=(yi-xi)*(yj-xj);
    for(int i=xi; i<yi;i++) for(int j=xj; j<yj;j++) {
      rgb_sum_pixel(&red,&green,&blue,p.pixels[i][j]);
    }
    if (dim!=0) {
      rgb_div_number(&red,&green,&blue,dim);
      assign_rgb_to_pixel(red,green,blue,&total);
    }else{total=p.pixels[row][col];}
    new.pixels[row][col] = total;
  }
  return new;
}

t_ppm ppm_operation_pixelate(t_ppm p,unsigned long r){
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  int row,col,red,green,blue;
  t_ppm_pixel total; 
  for(row=0; row < p.height; row+=r) for(col=0; col < p.width ; col+=r){
    set_black(&red,&green,&blue);
    for(int i=row; i<min((row+r),p.height);i++) for(int j=col; j<min((col+r),p.width);j++) {
      rgb_sum_pixel(&red,&green,&blue,p.pixels[i][j]);
    }
    rgb_div_number(&red,&green,&blue,(int)r*r);
    assign_rgb_to_pixel(red,green,blue,&total);
    for(int i=row; i<min((row+r),p.height);i++) for(int j=col; j<min((col+r),p.width);j++) {
      new.pixels[i][j] = total;
    }
  }
  return new;
}

t_ppm ppm_operation_saturate(t_ppm p){
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  unsigned int row,col;
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    new.pixels[row][col]=p.pixels[row][col];
    color_saturate(&new.pixels[row][col]);
  }
  return new;
}

t_ppm ppm_operation_greyscale(t_ppm p){
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  unsigned int row,col,aux;
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    aux=p.pixels[row][col].red+p.pixels[row][col].blue+p.pixels[row][col].green;
    if (aux/3>255) aux=255; else aux/=3;
    pixel_to_const(&new.pixels[row][col],aux);
  }
  return new;
}

t_ppm ppm_operation_brightness(t_ppm p,int level){
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  unsigned int row,col;
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    new.pixels[row][col]=p.pixels[row][col];
    ppm_modify_brightness(&new.pixels[row][col],level);
  }
  return new;
}

t_ppm ppm_operation_removecolors(t_ppm p,int* level){
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  unsigned int row,col;
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    new.pixels[row][col]=p.pixels[row][col];
    if (level[0]!=0) new.pixels[row][col].red=0;
    if (level[1]!=0) new.pixels[row][col].green=0;
    if (level[2]!=0) new.pixels[row][col].blue=0;
  }
  return new;
}

//Black and white operation
t_ppm ppm_operation_binarie(t_ppm p){
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  unsigned int row,col;
  int total; 
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    total=p.pixels[row][col].red+p.pixels[row][col].green+p.pixels[row][col].blue;
    if ((total/3)<(128)){
      pixel_to_const(&new.pixels[row][col], 0);
    }else{
      pixel_to_const(&new.pixels[row][col], 255);
    }
  }
  return new;
}

t_ppm ppm_operation_negative(t_ppm p){
  unsigned int row,col; 
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    new.pixels[row][col] = p.pixels[row][col];
    ppm_invert_colours(&new.pixels[row][col]);
  }
  return new;
}

t_ppm ppm_operation_portait(t_ppm p){
  unsigned int row,col; 
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  double r,x,y,ratio,dist;
  int red,green,blue;
  int xi,xj,yi,yj,dim;
  x=p.height/2;
  y=p.width/2;
  r=pow(min(p.width,p.height)/2,2);
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    new.pixels[row][col] = p.pixels[row][col];
    dist=pow((x-row),2)+ pow((y-col),2);
    if ( dist > r ) {
      ratio=(dist-r)/(10000);
      xi=max(row-ratio,0);
      xj=max(col-ratio,0);
      yi=min(row+ratio,p.height-1);
      yj=min(col+ratio,p.width-1);
      set_black(&red,&green,&blue);
      dim=(yi-xi)*(yj-xj);
      for(int i=xi; i<yi;i++) for(int j=xj; j<yj;j++) {
        rgb_sum_pixel(&red,&green,&blue,p.pixels[i][j]);
      }
      if (dim!=0) {
        rgb_div_number(&red,&green,&blue,dim);
        assign_rgb_to_pixel(red,green,blue,&new.pixels[row][col]);
      }
    }
  }
  return new;
}



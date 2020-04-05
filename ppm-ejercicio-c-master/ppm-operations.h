#ifndef __PPM_OPERATIONS_H
#define __PPM_OPERATIONS_H

t_ppm ppm_operation_rotate90(t_ppm );
t_ppm ppm_operation_flip_horizontal(t_ppm );
t_ppm ppm_operation_flip_vertical(t_ppm );
t_ppm ppm_operation_negative(t_ppm );
t_ppm ppm_operation_blur(t_ppm , unsigned long);
void ppm_divide_colours(t_ppm_pixel *p, unsigned int cant);
void ppm_sum_colours(t_ppm_pixel *p,t_ppm_pixel *p_sum);
void ppm_initialize_pixel(t_ppm_pixel *p);
t_ppm ppm_operation_saturate(t_ppm );
t_ppm ppm_operation_binarie(t_ppm );
t_ppm ppm_operation_portait(t_ppm p);
t_ppm ppm_operation_pixelate(t_ppm p, unsigned long r);
t_ppm ppm_operation_greyscale(t_ppm p);
t_ppm ppm_operation_brightness(t_ppm p, int level);
t_ppm ppm_operation_removecolors(t_ppm p,int* level);

#endif


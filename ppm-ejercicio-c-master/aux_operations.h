int options_handling(int argc,char*argv[]);
int max(int a,int b);
int min(int a,int b);
void color_saturate(t_ppm_pixel*p);
short int check_overflow(unsigned char c, int sum);
void ppm_modify_brightness(t_ppm_pixel *p, int level);
void ppm_invert_colours(t_ppm_pixel *p);
void set_black(int * r,int * g,int * b);
void rgb_div_number(int*r,int*g,int*b,int number);
void assign_rgb_to_pixel(int r,int g,int b,t_ppm_pixel*p);
void rgb_sum_pixel(int*r,int*g,int*b,t_ppm_pixel p);
void pixel_to_const(t_ppm_pixel*p, int c);
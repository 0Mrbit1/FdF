#include "../include/fdf.h"


int main()
{
    void *mlx_ptr; 

    void *win_ptr;

    void *img_ptr ; 

    mlx_ptr =  mlx_init(); 
    win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "FDF");

   img_ptr = mlx_new_image(mlx_ptr,500,500);

  mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 500, 500);
  mlx_loop(mlx_ptr);

    
}
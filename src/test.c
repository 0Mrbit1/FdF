#include "../include/fdf.h"

void draw_pixel(void *img_ptr, int bits_per_pixel, int size_line, int x, int y, int color)
{
    // Calculate the index of the pixel (x, y) in the image data
    int index = (y * size_line) + (x * (bits_per_pixel / 8));

    // Set the pixel color at the calculated index
    char *img_data = (char *)img_ptr;

    // Extracting color components without bitwise operators
    int red = color / 65536;           // Extract red component
    int green = (color % 65536) / 256; // Extract green component
    int blue = color % 256;            // Extract blue component

    // Assign color components to the image data with consideration for endianness
    if (bits_per_pixel == 24) {
        // For 24 bits per pixel (3 bytes per pixel), assuming RGB format
        img_data[index] = blue;        // Blue component
        img_data[index + 1] = green;   // Green component
        img_data[index + 2] = red;     // Red component
    } else {
        // For other bits per pixel formats, adjust the assignment accordingly
        // You may need to consider different image formats and endianness here
        // This example assumes little-endian ordering
        img_data[index] = red;         // Red component
        img_data[index + 1] = green;   // Green component
        img_data[index + 2] = blue;    // Blue component
    }
}

int main()
{
    void *mlx_ptr = mlx_init();
    void *win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "Pixel Drawing");
    void *img_ptr = mlx_new_image(mlx_ptr, 1000, 1000);

    // Get image information
    int bits_per_pixel;
    int size_line;
    int endian;

    // Draw a pixel at position (500, 500) with color white (0xFFFFFF)
    draw_pixel(img_data, bits_per_pixel, size_line, 500, 500, 0xFFFFFF);

    // Display the image in the window
    mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);

    mlx_loop(mlx_ptr);

    return 0;
}



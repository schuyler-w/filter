#include "helpers.h"
#include <math.h>
 
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i) // for rows
    {
        for (int j = 0; j < width; ++j) // for columns
        {
            int mean = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = mean; // assigns each RGB value in the image with the average
            image[i][j].rgbtGreen = mean;
            image[i][j].rgbtRed = mean;
        }
    }
    return;
}
 
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int sepiaRed = round(((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue)));
            int sepiaGreen = round(((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue)));
            int sepiaBlue = round(((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue)));
 
            if (sepiaRed < 256)
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }
            if (sepiaGreen < 256)
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            if (sepiaBlue < 256)
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }
    return;
}
 
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
 
    RGBTRIPLE tempArr[height][width]; // temp array for swapping
 
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width / 2; ++j)
        {
            tempArr[i][j] = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tempArr[i][j];
        }
    }
    return;
}
 
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempArr[height][width];
 
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            float redSum = 0;
            float blueSum = 0;
            float greenSum = 0;
            float divisor = 0;
 
            for (int row = -1; row <= 1; ++row) // iterates rows -1 to +1 around the specified pixel
            {
                for (int col = -1; col <= 1; ++col) // iterates columns -1 to +1 around the specified pixel
                {
                    if (i + row < 0 || i + row > height - 1) // checks if the pixel is in bounds
                    {
                        continue;
                    }
 
                    if (j + col < 0 || j + col > width - 1)
                    {
                        continue;
                    }
 
                    redSum += image[i + row][j + col].rgbtRed;
                    blueSum += image[i + row][j + col].rgbtBlue;
                    greenSum += image[i + row][j + col].rgbtGreen;
                    divisor++; // counts how many pixels are collated for averaging
 
                }
            }
 
            tempArr[i][j].rgbtRed = round(redSum / divisor);
            tempArr[i][j].rgbtBlue = round(blueSum / divisor);
            tempArr[i][j].rgbtGreen = round(greenSum / divisor);
 
        }
    }
 
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            image[i][j].rgbtRed = tempArr[i][j].rgbtRed;
            image[i][j].rgbtBlue = tempArr[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tempArr[i][j].rgbtGreen;
        }
    }
 
    return;
}
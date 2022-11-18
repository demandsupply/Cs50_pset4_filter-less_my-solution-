#include <math.h>
#include "helpers.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Create a function to cap > 255 values
int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    } 
    return RGB;
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(0.393*image[i][j].rgbtRed + 0.769*image[i][j].rgbtGreen + 0.189*image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349*image[i][j].rgbtRed + 0.686*image[i][j].rgbtGreen + 0.168*image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272*image[i][j].rgbtRed + 0.534*image[i][j].rgbtGreen + 0.131*image[i][j].rgbtBlue);

            // Cap the sepia values that exceed 255 to 255. Can use the function "limit" for more efficiency
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width-j-1];
            image[i][width-j-1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    // Create a copy of "image" array to preserve the original one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Calculate the value of the pixel averaging the sum of adjacent pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumBlue = 0;
            int sumGreen = 0;
            int sumRed = 0;
            float counter = 0.00;
            
            for (int k = i-1; k <= i+1; k++)
            {
                if (k != -1 && k < height)
                {
                    for (int l = j-1; l <= j+1; l++)
                    {
                        if (l != -1 && l < width)
                        {
                        sumRed = sumRed + copy[k][l].rgbtRed;
                        sumGreen = sumGreen + copy[k][l].rgbtGreen;
                        sumBlue = sumBlue + copy[k][l].rgbtBlue;
                        counter++;
                        }
                    }
                }
            }

            image[i][j].rgbtRed = round(sumRed/counter);
            image[i][j].rgbtGreen = round(sumGreen/counter);
            image[i][j].rgbtBlue = round(sumBlue/counter);
        }
    }
    return;
}

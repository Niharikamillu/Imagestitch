#include <iostream>
#include "Raw_File.h"
#include <fstream>

unsigned short* stitchimage(unsigned short* topImage, unsigned short* bottomImage, int width, int height)
{
    unsigned short* stitchimage = new unsigned short[width * height];


    for (int i = 0; i < width * height / 2; i++)
    {
        stitchimage[i] = topImage[i];
    }

    for (int i = width * height / 2; i < width * height; i++)
    {

        stitchimage[i] = bottomImage[i - width * height / 2 * width * height];

    }

    return stitchimage;
}
unsigned short* CropImage(unsigned short* Image, int nStartX, int nEndX, int nStartY, int nEndY)
{
    unsigned short* pOutputImage = new unsigned short[1024 * 1024];
    memset(pOutputImage, 0, sizeof(unsigned short) * 1024 * 1024);
    for (int y = nStartY; y < nEndY; y++)
    {
        for (int x = nStartX; x < nEndX; x++)
        {
            pOutputImage[x + y * 1024] = Image[x + y * 1024];
        }
    }
    return pOutputImage;
}


int main() {
    int width = 1024;
    int height = 1024;


    {
        Raw_File* rf = new Raw_File(1024, 1024);
        rf->Write(CropImage(rf->Read("image1.raw"), 0, 1024, 0, 512), "img Top.raw");
        rf->Write(CropImage(rf->Read("image1.raw"), 0, 1024, 512, 1024), "img Bottom.raw");
        unsigned short* image1(rf->Read("C:\\Niharika\\imagestitching\\Imageprocessing\\img Top.raw"));
        unsigned short* image2(rf->Read("C:\\Niharika\\imagestitching\\Imageprocessing\\img Bottom.raw"));
        rf->Write(stitchimage(image1, image2, 1024, 1024), ("C:\\Niharika\\imagestitching\\Imageprocessing\\fullimage.raw"));

    }

    return 0;
}

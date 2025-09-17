#include "Raw_File.h"
#include<fstream>


unsigned short** Raw_File::Read(const char* pFilePath, int* count)
{
    FILE* rfile = fopen(pFilePath, "r");
    fseek(rfile, 0, SEEK_END);
    std::size_t  nNumOfPixels = ftell(rfile) / sizeof(unsigned short);
    fseek(rfile, 0, SEEK_SET);
    std::size_t  frameDimension = m_Height * m_Width;
    unsigned short* imageData = new unsigned short[nNumOfPixels];

    fread(imageData, sizeof(unsigned short), nNumOfPixels, rfile);
    unsigned short** pFrameArray = new unsigned short* [(std::size_t)(nNumOfPixels / frameDimension)];
    for (int m = 0; m < nNumOfPixels; m += frameDimension)
    {
        unsigned short* frameData = new unsigned short[frameDimension];
        for (int i = m; i < m + frameDimension; i++)
        {
            frameData[i - m] = (unsigned short)imageData[i];
        }
        pFrameArray[(*count)++] = frameData;
    }
    fclose(rfile);
    return pFrameArray;
}

unsigned short* Raw_File::Read(const char* pFilePath)
{
    FILE* rfile = fopen(pFilePath, "r");
    std::size_t  frameDimension = m_Height * m_Width;
    unsigned short* imageData = new unsigned short[frameDimension];
    fread(imageData, sizeof(unsigned short), frameDimension, rfile);
    fclose(rfile);
    return imageData;
}

void Raw_File::Write(unsigned short** pImageData, int count, const char* pFilePath)
{
    FILE* wfile = fopen(pFilePath, "wb");
    std::size_t nFrameDimension = m_Height * m_Width;
    for (int i = 0; i < count; i++)
    {
        fwrite(pImageData[i], sizeof(unsigned short), nFrameDimension, wfile);
    }
    fclose(wfile);
}

void Raw_File::Write(unsigned short* pImageData, const char* pFilePath)
{
    FILE* wfile = fopen(pFilePath, "wb");
    std::size_t nFrameDimension = m_Height * m_Width;
    fwrite(pImageData, sizeof(unsigned short), nFrameDimension, wfile);
    fclose(wfile);
}

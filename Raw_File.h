#pragma once


class Raw_File
{
private:
	int m_Width =0, m_Height=0;
public:
	Raw_File(int nWidth, int nHeight)
	{
		m_Width = nWidth;
		m_Height = nHeight;
	}
	unsigned short** Read(const char* pFilePath, int* count);
	unsigned short* Read(const char* pFilePath);
	void Write(unsigned short** pImageBuff, int count, const char* pFilePath);
	void Write(unsigned short* pImageData, const char* pFilePath);
};

    


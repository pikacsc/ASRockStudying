#pragma once
#include "value.h"

class CFileStream
{
public:
	CFileStream();
	~CFileStream();

private:
	FILE*	 m_pFile;
	int		 m_iFileSize;
	bool	 m_bValid;

public:
	bool OpenFile(const char* _pFileName,const char* _pMode);
	bool CloseFile();
	void Read(void* _pData, int _iSize);
	void ReadLine(void* _pData, int& _iSize);
	void Write(void* _pData, int _iSize);
	void WriteLine(void* _pData, int _iSize);
};


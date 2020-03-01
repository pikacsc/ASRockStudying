#include "CFileStream.h"

CFileStream::CFileStream()
	:m_pFile(nullptr), m_iFileSize(0), m_bValid(false)
{

}

CFileStream::~CFileStream()
{
	CloseFile();
}

bool CFileStream::OpenFile(const char* _pFileName,const char* _pMode)
{
	if (m_bValid)
	{
		return false;
	}

	fopen_s(&m_pFile, _pFileName, _pMode);

	if (!m_pFile)
	{
		return false;
	}

	//파일 커서를 가장뒤로 이동
	// fseek 함수는 파일커서를 원하는 위치로 이동 시키는 함수
	// SEEK_SET : 파일의 제일 처음
	// SEEK_CUR : 현재 가리키고 있는 파일 커서의 위치를 의미
	// SEEK_END : 파일의 가장 마지막을 의미
	// 2번째 인자인 offset 들어가는 바이트 수만큼 3번째 인자에서 지정한
	// 위치로부터 이동하게 됨
	fseek(m_pFile, 0, SEEK_END);

	// ftell : 파일 위치 지정자의 위치를 얻어오는 함수
	// fseek를 통해 파일 위치 지정자를 가장 마지막으로 이동 시킨뒤
	// ftell을 호출 하여 파일 위치 지정자의 위치를 얻어오면
	// 곧 파일 크기가 된다.
	m_iFileSize = ftell(m_pFile);

	//가장 앞으로 다시 이동
	fseek(m_pFile, 0, SEEK_SET);

	m_bValid = true;

	return true;
}

bool CFileStream::CloseFile()
{
	if (!m_bValid)
	{
		return false;
	}
	fclose(m_pFile);
	m_pFile = nullptr;
	m_iFileSize = 0;
	m_bValid = false;

	return true;
}

void CFileStream::Read(void* _pData, int _iSize)
{
	// 파일이 열려있지 않은 상태라면 불가능
	if (!m_bValid)
	{
		return;
	}

	fread(_pData, _iSize, 1, m_pFile);
}

void CFileStream::ReadLine(void* _pData, int& _iSize)
{
	if (!m_bValid)
	{
		return;
	}

	char cData;
	char* pChangeData = (char*)_pData;
	_iSize = 0;

	/* feof 함수는 파일 커서가 파일의 끝에 도달했는지를 체크한다
	파일의 끝에 도달하지 않았을 경우 0을 리턴하고 끝일경우
	0이 아닌 수를 리턴함
	*/

	while (feof(m_pFile) == 0) //feof() , 파일의 끝이면 true
	{
		fread(&cData, 1, 1, m_pFile);

		if (cData == '\n')
		{
			break;
		}

		pChangeData[_iSize] = cData;
		++_iSize;
	}
}

void CFileStream::Write(void* _pData, int _iSize)
{
	if (!m_bValid)
	{
		return;
	}

	fwrite(_pData, _iSize, 1, m_pFile);
}

void CFileStream::WriteLine(void* _pData, int _iSize)
{
	if (!m_bValid)
	{
		return;
	}

	char* pBuffer = new char[_iSize + 1];

	*(pBuffer + _iSize) = '\n';

	fwrite(pBuffer, _iSize + 1, 1, m_pFile);

	delete[] pBuffer;
}

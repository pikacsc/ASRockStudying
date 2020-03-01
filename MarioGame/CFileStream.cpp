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

	//���� Ŀ���� ����ڷ� �̵�
	// fseek �Լ��� ����Ŀ���� ���ϴ� ��ġ�� �̵� ��Ű�� �Լ�
	// SEEK_SET : ������ ���� ó��
	// SEEK_CUR : ���� ����Ű�� �ִ� ���� Ŀ���� ��ġ�� �ǹ�
	// SEEK_END : ������ ���� �������� �ǹ�
	// 2��° ������ offset ���� ����Ʈ ����ŭ 3��° ���ڿ��� ������
	// ��ġ�κ��� �̵��ϰ� ��
	fseek(m_pFile, 0, SEEK_END);

	// ftell : ���� ��ġ �������� ��ġ�� ������ �Լ�
	// fseek�� ���� ���� ��ġ �����ڸ� ���� ���������� �̵� ��Ų��
	// ftell�� ȣ�� �Ͽ� ���� ��ġ �������� ��ġ�� ������
	// �� ���� ũ�Ⱑ �ȴ�.
	m_iFileSize = ftell(m_pFile);

	//���� ������ �ٽ� �̵�
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
	// ������ �������� ���� ���¶�� �Ұ���
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

	/* feof �Լ��� ���� Ŀ���� ������ ���� �����ߴ����� üũ�Ѵ�
	������ ���� �������� �ʾ��� ��� 0�� �����ϰ� ���ϰ��
	0�� �ƴ� ���� ������
	*/

	while (feof(m_pFile) == 0) //feof() , ������ ���̸� true
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

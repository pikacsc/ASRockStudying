#include <iostream>

#define NAME_SIZE 32
#define STUDENT_MAX 3
#define FILE_NAME "Student.std"


typedef struct _tagStudent
{
	char	strName[NAME_SIZE];
	int		iNumber;
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
} STUDENT, *PSTUDENT;

int main()
{
	//File Write
	//STUDENT tStudent[STUDENT_MAX] = {};

	//for (int i = 0; i < STUDENT_MAX; ++i)
	//{
	//	std::cout << "Name : ";
	//	std::cin >> tStudent[i].strName;

	//	tStudent[i].iNumber = i + 1;

	//	std::cout << "Kor : ";
	//	std::cin >> tStudent[i].iKor;

	//	std::cout << "Eng : ";
	//	std::cin >> tStudent[i].iEng;

	//	std::cout << "Math : ";
	//	std::cin >> tStudent[i].iMath;

	//	tStudent[i].iTotal = tStudent[i].iKor + tStudent[i].iEng + tStudent[i].iMath;

	//	tStudent[i].fAvg = tStudent[i].iTotal / 3.f;

	//}

	//int iStudentCount = STUDENT_MAX;

	//FILE* pFile = nullptr;
	//int error = fopen_s(&pFile, "Student.std", "wb");

	//if (pFile == nullptr || error != 0)
	//{
	//	std::cout << "Error : can't write file" << std::endl;
	//	exit(1);
	//}

	//fwrite(&iStudentCount, sizeof(int), 1, pFile);

	//for (int i = 0; i < iStudentCount; ++i)
	//{
	//	//학생 구조체를 통으로 저장
	//	fwrite(&tStudent[i], sizeof(STUDENT), 1, pFile);
	//}

	//fclose(pFile);


	STUDENT tStudent[STUDENT_MAX] = { 0, };

	FILE* pFile = NULL;

	fopen_s(&pFile, FILE_NAME, "rb");

	if (!pFile)
	{
		std::cout << "Error : can't read file" << std::endl;
		exit(1);
	}
	int iStudentCount = 0;
	fread(&iStudentCount, sizeof(int), 1, pFile);

	for (int i = 0; i < iStudentCount; ++i)
	{
		fread(&tStudent[i], sizeof(STUDENT), 1, pFile);
	}


	//읽어온 학생 출력
	for (int i = 0; i < iStudentCount; ++i)
	{
		std::cout << "name : " << tStudent[i].strName << std::endl;
		std::cout << "student id : " << tStudent[i].iNumber << std::endl;
		std::cout << "kor : " << tStudent[i].iKor << std::endl;
		std::cout << "eng : " << tStudent[i].iEng << std::endl;
		std::cout << "math : " << tStudent[i].iMath << std::endl;
		std::cout << "Total : " << tStudent[i].iTotal << std::endl;
		std::cout << "Avg : " << tStudent[i].fAvg << std::endl;
		std::cout << std::endl;
	}


	fclose(pFile);
	return 0;
}
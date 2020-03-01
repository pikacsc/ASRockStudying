#include <iostream>

constexpr char FILE_NAME[] = "hot.txt";

int main()
{

	FILE* pFile = nullptr;

	// r : read, w : write, a : access 
	// t : text file,   b : binary file
	int error = fopen_s(&pFile, FILE_NAME, "wt");

	if (error != 0 || pFile == nullptr)
	{
		std::cout << "Error : can't write file" << std::endl;
		exit(1);
	}

	char pText[] = "abcd";

	fwrite(pText, 1, sizeof(pText), pFile);

	fclose(pFile);
	

	error = fopen_s(&pFile, FILE_NAME, "rt");

	if (error != 0 || pFile == nullptr)
	{
		std::cout << "Error : can't open file " << std::endl;
		exit(1);
	}

	char str[10] = { 0, };
	fread(str, 1, 4, pFile);

	std::cout << str << std::endl;


	fclose(pFile);

	return 0;
}
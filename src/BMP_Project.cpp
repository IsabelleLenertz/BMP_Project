//============================================================================
// Name        : BMPproject.cpp
// Author      : Isabelle Delmas
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream reader;
	int* pWidth = new int;

	reader.open("FF7.bmp", ios::binary);
	if( reader.is_open() == true )
	{
		cout << "The file was found." << endl;
	}
	else
	{
		cout << "The file could not be open." << endl;
		cout << "Emergency exit." << endl;
		return 0;
	}

	// Reads the width of the image
	reader.seekg(18);
	reader.read(reinterpret_cast<char*>(pWidth), 4);
	cout << "The width of the image is: " << *pWidth << endl;


	return 0;
}

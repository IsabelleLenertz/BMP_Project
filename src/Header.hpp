/*
 * Header.hpp
 *
 *  Created on: Oct 6, 2015
 *      Author: Isabelle Delmas
 */

#ifndef HEADER_HPP_
#define HEADER_HPP_
#include <fstream>
#include <iostream>

using namespace std;

class Header {
private:
	// Stream use to read the header of a bmp file in binary mode
	ifstream reader;

	// Data to be read from the file:
	int imageWidth;
	int imageHeight;
	int bytesPerPixel;
	int lengthOfHeader;

	// Data to be calculated from the previous ones.
	int beginningOfArray;
	bool valideAddress;
	int bytesPerLine;
	int paddingBytesAvailable;

public:
	Header();
	virtual ~Header();
};

#endif /* HEADER_HPP_ */

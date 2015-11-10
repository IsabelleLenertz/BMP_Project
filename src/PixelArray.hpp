/*
 * PixelArray.hpp
 *
 *  Created on: Nov 9, 2015
 *      Author: Isabelle
 */

#ifndef PIXELARRAY_HPP_
#define PIXELARRAY_HPP_

#include "Header.hpp"
#include <fstream>
#include <iostream>

using namespace std;

class PixelArray {

protected:
	Header *pFileHeader;
	bool valid;
	string fileAddress;


public:
	PixelArray();
	PixelArray(string newAddress);
	virtual ~PixelArray();

	bool setFileAddress(string newAddress);
};

#endif /* PIXELARRAY_HPP_ */

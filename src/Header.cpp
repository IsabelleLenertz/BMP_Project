/*
 * Header.cpp
 *
 *  Created on: Oct 6, 2015
 *      Author: Isabelle
 */

#include "Header.hpp"

Header::Header() {
	this->valide = false;

	// Sets all the attributes to 0
	this->imageWidth = 0;
	this->imageHeight = 0;
	this->bytesPerPixel = 0;
	this->lengthOfHeader = 0;
	this->beginningOfArray = 0;
	this->paddingAvailable = 0;
	this->paddingPerLine = 0;

}

Header::Header(string address){
	this->fileAddress = address;

	// reads the header of the BMP file and calculates the appropriate attributes
	if (this->setup() == true){
		// sets the validity flag to true if the file was open
		this->valide = true;
	}
	else{
		// sets the validity flag to false if the file was not open
		this->valide = false;

		// Sets all the attributes to 0
		this->imageWidth = 0;
		this->imageHeight = 0;
		this->bytesPerPixel = 0;
		this->lengthOfHeader = 0;
		this->beginningOfArray = 0;
		this->paddingAvailable = 0;
		this->paddingPerLine = 0;
	}
}

Header::~Header() {
	// TODO Auto-generated destructor stub
}

/*
 * Reads the header of a bmp file, and sets up all relating the attributes.
 * Returns true if the reader was able to open the bmp file.
 * Returns true if the reader could not open the bmp file.
 */
bool Header::setup(){
	// fstream.read needs a pointer, the data will be copied into the right attribute after reading
	int *pWidth = new int;
	int *pHeight = new int;
	int *pBitesPerPixel = new int;


	// FOR 24 BITES BMP ONLY
	this->beginningOfArray = 54; // for 24 bites BMP only
	this->lengthOfHeader = 53; // for 24 bites BMP only


	/*
	 * EXCTRATIING USEFUL DATA FROM THE HEADER FILE
	 */
	this->reader.open(fileAddress.c_str(), ios::binary);

	if( this->reader.is_open() == false ){
		// Does not set any data if the file could not be open
		// Changes the validity flag to false and exists the function
		this->valide = false;

		// deletes the pointer no longer in use.
		delete pWidth ;
		delete pHeight;
		delete pBitesPerPixel;

		// returns false to indicate that the file could be open
		return false;
	}

	// Reads the width of the image
	this->reader.seekg(18);
	this->reader.read(reinterpret_cast<char*>(pWidth), 4);
	// Sorts it in the appropriate attribute
	this->imageWidth = *pWidth;

	// Reads the height of the image
	reader.seekg(22);
	reader.read(reinterpret_cast<char*>(pHeight), 4);
	// Sorts it in the appropriate attribute
	this->imageHeight = *pHeight;

	// Reads the number of bites per pixel
	reader.seekg(28);
	reader.read(reinterpret_cast<char*>(pBitesPerPixel), 4);

	/*
	 * Calculating bytesPerLine and paddingBytesAvailable;
	 */

	// Calculate the number of Bytes per pixel
	this->bytesPerPixel = *pBitesPerPixel/8;

	// Calculate the number of padding bytes per line (a line has to end with a multiple of 4 bytes)
	if ((*pWidth)*bytesPerPixel%4 == 0){
		this->paddingPerLine = 0;
	}
	else {
		this->paddingPerLine = 4-(*pWidth)*(this->bytesPerPixel)%4;
	}

	// Calculate the number of padding bytes in the entire file.
	this->paddingAvailable = paddingPerLine*(*pHeight);

	// Closes the reader
	reader.close();

	// deletes the pointer no longer in use
	delete pWidth ;
	delete pHeight;
	delete pBitesPerPixel;

	// returns true to signify the file was properly open
	return true;
}

/*
 * Takes the new Address of the bmp file the header is has to read.
 * returns true and sets all the attributes if the file was open.
 * returns false if the file could not be open
 */
bool Header::setfileAddress(string newAddress){

	this->fileAddress = newAddress;
	if ( this->setup() == true ) {
		return true;
	}
	else{
		return false;
	}
}

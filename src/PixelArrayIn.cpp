/*
 * PixelArrayIn.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: Isabelle
 */

#include "PixelArrayIn.hpp"

PixelArrayIn::PixelArrayIn() {
}

PixelArrayIn::PixelArrayIn(string newAddress):PixelArray::PixelArray(newAddress) {
	this->setFileAddress(newAddress);

}
PixelArrayIn::~PixelArrayIn() {
	cout << "You are destroying a PixelArrayIn." << endl;
}

/**
 * Insert a message inside the image.
 * returns true to indicates success, false to indicate failure
 * throws an exception if the message was too long, indicating the size of the message and the maximum room available inside the padding bytes.
 */
bool PixelArrayIn::insertMessage(string message){

	// does not execute the function if the file was not setup properly
	if (this->valid == false){
		return false;
	}
	// throws an exception if the message is too long
	else if (this->pFileHeader->getPaddingAvailable() < (int)message.size() ){
		throw MessageTooLong((int)message.size(), this->pFileHeader->getPaddingAvailable());
		return false;
	}
	// attempts inserting the message
	else{

		// stores the addresses of the beginning of the padding bytes of each line.
		int lineAddress [this->pFileHeader->getImageHeight()];
		lineAddress[0] = this->pFileHeader->getBeginningOfArray() + (this->pFileHeader->getImageWidth())*this->pFileHeader->getBytesPerPixel();
		for (int i = 1; i < this->pFileHeader->getImageHeight(); i++){
			lineAddress[i] = this->pFileHeader->getBeginningOfArray() + (this->pFileHeader->getImageWidth())*this->pFileHeader->getBytesPerPixel()*(i+1) + this->pFileHeader->getPaddingPerLine()*i;
		}
		// Opens the writer using the address stored inside the header (has to be converted into a c-string)
		this->writer.open(this->pFileHeader->getFileAddress().c_str(), ios::out | ios::in | ios::binary);

		// if the file could be opened
		if (this->writer.is_open() == true){
			int charCounter = 0; // keeps track of the number of characters inserted
			// check if the end of the message was reached
			while ( charCounter <= (int)message.size() ){
				// keeps track of the current line
				for (int j = 0; j < this->pFileHeader->getImageHeight(); j++){
					// Keeps track of the current padding byte within the current line
					for (int k = 0; k < this->pFileHeader->getPaddingPerLine(); k++){
						// places the writing position at the current line (j), at the current padding byte (k)
						this->writer.seekp(lineAddress[j] + (k) );
						// write the current character (i)
						this->writer.write(&message[charCounter], 1);
						// moves on to the next character.
						charCounter++;
					}// end of for
				}// end of for
			}// end of while
		}// end of if
		// if the file could not be opened
		else{
			return false;
		} // end of else
	}// end of else

	//Closes the writer
	this->writer.close();

	// the end of the function has been reached
	// indicate success
	return true;
}// end of insertMessage

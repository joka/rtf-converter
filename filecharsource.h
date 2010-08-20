/*Copyright 2001
 *
 * filecharsource.h
 *
 * Author: Gregory Ford greg@reddfish.co.nz
 * RTF token parser based on:
 *      rtf2html by Dmitry Porapov <dpotapov@capitalsoft.com>,
 *      based on earlier work of Chuck Shotton.
 *      distributed under BSD-style license
 * RTF token lists and hashing algorithm based on
 *      RTF Tools, Release 1.10 
 *      6 April 1994	
 *      Paul DuBois	dubois@primate.wisc.edu 
 *
 * Copying permitted under GNU licence (see COPYING)
 */ 
// filecharsource.h: interface for the FileCharSource class.
//
//////////////////////////////////////////////////////////////////////

class FileCharSource : public CharSource  
{
public:
	FileCharSource();
	FileCharSource( char * filename );
	FileCharSource( FILE * fileHandle );
	virtual ~FileCharSource();
	char unGetChar(char ch);
	char getChar();
	bool endOfInput();

private:
	FILE * f;
};


/*Copyright 2001
 *
 * filecharsource.cpp
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
// filecharsource.cpp: implementation of the FileCharSource class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>

#include "charsource.h"
#include "filecharsource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FileCharSource::FileCharSource()
{
	f = NULL;
}

FileCharSource::~FileCharSource()
{
	if (f) fclose(f);
}



FileCharSource::FileCharSource(FILE *fileHandle)
{
	f = fileHandle;
}


char FileCharSource::unGetChar(char ch)
{
	return ungetc(ch,f);
}
/**************************************/

char FileCharSource::getChar()
{
	char ch;
	do{
		ch=fgetc(f);
	} while ((ch=='\r')||(ch=='\n'));
	return ch;
}

/**************************************/

FileCharSource::FileCharSource(char *filename)
{
	f = fopen( filename, "r" );

}

bool FileCharSource::endOfInput()
{
	return (feof( f ) != 0);
}

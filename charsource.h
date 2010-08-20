/*Copyright 2001
 *
 * charsource.h
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
// charsource.h: interface for the CharSource class.
//
//////////////////////////////////////////////////////////////////////


class CharSource  
{
public:
	virtual bool endOfInput() = 0 ; //{return true;};
	virtual char unGetChar( char ch ) = 0 ; // {return '\0';};
	virtual char getChar() = 0 ;  //{return '\0';};
	CharSource();
	~CharSource();
};


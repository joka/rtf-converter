/*Copyright 2001
 *
 * charoutput.h
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
// charoutput.h: interface for the CharOutput class.
//
//////////////////////////////////////////////////////////////////////


class CharOutput  
{
public:
	virtual void putChar( char c );
	virtual int putString( string str);
	CharOutput();
	virtual ~CharOutput();

};

class FileCharOutput : public CharOutput  
{
public:
	int putString( string str);
	void putChar( char c );
	FileCharOutput( const char *filename );
	//FileCharOutput();
	virtual ~FileCharOutput();

private:
	FILE * fh;
};



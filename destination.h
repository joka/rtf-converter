/*Copyright 2001
 *
 * destination.h
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
// destination.h: interface for the Destination class.
//
//////////////////////////////////////////////////////////////////////

class Destination  
{
public:
	virtual bool handleToken( Token* token)=0;
	Destination();
	virtual ~Destination();

};


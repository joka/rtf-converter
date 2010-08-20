/*Copyright 2001
 *
 * stylemap.h
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
// stylemap.h

class StyleMap  
{
public:
	int rtfStyle[1 + h5Tag - pTag];
	void setStyle( TagType tag, int rtfStyleNumber );
	TagType getStyle( int rtfStyleNumber );
	StyleMap();
	virtual ~StyleMap();

};
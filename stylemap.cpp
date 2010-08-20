/*Copyright 2001
 *
 * stylemap.cpp
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
//////////////////////////////////////////////////////////////////////
// stylemap.cpp
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include <string>
#include <memory>
using namespace std;


#include "tag.h"
#include "stylemap.h"


StyleMap::StyleMap()
{
	for ( int i = (int) pTag ; i <= (int) h5Tag ; i++ ) {
		rtfStyle[i - (int) pTag] = pTag ;
	}
}

StyleMap::~StyleMap()
{

}

TagType StyleMap::getStyle(int rtfStyleNumber)
{
	for ( int i = (int) pTag ; i <= (int) h5Tag ; i++ ) {
		if ( rtfStyle[i -(int) pTag ] == rtfStyleNumber) {
			return (TagType) i;
		}
	}
	return noTag;	
}

void StyleMap::setStyle(TagType tag, int rtfStyleNumber)
{
	if ( tag >= pTag && tag <= h5Tag ) {
		rtfStyle[ ((int) tag ) - ((int) pTag)] = rtfStyleNumber;
	}
}

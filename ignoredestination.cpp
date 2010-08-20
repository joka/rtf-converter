/*Copyright 2001
 *
 * ignoredestination.cpp
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
// ignoredestination.cpp: implementation of the IgnoreDestination class.
//
//////////////////////////////////////////////////////////////////////
#include <string>
using namespace std;
#include "token.h"
#include "charsource.h"
#include "tokeniser.h"

#include "destination.h"

#include "ignoredestination.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IgnoreDestination::IgnoreDestination()
{
	groupLevel = 0 ;
}

IgnoreDestination::~IgnoreDestination()
{

}
bool IgnoreDestination::handleToken( Token* token)
{
	if ( token->getType() == groupToken ) {
		GroupToken *g = (GroupToken *)token;
		if ( g->group == startGroup ) {
			groupLevel++;
		} else {
			groupLevel--;
		}
		if (groupLevel <0) {
			groupLevel = 0; // reinitialise this object
			// ready for reusing on another group!
			return true;
		}
	}
	return false;
}

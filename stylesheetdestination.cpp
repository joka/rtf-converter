/*Copyright 2001
 *
 * stylesheetdestination.cpp
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
// stylesheetdestination.cpp: implementation of the StyleSheetDestination class.
//
//////////////////////////////////////////////////////////////////////
#include <string>
using namespace std;

#include "tag.h"
#include "token.h"
#include "stylemap.h"
#include "charsource.h"
#include "tokeniser.h"
#include "destination.h"
#include "stylesheetdestination.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

StyleSheetDestination::StyleSheetDestination()
{
	groupLevel = 0 ;
	currentStyleNum = 0;
}

StyleSheetDestination::~StyleSheetDestination()
{

}

bool StyleSheetDestination::handleToken(Token *token)
{
	switch ( token->getType() ) {
	case groupToken:
		{
			GroupToken *g = (GroupToken *)token;
			if ( g->group == startGroup ) {
				groupLevel++;
			} else {
				groupLevel--;
				if ( groupLevel == 0 ) {
					AddCurrentStyleToMap();
					currentStyleName = "";
					currentStyleNum = 0;
				}
			}
			if (groupLevel <0) {
				groupLevel = 0; // reinitialise this object
				// ready for reusing on another group!
				return true;
			}
		break;
		} 
	case controlToken:
		{
			ControlToken *c = (ControlToken *) token;
			if ( c->rtfMajor == rtfParAttr && c->rtfMinor == rtfStyleNum ) {
				currentStyleNum = c->arg;
			}
		break;
		}
	case charToken:
		{
			currentStyleName += token->text;
			break;
		}
	default:
		break;
	}
	return false;
}


void StyleSheetDestination::setStyleMap(StyleMap *map)
{
	styleMap = map;
}


void StyleSheetDestination::AddCurrentStyleToMap()
{
	if ( currentStyleName.find_last_of( ';' ) == currentStyleName.size() -1 ) {
		currentStyleName = currentStyleName.substr( 0, currentStyleName.size() - 1 );
	}

	// potentially get error for "heading 10" ---> interpreted as heading 1
	if ( currentStyleName.size() > 8 ) {
		string s = currentStyleName.substr(0,8) ; 
		if ( currentStyleName.substr(0,8) == "heading " ) {
		switch ( currentStyleName[8] ) {
			case '1':
				{
					styleMap->setStyle( h1Tag, currentStyleNum );
					break;
				}
			case '2':
				{
					styleMap->setStyle( h2Tag, currentStyleNum );
					break;
				}
			case '3':
				{
					styleMap->setStyle( h3Tag, currentStyleNum );
					break;
				}
			case '4':
				{
					styleMap->setStyle( h4Tag, currentStyleNum );
					break;
				}
			case '5':
				{
					styleMap->setStyle( h5Tag, currentStyleNum );
					break;
				} 
			default:
				break;
			}
		}
	}
}

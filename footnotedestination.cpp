/*Copyright 2001
 *
 * footnotedestination.cpp
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
// footnotedestination.cpp: implementation of the FootnoteDestination class.
//
//////////////////////////////////////////////////////////////////////
#include <string>
#include <cstring>
#include <vector>
using namespace std;

#include "token.h"
#include "charoutput.h"
#include "charsource.h"
#include "tokeniser.h"

#include "destination.h"
#include "footnotedestination.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FootnoteDest::FootnoteDest()
{

}

FootnoteDest::~FootnoteDest()
{

}

bool FootnoteDest::handleToken(Token *token)
{
	switch (token->getType()) {
	case groupToken:
		{
			GroupToken *g = (GroupToken *)token;
			if ( g->group == startGroup ) {
				groupLevel++;
			} else {
				groupLevel--;
			}
			if (groupLevel <0) {
				char fnString[64];
				groupLevel = 0; // reinitialise this object
				footnotes.push_back( current );
				sprintf( fnString, 
					"<sup><a href=\"#footnote_%d\">%d</a></sup>", footnotes.size(), footnotes.size() ); 
				out->putString( fnString ); 
				current = "";
				// ready for reusing on another footnote!
			return true;
			}
		}
		break;
	case controlToken:
		// ignore all formatting in footnotes
		break;
	case charToken:
		current += token->text;
		break;
	default:
		break;
	}
	return false;
}

FootnoteDest::FootnoteDest(CharOutput *out)
{
	this->out= out;
}

void FootnoteDest::outputAll()
{
	char fnString[96];
	out->putString ( "<hr>" );
	for ( int i = 0; i < footnotes.size() ; i++ ) {
		sprintf( fnString, 
				"<p><sup>%d</sup>&nbsp;", i++); 
		out->putString( fnString ); 			
		out->putString( footnotes[i]  );
		out->putString( "</p>"  ); 
	}
}

/*Copyright 2001
 *
 * infodestination.cpp
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
// infodestination.cpp: implementation of the InfoDestination class.
//
//////////////////////////////////////////////////////////////////////
#ifdef WIN32 
#pragma warning( disable : 4786 ) 
#endif
#include <string>
#include <vector>
// #include <cstring>
using namespace std;

#include <stdio.h>

#include "linktracker.h"
#include "token.h"
#include "charsource.h"
#include "charoutput.h"
#include "tokeniser.h"
#include "destination.h"
#include "infodestination.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

InfoDestination::InfoDestination()
{
	groupLevel = 0;
}

InfoDestination::~InfoDestination()
{

}

bool InfoDestination::handleToken(Token *token)
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
	return false; // no change	
}

svec FootnoteDest::footnotes;

FootnoteDest::FootnoteDest()
{
	groupLevel = 0;
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
				footnotes.push_back( current );
				sprintf( fnString, 
					"<sup><a href=\"#footnote_%d\">%d</a></sup>", footnotes.size(), footnotes.size() ); 
				out->putString( fnString ); 
				groupLevel = 0; // reinitialise this object
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
CharOutput *FootnoteDest::out= NULL;

void FootnoteDest::setOutput(CharOutput *out)
{
	FootnoteDest::out= out;
}

void FootnoteDest::outputAll()
{
	char fnString[96];
	if ( out == NULL ) {
		return;
	}
	out->putString ( "<hr>" );
	for ( int i = 0; i < footnotes.size() ; i++ ) {
		string str(footnotes[i]);
		sprintf( fnString, 
			"<p class=\"footnote\"><sup><a name=\"footnote_%d\">%d</a></sup>&nbsp;", 
			i+1, 
			i+1
		); 
		out->putString( fnString ); 			
		out->putString( str );
		out->putString( "</p>"  ); 
	}
}

//////////////////////////////////////////////////////////////////////
// FieldDest Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FieldDest::FieldDest()
{
	groupLevel =0;
}

FieldDest::~FieldDest()
{

}

FieldDest::FieldDest(CharOutput *out, LinkTracker *tracker)
{
	groupLevel = 0;
	this->out= out;
	linkTracker = tracker;
}

bool FieldDest::handleToken(Token *token)
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
			if (groupLevel <= 0) {
				groupLevel = 0; // reinitialise this object
				// ready for reusing on another footnote!
				return true; // end of field destination
			}
		}
		break;
	case controlToken:
		return handleControlToken( (ControlToken *) token );
		// ignore all formatting in fields
		break;
	case charToken:
		// strip out the spaces
		switch ( source ) {
		case rtfFieldInst:

			if ( token->text != " " && token->text != "\"") {
				linkTracker->link.append( token->text );
			}
			if ( linkTracker->link.find( string("HYPERLINK" ) ) != -1 ) {
				linkTracker->hyperlink = true;
				linkTracker->link = "";
			}
			break;
		case rtfFieldResult:
			linkTracker->hasResult = true;
			linkTracker->result.append( token->text );
			break;
		}
		break;
	default:
		break;
	}
	return false;
}

bool FieldDest::handleControlToken(ControlToken *token)
{
	switch ( token->rtfMinor ) {
	case rtfField:
		source = rtfField;
		linkTracker->hyperlink = false; // don't know what kind of field yet!
		linkTracker->link = "";
		linkTracker->hasResult = false; // 
		linkTracker->result = "";
		break;
	case rtfFieldInst:
		source = rtfFieldInst;
		break;
	case rtfFieldResult:
		source = rtfFieldResult;
		break;
	default:
		break;
	}	
	return false;
}



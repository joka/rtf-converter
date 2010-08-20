/*Copyright 2001
 *
 * rtfparser.cpp
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
// rtfparser.cpp: implementation of the RtfParser class.
//
//////////////////////////////////////////////////////////////////////
#ifdef WIN32 
// name decoration causes STL classes to have names > 256 characters 
// which is more than VC++ debugger can handle, to avoid ugly warning 
// messages disable warning C4786
#pragma warning( disable : 4786 ) 
#endif

#include <string>
#include <vector>
#include <stack>
using namespace std ;
#include <stdio.h>

#include "linktracker.h"
#include "charsource.h"	// 
#include "token.h"
#include "destination.h"

#include "tag.h"
#include "stylemap.h"
#include "tokeniser.h"
#include "charoutput.h"
#include "graphicstate.h"


#include "bodydestination.h"
#include "ignoredestination.h"
#include "stylesheetdestination.h"
#include "infodestination.h"
#include "rtfparser.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RtfParser::RtfParser()
{

}

RtfParser::~RtfParser()
{
	if ( body ) delete body;
	if ( ignore ) delete ignore; 
	if ( styleSheet ) delete styleSheet ;
	if ( field ) delete field ;
	if ( info ) delete info ; 
}

void RtfParser::parseDocument(CharSource * source, CharOutput * out)
{
	int newDestination = 0;
	currDestination = body;
	stack<Destination *> destinationStack;
	

	Tokeniser tokeniser(source);
	while ( !tokeniser.isFinished() ) {
		Token *token = tokeniser.nextToken();

		if ( token != NULL) {
			if ( token->destination ) {
				Destination * newDest;
				newDest = SetDestination( ((ControlToken *)token)->rtfMinor ) ;
				if (newDest != currDestination ) {
					destinationStack.push( currDestination );
					currDestination = newDest;
				}
			} 
			newDestination = currDestination->handleToken( token );
					
			if ( newDestination ) {
				unSetDestination( currDestination );
				if ( destinationStack.size() <1  ) {
					currDestination = body;
				} else {
					currDestination = destinationStack.top();
					destinationStack.pop();				
				}
				currDestination->handleToken( token );

			}

			delete token;
		}
	}
	body->popAllTags();
	FootnoteDest::outputAll();
}

Destination * RtfParser::SetDestination(int minorCode)
{
	switch ( minorCode ) {
	case rtfStyleSheet:
		return styleSheet;
	case rtfInfo:
	case rtfITitle:
	case rtfISubject:
	case rtfIAuthor:
	case rtfIKeywords:
		return info;
	case rtfParNumText:
	case rtfBody:
		return body;
	// 	return field; // disabled til I cn get fields sussed
	case rtfFootnote:
		return new FootnoteDest();
	case rtfField:
	case rtfFieldResult:
	case rtfFieldInst:
	case rtfCustomDestination:
	case rtfFontTbl:
	default:
		return new IgnoreDestination();
	}
}

RtfParser::RtfParser(CharOutput *out)
{
	body = new BodyDestination( out );
	body->setStyleMap( &styleMap );
	body->setLinkTracker( &linkTracker );

	ignore = new IgnoreDestination();
	styleSheet = new StyleSheetDestination();
	styleSheet->setStyleMap( &styleMap );
	field = new FieldDest( out, &linkTracker);
	FootnoteDest::setOutput( out );
	info = new InfoDestination();
	currDestination = body;
}

void RtfParser::unSetDestination(Destination *dest)
{
	if (	
		dest != body && 
		dest != styleSheet && 
		dest != info && 
		dest != field
		) 
	{
		delete dest;
	}
}


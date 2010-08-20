/*Copyright 2001
 *
 * rtfparser.h
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
// rtfparser.h: interface for the RtfParser class.
//
//////////////////////////////////////////////////////////////////////

class RtfParser  
{
public:
	void unSetDestination(Destination *dest);
	RtfParser( CharOutput * out );
	Destination * SetDestination( int minorCode );
	void parseDocument( CharSource *source, CharOutput *out );
	RtfParser();
	virtual ~RtfParser();

private:
	Destination *currDestination;
	BodyDestination *body;
	FootnoteDest *footnote;
	FieldDest *field;
	IgnoreDestination *ignore;
	StyleSheetDestination *styleSheet;
	InfoDestination *info;
	StyleMap styleMap;
	LinkTracker linkTracker; 
};




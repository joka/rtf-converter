/*Copyright 2001
 *
 * graphicstate.h
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
// graphicstate.h: interface for the GraphicState class.
//
//////////////////////////////////////////////////////////////////////

class GraphicState  
{
public:
	static bool table;
	GraphicState();
	virtual ~GraphicState();
	bool characterFormat[maxCharTag];  // highest character tag in enum TagType	
	TagType paragraphFormat;
	bool atag;
	static bool tableCell;
	static bool tableRow;
	bool listItem;
};

class ActiveGraphicState : public GraphicState  
{
public:
	ActiveGraphicState();
	virtual ~ActiveGraphicState();
//	static bool atag;
	static bool table;
	static bool tableCell;
	static bool tableRow;
};

class DesiredGraphicState : public GraphicState  
{
public:
	DesiredGraphicState();
	DesiredGraphicState( DesiredGraphicState *parent);
	virtual ~DesiredGraphicState ();
//	static bool atag;
	static bool table;
	static bool tableCell;
	static bool tableRow;
};




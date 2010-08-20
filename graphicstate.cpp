/*Copyright 2001
 *
 * graphicstate.cpp
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
// graphicstate.cpp: implementation of the GraphicState class.
//
//////////////////////////////////////////////////////////////////////
#include <string>
using namespace std ;

#include "tag.h"
#include "graphicstate.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//bool GraphicState::atag = false;
bool GraphicState::table = false;
bool GraphicState::tableCell = false;
bool GraphicState::tableRow = false;

GraphicState::GraphicState()
{
	int i;
	paragraphFormat = noTag;
	for ( i = (int) bTag; i < (int) maxCharTag; i++ ) {
		characterFormat[i] = false;
	}
	//table = false;
	//tableCell = false;
	//tableRow = false;
	listItem = false;
	atag = false;
}

GraphicState::~GraphicState()
{

}




//////////////////////////////////////////////////////////////////////
// DesiredGraphicState Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//bool DesiredGraphicState::atag = false;
bool DesiredGraphicState::table = false;
bool DesiredGraphicState::tableCell = false;
bool DesiredGraphicState::tableRow = false;

DesiredGraphicState::DesiredGraphicState(DesiredGraphicState *parent)
{
	int i;
	paragraphFormat = parent->paragraphFormat;
	for ( i = (int) bTag; i < (int) maxCharTag; i++ ) {
		characterFormat[i] = parent->characterFormat[i];
	}
	atag = false;
	//table = parent->tableCell; // tables are all now static so don't need to copy
	//tableCell = parent->tableCell;
	//tableRow = parent->tableRow;
	listItem = parent->listItem;
}
DesiredGraphicState::DesiredGraphicState()
{

}

DesiredGraphicState::~DesiredGraphicState()
{

}


ActiveGraphicState::ActiveGraphicState()
{

}

ActiveGraphicState::~ActiveGraphicState()
{

}


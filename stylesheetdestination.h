/*Copyright 2001
 *
 * stylesheetdestination.h
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
// stylesheetdestination.h: interface for the StyleSheetDestination class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STYLESHEETDESTINATION_H__A8B97BEC_18E0_11D5_9485_0080AD7A2368__INCLUDED_)
#define AFX_STYLESHEETDESTINATION_H__A8B97BEC_18E0_11D5_9485_0080AD7A2368__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class StyleSheetDestination : public Destination  
{
public:
	void AddCurrentStyleToMap();
	StyleMap * styleMap;
	void setStyleMap( StyleMap *map );
	string currentStyleName;
	int currentStyleNum;
	int groupLevel;
	bool handleToken( Token* token);
	StyleSheetDestination();
	virtual ~StyleSheetDestination();

};

#endif // !defined(AFX_STYLESHEETDESTINATION_H__A8B97BEC_18E0_11D5_9485_0080AD7A2368__INCLUDED_)

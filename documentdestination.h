/*Copyright 2001
 *
 * documentdestination.h
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
// documentdestination.h: interface for the DocumentDestination class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCUMENTDESTINATION_H__A8B97BF1_18E0_11D5_9485_0080AD7A2368__INCLUDED_)
#define AFX_DOCUMENTDESTINATION_H__A8B97BF1_18E0_11D5_9485_0080AD7A2368__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Destination.h"

class DocumentDestination : public Destination  
{
public:
	DocumentDestination();
	virtual ~DocumentDestination();

};

#endif // !defined(AFX_DOCUMENTDESTINATION_H__A8B97BF1_18E0_11D5_9485_0080AD7A2368__INCLUDED_)

/*Copyright 2001
 *
 * footnotedestination.h
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
// footnotedestination.h: interface for the FootnoteDestination class.
//
//////////////////////////////////////////////////////////////////////


class FootnoteDest : public Destination  
{
public:
	void outputAll();
	FootnoteDest( CharOutput * out);
	string current;
	bool handleToken( Token* token);
	FootnoteDest();
	virtual ~FootnoteDest();
	static vector<string> footnotes;
	int groupLevel;
	CharOutput * out;		
};


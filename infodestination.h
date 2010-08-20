/*Copyright 2001
 *
 * infodestination.h
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
// infodestination.h: interface for the InfoDestination class.
//
//////////////////////////////////////////////////////////////////////


class InfoDestination : public Destination  
{
public:
	bool handleToken( Token* token);
	InfoDestination();
	virtual ~InfoDestination();
	int groupLevel;
};

typedef string s;
typedef vector<s> svec;

class FootnoteDest : public Destination  
{
public:
	FootnoteDest();
	virtual ~FootnoteDest();
	static void setOutput( CharOutput * out);
	static void outputAll();
	string current;
	bool handleToken( Token* token);
	static svec  footnotes;
	int groupLevel;
	static CharOutput * out;		
};

enum FieldType { UnknownField, LinkField, ContentsField }; 

class FieldDest : public Destination  
{
public:
	int source;
	FieldDest();
	virtual ~FieldDest();
	FieldDest( CharOutput * out, LinkTracker *tracker);
	string current;
	FieldType fieldType;
	
	bool handleToken( Token* token);
	int groupLevel;
	CharOutput * out;		
private:
	bool handleControlToken( ControlToken * token );
	LinkTracker * linkTracker;
};



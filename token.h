/*Copyright 2001
 *
 * token.h
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
// token.h: interface for the Token class.
//
//////////////////////////////////////////////////////////////////////

typedef enum tag_TokenType {
	invalidToken,
	charToken,
	groupToken,
	controlToken
} TokenType;


class Token  
{
public:
	bool destination;
	virtual TokenType getType()=0;
	Token();
	virtual ~Token();
	string text;	// store the token text in case it is needed
};

typedef enum GroupType { startGroup, endGroup };

class GroupToken : public Token  
{
public:
	GroupToken( GroupType t );
	TokenType getType();
	GroupToken();
	virtual ~GroupToken();
	GroupType group;
};


class ControlToken : public Token  
{
public:
	int rtfMinor;
	int rtfMajor;
	TokenType getType();
	ControlToken();
	virtual ~ControlToken();
	bool hasArg;
	int arg;		// arg value if present
};


class CharToken : public Token  
{
public:
	CharToken( char ch );
	TokenType getType();
	CharToken();
	virtual ~CharToken();
	char ch;
};


class InvalidToken : public Token  
{
public:
	string errorMessage;
	InvalidToken( const char *errorMessage );
	TokenType getType();
	InvalidToken();
	virtual ~InvalidToken();

};


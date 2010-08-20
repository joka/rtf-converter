/*Copyright 2001
 *
 * tokeniser.cpp
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
// tokeniser.cpp: implementation of the Tokeniser class.
//
//////////////////////////////////////////////////////////////////////
#include <string>

using namespace std ;

#include "ctype.h"
#include <stdlib.h>
#include "charsource.h"	// 
#include "token.h"
#include "tokeniser.h"
#include <cstring>
#include "rtftokens.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static bool	hashTableReady = false;

Tokeniser::Tokeniser()
{
	finished = true;
	lookupInit();
}

Tokeniser::~Tokeniser()
{

}

Tokeniser::Tokeniser(CharSource *source)
{
	Tokeniser();
	setCharSource (source);
	finished = false;
	
}

Token *Tokeniser::nextToken()
{
	char ch;
	if ( !charSource ) return NULL;

	if(charSource->endOfInput()) {
		finished = true;
		return NULL;
	}
	ch = charSource->getChar();
	switch (ch) 
	{
	case '\\':
		return backslash() ;
		break;
	
	case '{':
		return (Token * ) new GroupToken( startGroup );
		break;
	
	case '}':
		return (Token * ) new GroupToken( endGroup );
		break;
	case '\xff':
		return NULL;
		break;
	default:
		return (Token * ) new CharToken( ch );
			
	}
}

void Tokeniser::setCharSource(CharSource *source)
{
	charSource = source;
	finished = false;
}


bool Tokeniser::isFinished()
{
	return finished;
}


int Tokeniser::buildArg(char ch)
{
	int i=0;
	char arg[MAX_RTF_TOKEN];

	if( charSource->endOfInput())
	{
		return -1;
	}
	if(ch=='-')
	{
		arg[i++]='-';
		ch=charSource->getChar();
		if(charSource->endOfInput())
		{
			arg[0]=0;

			return atoi( arg );
		}
	}
	for(;isdigit(ch);i++)
	{
		arg[i]=ch;
		if(i>=MAX_RTF_TOKEN-1)
		{
			arg[MAX_RTF_TOKEN-1]=0;
			while(isdigit(ch)) {
				ch=charSource->getChar();
				if(charSource->endOfInput())
					return atoi( arg );
			} 
			break;
		}
		ch=charSource->getChar();
		if(charSource->endOfInput())
		{
			arg[i+1]=0;
			return atoi(arg);
		}
	}
	arg[i]=0;
	 
	if(!isspace(ch)) {
		charSource->unGetChar( ch );
	}
	if( arg[0] == '\0' ) {
		return -1;
	} else {
		return atoi( arg );
	}
}

Token *Tokeniser::buildControlToken( char ch, bool isDestination)
{
	int i=0;
	char token[MAX_RTF_TOKEN];
	ControlToken * control = new ControlToken();
	control->destination = isDestination;

	for(i=1;;i++)
	{
		token[i-1]=ch;
		if(i>=MAX_RTF_TOKEN-1)
		{
			do {
				ch=charSource->getChar();
				if(charSource->endOfInput()) {
					token[i] = '\0';
					control->text = token;
					return control;
				}
			} while (isalpha(ch)); 	
			control->arg = buildArg(ch);
			break;
		}
		ch= charSource->getChar();
		if(charSource->endOfInput())
		{
			token[i]='\0';
			break;
		}
		if( !isalpha(ch) )
		{
			token[i]='\0';
			control->arg = buildArg(ch);
			break;
		}
	}
	token[i]='\0';
	control->text.assign(token, i);
	//control->text = token;
	lookup (token, control);
	return (Token *) control;
}

Token *Tokeniser::backslash()
{
	// already seen a backslash

	char ch = charSource->getChar();
	if(charSource->endOfInput())
	{
		return (Token *) new InvalidToken("backslash at end of file");
	}
	if ( ch == '*' ) {
		return handleDestination();
	}

	switch (ch) 
	{
		case '\\':
		case '{':
		case '}':
		case '_':  // it seems \_ is another valid RTF escape 
			return (Token * ) new CharToken( ch );
			break;
		case '\'': // single quote -> rtf escaped character 
		{
			char ch1, ch2;
			ch1 = charSource->getChar();
			ch2 = charSource->getChar();
			if(!charSource->endOfInput()) 
			{
				if(isxdigit(ch1)&&isxdigit(ch2))
				{
					ch = chartoi(ch1)*16+chartoi(ch2);
					return (Token * ) new CharToken( ch );
				}
			} 
			return (Token *) new InvalidToken("invalid rtf character escape code");
			break;
		}
		default:
			if (isalpha(ch)) 
			{
				return buildControlToken(ch, false);
			} else {
				return (Token *) new InvalidToken("unrecognised rtf escape code");
			}
			break;
	}
}

Token * Tokeniser::handleDestination()
{

	char ch = charSource->getChar();
	if(charSource->endOfInput())
	{
		return (Token *) new InvalidToken("backslash at end of file");
	}

	if ( ch == '\\' ) {
		char ch = charSource->getChar();
		if(charSource->endOfInput())
		{
			return (Token *) new InvalidToken("backslash at end of file");
		}

		if (isalpha(ch)) 
		{
			return buildControlToken( ch, true);
		} else {
			return (Token *) new InvalidToken("non-alphabetic character in destination name");
		}
	} else {
		return (Token *) new InvalidToken("\\destination expected after '\\*'");
	}

}

int Tokeniser::chartoi(char ch)
{
	if((ch>='0')&&(ch<='9'))
		return ch-'0';
	if((ch>='A')&&(ch<='Z'))
		return ch-'A'+10;
	if((ch>='a')&&(ch<='z'))
		return ch-'a'+10;
	return -1;
}

/*
 * Initialize lookup table hash values.  Only need to do this once.
 */

void
Tokeniser::lookupInit ()
{
	RTFKey	*rp;

	if (!hashTableReady )
	{
		for (rp = rtfKey; rp->rtfKStr != (char *) NULL; rp++)
			rp->rtfKHash = hash (rp->rtfKStr);
		hashTableReady = true;
	}
}


/*
 * Determine major and minor number of control token.  If it's
 * not found, the class turns into rtfUnknown.
 */

void
Tokeniser::lookup (char *s, ControlToken *token)
{
	RTFKey	*rp;
	int	hashValue;

	hashValue = hash (s);
	for (rp = rtfKey; rp->rtfKStr != (char *) NULL; rp++)
	{
		if (hashValue == rp->rtfKHash && strcmp (s, rp->rtfKStr) == 0)
		{
			//token->rtfClass = rtfControl;
			token->rtfMajor = rp->rtfKMajor;
			if ( token->rtfMajor == rtfDestination ) {
				token->destination = true;
			}
			token->rtfMinor = rp->rtfKMinor;
			return;
		}
	}
	//token->rtfClass = rtfUnknown;
}


/*
 * Compute hash value of symbol
 */

int
Tokeniser::hash (char *s)
{
	char	c;
	int	val = 0;

	while ((c = *s++) != '\0') {
		val += (int) c;
	}
	return (val);
}


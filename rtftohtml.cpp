/*Copyright 2001
 *
 * rtftohtml.cpp
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
// rtftohtml.cpp

#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std ;
#include <stdio.h>

#include "linktracker.h"

#include "charoutput.h"
#include "charsource.h"
#include "filecharsource.h"

#include "tag.h"
#include "stylemap.h"
#include "token.h"
#include "tokeniser.h"

#include "graphicstate.h"
#include "destination.h"
#include "bodydestination.h"
#include "ignoredestination.h"
#include "stylesheetdestination.h"
#include "infodestination.h"

#include "rtfparser.h"

void indent( int groupLevel ) {
	cout << endl;
	for ( int i = 0 ; i < groupLevel ; i++ ) {
		cout << "\t";
	}

}

void usage( const char *app_name )
{
	cout << "usage: " << app_name << " [ -options ] filename" << endl;
	cout << "where -options are:" << endl;
	cout << "\t-o outputfile" << endl;
	cout << "\t-help" << endl;
}

int 
main( int argc, char *argv[ ] )
{
	int argno;
	char *infile = NULL;
	char *outfile = NULL;

	// parse the command line parameters.

	if ( argc == 1 ) { // called with no parameters 
		usage(argv[0]);
		return 1; // is this an error? (maybe should take input from stdin --> stdout??)
	}
	for ( argno = 1; argno < argc; argno++ ) {
		switch ( *argv[argno] ) {
		case '-':
			// we have an option 
			if ( strcmp( argv[argno], "-help" ) == 0 ) {
				usage(argv[0]);
				return 0;
			} else if ( strcmp( argv[argno], "-o" ) == 0 ) { 
				if ( argno >= argc ) {
					usage (argv[0]);
					return 2;
				}
				argno++;
				outfile = argv[argno];
			}
			break;
		default:
			infile = argv[argno];
		}
	}
	FileCharSource *src;

	// note: we are ignoring outfile if it was specified and always writing to stdout
		
	if ( infile != NULL ) {
		src = new FileCharSource( infile );
	} else {
		src = new FileCharSource( stdin );
	}

	CharOutput *dest = NULL;
	
	if ( outfile != NULL ) {
		dest = (CharOutput *) new FileCharOutput( outfile );
	} else {
		dest = new CharOutput();

	}

	RtfParser parser( dest );
	parser.parseDocument( src, dest);
	return 0;
};


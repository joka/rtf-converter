/*Copyright 2001
 *
 * bodydestination.cpp
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
#include <string>
#include <vector>
#include <stack>
using namespace std ;

#include <stdio.h>

#include "linktracker.h"
#include "htmlcodes.h"
#include "charsource.h"	// 
#include "token.h"
#include "destination.h"
#include "tag.h"
#include "stylemap.h"
#include "tokeniser.h"
#include "charoutput.h"
#include "graphicstate.h"
#include "bodydestination.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


BodyDestination::BodyDestination()
{
	HTML_CODES = ANSI_CODES;
}

BodyDestination::~BodyDestination()
{

}

BodyDestination::BodyDestination(CharOutput *out)
{
	linkTracker = NULL;
	HTML_CODES = ANSI_CODES;
	this->out= out;
}

bool BodyDestination::handleToken(Token *token)
{

	switch (token->getType()) {
	case groupToken:
		return handleGroup((GroupToken *) token);
		break;
	case controlToken:
		return handleControl((ControlToken *) token);
		break;
	case charToken:
		 handleChar((CharToken *) token);
		break;
	default:
		break;
	}
	return false;
}

bool BodyDestination::handleGroup(GroupToken *token)
{
	if (token->group == startGroup) {
		return handleStartGroup(token);
	} else { 
		return handleEndGroup(token);
	}
}

void BodyDestination::prepareCharContext()
{
	if ( contextStack.size() == 0 ) {
		contextStack.push( new DesiredGraphicState() );
	}
	DesiredGraphicState targetState = contextStack.top();

	reconcileStates( targetState ); 
	// when no paragraph formatting is specified enclose 
	// text in <p>
	if ( activeState.paragraphFormat == 0 ) {
		pushParagraph( pTag );
	}
}

int BodyDestination::handleChar(CharToken *token)
{
	prepareCharContext();
	putHtmlChar( (unsigned char) token->text[0] );
	return contextStack.size(); 
}

bool BodyDestination::handleControl(ControlToken *token)
{
	DesiredGraphicState * targetState;
	if ( contextStack.empty() ) {
		targetState = new DesiredGraphicState();
	} else {
		targetState=&(contextStack.top());
	}

	switch ( token->rtfMajor ) {
	case rtfCharAttr:
		// handle bold/italic/underline/subscript/superscript
		handleRtfCharAttr(token, targetState);
		break;
	case rtfSpecialChar:
		// handle paragraph tabs emDash etc
		handleRtfSpecialChar(token, targetState);
		break;
	case rtfTblAttr:
		// handle table ( \trowd )
		handleRtfTblAttr(token, targetState);
		break;
	case rtfParAttr:
		handleRtfParAttr(token, targetState);
		break;
	case rtfCharSet:
		if ( token->rtfMinor == rtfMacCharSet ) {
			HTML_CODES = MAC_CODES; // translate mac charset.
		}
		break;
	case rtfDestination:
		// change destination to destination specified in token
		if (token->rtfMinor == rtfFieldResult ) {
			return handleField( token );
			// return false; // FieldResults can be parsed by the Body Destination
		}
		return true;
	default:
			// do nothing ??
		break;
	}
	return false; // no change in destination
}



bool BodyDestination::handleStartGroup(Token *token)
{
	// copy the current state
	DesiredGraphicState *newState; 
//	if ( fieldStack.size() > 0 ) {
//		int& fieldGroup = fieldStack.top();
//		fieldGroup++;
//	}
	if ( contextStack.empty() ) {
		newState = new DesiredGraphicState();
	} else {
		newState = new DesiredGraphicState( contextStack.top() );
	}
	contextStack.push(newState);

	return false;
}

bool BodyDestination::handleEndGroup(Token *token)
{

//	if ( fieldStack.size() > 0 ) {
//		int& fieldGroup = fieldStack.top();
//		if ( fieldGroup == 1 ) {					
//			if ( contextStack.size() == 0 ) {
///				contextStack.push( new DesiredGraphicState() );
//			}
//			DesiredGraphicState targetState = contextStack.top();
//
//			reconcileStates( targetState ); 
//			out->putString( "</a>" );
//			fieldStack.pop();
//			return true;
//		} else {
//			fieldGroup-- ;
//		}
//	}
//	if (contextStack.size() <= 1) {
//		//end of document
//		popAllTags(); // write out any end tags (e.g. </p>) 
//	}
// parser should now call papAllTags explicitly when we are finished
	if ( linkTracker->hasResult ) {
		out->putString( linkTracker->result );
		linkTracker->hasResult = false;
		linkTracker->result = "";
	}
	
	// just throw away the previous state
	if ( contextStack.size() > 0 ) {
		contextStack.pop();
		return false;
	} else {
		return true;
	}
}


void BodyDestination::reconcileStates(DesiredGraphicState& desired)
{
	int i;
	
	//pop any tags which are not desired
	//If "desired" has no paragraph setting, change it to <p>
	// unless we are in a table (where it's ok to go without the <p>)

	if ( desired.paragraphFormat == noTag && !desired.table) {
		desired.paragraphFormat = pTag;
	}

	if ( activeState.table && !desired.table) {
		popTo( tableTag );
	}

	if ( activeState.tableRow && !desired.tableRow) {
		popTo( trTag );
	}

	if ( activeState.tableCell && !desired.tableCell) {
		popTo( tdTag );
		if ( desired.tableRow ) {
			desired.tableCell = true; // we need to put <td> back now
		}
	}

	if ( (activeState.paragraphFormat != noTag) 
		&& (activeState.paragraphFormat != tableTag)
		&& (desired.paragraphFormat != activeState.paragraphFormat) ) 
	{
		popTo( pTag );	
	}
	for ( i = (int) bTag; i < (int) maxCharTag; i++ ) {
		if ( activeState.characterFormat[i] && !desired.characterFormat[i] ) {
			popTo((TagType) i);
			activeState.characterFormat[i] = false;
		}
	}
	if ( activeState.atag && !desired.atag ) {
		popTo( aTag ); // we pop the <a> tags, 
		// but there no matching push(aTag) - we don't put them back after formatting tags!
	}

	if ( desired.table) {
		
		if ( !activeState.table ) {
			pushTable();
		}
		if ( desired.tableRow && !activeState.tableRow) {
			pushTableRow();
			desired.tableCell = true; // always have <td> after <tr>
		}
		if ( desired.tableCell && !activeState.tableCell ) {
			pushTableCell();
		} 
	}

	//push any tags which are desired but not active
	if ( desired.paragraphFormat != activeState.paragraphFormat ) 
	{
		pushParagraph(desired.paragraphFormat);
	}
	for ( i = (int) bTag; i < (int) maxCharTag; i++ ) {
		if ( activeState.characterFormat[i] != desired.characterFormat[i] ) {
			pushFormat((TagType) i);
		}
	}

}


void BodyDestination::pushFormat(TagType format)
{
	Tag newTag( format );
	out->putString( newTag.toString() );
	newTag.endTag = true;
	tagStack.push( newTag );
	activeState.characterFormat[format] = true;
}

void BodyDestination::pushParagraph(TagType item)
{
	Tag newTag( item );
	out->putString( "\n" + newTag.toString() );
	newTag.endTag = true;
	tagStack.push( newTag );
	activeState.paragraphFormat = item;
}
void BodyDestination::popTo(TagType stopTag)
{
	while ( tagStack.size() > 0 ) {
		Tag top = tagStack.top();
		if ( top.tagType == tableTag ) {
			// table should always be the last tag on the stack 
			// so always stop when you see one!
			out->putString( top.toString() );
			activeState.table  = false;
			tagStack.pop();
			break;
		} else if ( top.isParagraphFormat() ) 
		{
			out->putString( top.toString() );
			if ( activeState.table ) {
				activeState.paragraphFormat = tableTag;
			} else {
				activeState.paragraphFormat = noTag;
			}
			tagStack.pop();
			if ( stopTag == pTag ) {
				break;		
			}
		} else if ( top.isCharacterFormat() ) { 
			activeState.characterFormat[top.tagType] = false;
			out->putString( top.toString() );
			tagStack.pop();
			if ( top.tagType == stopTag ) {
				break;
			}
		} else {
			out->putString( top.toString() );
			if ( top.tagType == trTag ) {
				activeState.tableRow = false;
			} else if ( top.tagType == tdTag ) {
				activeState.tableCell = false;	
			} else if ( top.tagType == aTag ) {
				activeState.atag = false;
				// atag = false;
			} 

			tagStack.pop();
			if ( top.tagType == stopTag ) {
				break;
			}
		}
	}
}

void BodyDestination::popAllTags()
{
	while ( tagStack.size() > 0 ) {	
		popTo(tableTag);
	}
}

void BodyDestination::handleRtfParAttr(ControlToken *token, DesiredGraphicState *desired)
{
	if ( token->rtfMinor == rtfParDef ) {
		desired->paragraphFormat = pTag;
	} else if ( (token->rtfMinor == rtfInTable ) 
		&& (!desired->tableRow)  
		&& (!desired->tableCell )) 
	{
		// hack to match bogus RTF generated by Word 2000
		// if we get a \intbl and desired state is not currently 
		// in a table row or cell then assume we need to start 
		// a new row

		if ( activeState.tableRow ) {
			// close the preceding row  if it is still open
			popTo( trTag ); // a table is a top level object like a character
		}

		desired->table = true;
		desired->tableRow = true;
		desired->tableCell = true;
	} else if (token->rtfMinor == rtfStyleNum ) {
		TagType tag = styleMap->getStyle( token->arg );
		if (tag  != noTag ) {
			desired->paragraphFormat = tag;
		}
	}
}

int BodyDestination::handleRtfCharAttr(ControlToken *token, DesiredGraphicState *desired)
{
	int i =0;
	bool newTagState = true;
	if (token->hasArg && (token->arg == 0)) {
		newTagState = false;
	}
	switch ( token->rtfMinor ) {
	case rtfPlain:
		for (i = 0 ; i < maxCharTag ; i++) {
			desired->characterFormat[i] = false;
		}
		break;
	case rtfBold:
		desired->characterFormat[bTag] = newTagState;
		break;
	case rtfSubScrShrink:
	case rtfSubScript:
		desired->characterFormat[subTag] = newTagState;
		break;
	case rtfNoSuperSub:
		// what is this tag for??
		break;
	case rtfItalic:
		desired->characterFormat[iTag] = newTagState;
		break;
	case rtfUnderline:
	case rtfDotUnderline:
	case rtfDbUnderline:
	case rtfNoUnderline:
	case rtfWordUnderline:
		desired->characterFormat[uTag] = newTagState;
		break;
	case rtfSuperScrShrink:
	case rtfSuperScript:
		desired->characterFormat[supTag] = newTagState;
		break;
	default:
			// do nothing ??
		break;
	}
	return contextStack.size();
}

int BodyDestination::handleRtfSpecialChar(ControlToken *token, DesiredGraphicState *desired)
{
	// for special characters that really are part of the char stream
	// should create new CharToken from the ControlToken and call handleChar()
	switch ( token->rtfMinor ) {
	case rtfCell:
		desired->tableCell = false;
		break;
	case rtfRow:
		desired->tableRow = false;
		desired->table = false; // we only know we still have a table if 
		// we see the \\trowd before we see the next character 
		break;
	case rtfPar:
		popTo( pTag ); // need to write the previous </p> before we forget

		desired->paragraphFormat = noTag;// end of paragraph
		break;
	case rtfPage:
		break;
	case rtfLine: // how to we deal with these?
		out->putString(Tag::tagIdToString(brTag)); //by-passed output stack for now
		break;
	case rtfTab:
		prepareCharContext();
		out->putString("&nbsp;");
		break;
	case rtfEmDash:
		break;
	case rtfEnDash:
		break;
	case rtfEmSpace:
		break;
	case rtfEnSpace:
		break;
	case rtfBullet:
		break;
	case rtfLQuote:
		break;
	case rtfRQuote:
		break;
	case rtfLDblQuote:
		break;
	case rtfRDblQuote:
		break;
	case rtfNoBrkSpace:
		break;
	default:
			// do nothing ??
		break;
	}
	return contextStack.size();
}

int BodyDestination::handleRtfTblAttr(ControlToken *token, DesiredGraphicState *desired)
{
	switch ( token->rtfMinor ) {
	case rtfRowDef: 
		// this could be a continuation of the previous \\trowd (table) 
		// 
		if ( desired->tableRow ) {
			// Word 2000 defines the table at both start and end of the row 
			// so ignore a table definition when we are inside a row
			break;
		}
		if ( activeState.tableRow ) {
			// close the preceding row  if it is still open
			popTo( trTag ); // a table is a top level object like a character
		}

		desired->paragraphFormat = tableTag;
		desired->table = true;
		desired->tableRow = true;
		desired->tableCell = true;
		break;
	default:
			// do nothing ??
		break;
	}
	return contextStack.size();
}

void BodyDestination::pushTableCell()
{
	Tag newTag( tdTag );
	out->putString( newTag.toString() );
	newTag.endTag = true;
	tagStack.push( newTag );
	activeState.tableCell  = true;
}

void BodyDestination::pushTableRow()
{
	Tag newTag( trTag );
	out->putString( newTag.toString() );
	newTag.endTag = true;
	tagStack.push( newTag );
	activeState.tableRow  = true;
}

void BodyDestination::pushTable()
{
	Tag newTag( tableTag );
	out->putString( "\n" + newTag.toString() );
	newTag.endTag = true;
	tagStack.push( newTag );
	activeState.table  = true;
	if ( activeState.paragraphFormat == noTag ) {
		activeState.paragraphFormat = tableTag;
	}
}

void BodyDestination::setStyleMap(StyleMap *map)
{
	styleMap = map;
}




void BodyDestination::putHtmlChar(unsigned char c)
{
	if ( HTML_CODES[ c ][0] != '\0' ) {
		out->putString( string(HTML_CODES[ c ]) );
	} else {
		out->putChar( c );
	}
}


void BodyDestination::setLinkTracker(LinkTracker *tracker)
{
	linkTracker = tracker;
}

bool BodyDestination::handleField(ControlToken *token)
{
	if ( linkTracker->hyperlink ) {
		int i =0;
		DesiredGraphicState * targetState;
		if ( contextStack.empty() ) {
			targetState = new DesiredGraphicState();
		} else {
			targetState=&(contextStack.top());
		}

		activeState.atag = true;
		//Tag newTag( aTag, " href=\"" + linkTracker->link + "\"" );
		linkTracker->link = "http://" + linkTracker->link + "";
        Tag newTag(aTag, linkTracker->link);

		targetState->atag = true;

		linkTracker->link = "";
		linkTracker->hyperlink = false;
		out->putString( newTag.toString() );
		newTag.endTag = true;
		tagStack.push( newTag );
	}
	return false; 
}

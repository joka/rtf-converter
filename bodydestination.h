/*Copyright 2001
 *
 * bodydestination.h
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
// bodydestination.h: interface for the BodyDestination class.
//
//////////////////////////////////////////////////////////////////////


class BodyDestination : public Destination  
{
public:
	LinkTracker * linkTracker;
	void setLinkTracker ( LinkTracker * tracker );
	StyleMap * styleMap;
	void setStyleMap( StyleMap *map );
	BodyDestination( CharOutput * out);
	bool handleToken(Token*  token);
	BodyDestination();
	void popAllTags();
	virtual ~BodyDestination();

private:
	void prepareCharContext();
	void putHtmlChar( unsigned char c);
	void handleRtfParAttr( ControlToken *token, DesiredGraphicState *desired);
	int handleRtfTblAttr(ControlToken * token, DesiredGraphicState *desired);
	int handleRtfSpecialChar(ControlToken * token, DesiredGraphicState *desired);
	int handleRtfCharAttr(ControlToken * token, DesiredGraphicState *desired);
	GraphicState activeState;
	stack<Tag> tagStack;
	stack<DesiredGraphicState> contextStack;
	CharOutput * out;
	void popTo( TagType stopTag );
	void pushParagraph( TagType item);
	void pushFormat( TagType format );
	void reconcileStates(DesiredGraphicState& desired );
	void pushTable();
	void pushTableRow();
	void pushTableCell();
	char * *HTML_CODES;
	bool handleEndGroup(Token * token);
	bool handleStartGroup(Token * token);
	bool handleControl (ControlToken *token);
	int handleChar( CharToken *token);
	bool handleGroup( GroupToken *token);
	bool handleField( ControlToken *token );
	stack<int> fieldStack;
};


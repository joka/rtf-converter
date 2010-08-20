/*Copyright 2001
 *
 * tag.h
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
// tag.h: interface for the Tag class.
//
//////////////////////////////////////////////////////////////////////

typedef enum tag_TagType {
	noTag,
	bTag, iTag, uTag, subTag, supTag, maxCharTag,
	aTag, brTag, hrTag, pTag, h1Tag, h2Tag, h3Tag, h4Tag, h5Tag, 
	tableTag, ulTag, olTag, trTag, tdTag, liTag, maxTag
} TagType;

typedef struct tag_TagItem {
	bool hasEndTag;
	char text[12];
} TagItem;


class Tag  
{
public:
	static string tagIdToString( TagType tagId, bool endTag = false );
	bool isTable();
	bool isParagraphFormat();
	bool isCharacterFormat();
	void setAttributes( string& attributes);
	string getAttributes();
	Tag(TagType tagId, string& tagAttributes );
	Tag( TagType tagId );
	string toString(); // you'll need to delete this when you're finished with it
	virtual ~Tag();
	Tag();
	TagType tagType;
	bool endTag;
	string attributes;
	
private:
protected:
};


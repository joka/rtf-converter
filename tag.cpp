/*Copyright 2001
 *
 * tag.cpp
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
// Tag.cpp: implementation of the Tag class.
//
//////////////////////////////////////////////////////////////////////
#include <string>
#include <memory>
using namespace std;

#include "tag.h"

TagItem tagDefinition[maxTag] = {
	{false, ""},
	{true, "b"}, 
	{true, "i"}, 
	{true, "u"}, 
	{true, "sub"}, 
	{true, "sup"},
	{false, ""},
	{false, "a"},
	{false, "br"}, 
	{false, "hr"}, 
	{true, "p"}, 
	{true, "h1"}, 
	{true, "h2"}, 
	{true, "h3"}, 
	{true, "h4"}, 
	{true, "h5"}, 
	{true, "table"}, 
	{true, "ul"}, 
	{true, "ol"}, 
	{true, "tr"}, 
	{true, "td"}, 
	{true, "li"} 
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Tag::Tag()
{

}

Tag::~Tag()
{

}

//DEL string Tag::get_tag_name()
//DEL {
//DEL 	return tag_name;
//DEL }

//DEL bool Tag::get_endTag()
//DEL {
//DEL 	return endTag;
//DEL }

//DEL Tag::Tag(string tag_name, bool endTag)
//DEL {
//DEL 	this->tag_name = tag_name;
//DEL 	this->endTag = endTag;
//DEL }

//DEL void Tag::set_endTag(bool endTag)
//DEL {
//DEL 	this->endTag = endTag;
//DEL }

//DEL void Tag::set_tag_name(string tag_name)
//DEL {
//DEL 	this->tag_name = tag_name;
//DEL }

string Tag::toString()
{
	if ( endTag ) {
		if ( tagDefinition[tagType].hasEndTag ) {
			return "</" + string( tagDefinition[tagType].text ) + ">"; 
		} else {
			return string ("");
		}
	} else {
		// start tag
		return "<" + string( tagDefinition[tagType].text ) + attributes + ">"; 
	}
}

Tag::Tag(TagType tagId)
{
	tagType = tagId;
	endTag = false;
}

Tag::Tag(TagType tagId, string &tagAttributes)
{
	tagType = tagId;
	endTag = false;
	attributes = tagAttributes; // use overloaded = to copy string ???
}

string Tag::getAttributes()
{
	return attributes; // copy constructor???
}

void Tag::setAttributes(string &attributes)
{
	this->attributes = attributes;
}

bool Tag::isCharacterFormat()
{
	if (tagType > noTag && tagType < maxCharTag ) {
		return true;
	} else {
		return false;
	}
}

bool Tag::isParagraphFormat()
{
	if (tagType >= pTag && tagType <= olTag ) {
		return true;
	} else {
		return false;
	}
}

bool Tag::isTable()
{
	if (tagType == tableTag ) {
		return true;
	} else {
		return false;
	}
}


string Tag::tagIdToString(TagType tagId, bool endTag)
{
	if ( endTag ) {
		if ( tagDefinition[tagId].hasEndTag ) {
			return "</" + string( tagDefinition[tagId].text ) + ">"; 
		} else {
			return string ("");
		}
	} else {
		// start tag
		return "<" + string( tagDefinition[tagId].text ) + ">"; 
	}

}

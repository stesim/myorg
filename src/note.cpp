#include "note.h"

using Glib::ustring;
using Glib::DateTime;

Note::Note()
	: m_bHasDate( false ), m_bIsFullDay( false )
{
}

Note::Note( ustring title, ustring content )
	: m_strTitle( title ), m_strContent( content ), m_bHasDate( false ),
	m_bIsFullDay( false )
{
}

Note::Note( ustring title, ustring content, DateTime date )
	: Note( title, content, date, false )
{
}

Note::Note( ustring title, ustring content, DateTime date, bool isFullDay )
	: m_strTitle( title ), m_strContent( content ), m_bHasDate( true ),
	m_Date( date ), m_bIsFullDay( isFullDay )
{
}

Note::~Note()
{
}

const ustring& Note::getTitle() const
{
	return  m_strTitle;
}

void Note::setTitle( const ustring& title )
{
	m_strTitle = title;
}

const ustring& Note::getContent() const
{
	return m_strContent;
}

void Note::setContent( const ustring& content )
{
	m_strContent = content;
}

bool Note::hasDate() const
{
	return m_bHasDate;
}

void Note::setHasDate( bool hasDate )
{
	m_bHasDate = hasDate;
}

const DateTime& Note::getDate() const
{
	return m_Date;
}

void Note::setDate( const DateTime& date )
{
	m_Date = date;
}

bool Note::isFullDay() const
{
	return m_bIsFullDay;
}

void Note::setIsFullDay( bool isFullDay )
{
	m_bIsFullDay = isFullDay;
}

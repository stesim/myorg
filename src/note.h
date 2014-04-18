#pragma once

#include <glibmm/datetime.h>
#include <glibmm/ustring.h>

class Note
{
public:
	Note();
	Note( Glib::ustring title, Glib::ustring content );
	Note( Glib::ustring title, Glib::ustring content, Glib::DateTime date );
	Note( Glib::ustring title, Glib::ustring content,
			Glib::DateTime date, bool isFullDay );
	virtual ~Note();

	const Glib::ustring& getTitle() const;
	void setTitle( const Glib::ustring& title );

	const Glib::ustring& getContent() const;
	void setContent( const Glib::ustring& content );

	bool hasDate() const;
	void setHasDate( bool hasDate );

	const Glib::DateTime& getDate() const;
	void setDate( const Glib::DateTime& date );

	bool isFullDay() const;
	void setIsFullDay( bool isFullDay );

private:
	Glib::ustring m_strTitle;
	Glib::ustring m_strContent;
	bool m_bHasDate;
	Glib::DateTime m_Date;
	bool m_bIsFullDay;
};

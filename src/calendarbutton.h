#pragma once

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <glibmm/datetime.h>
#include "notecollection.h"

class CalendarButton : public Gtk::Box
{
public:
	CalendarButton();
	virtual ~CalendarButton();

	NoteCollection* getNotes() const;
	void setNotes( NoteCollection* notes );

	const Glib::DateTime& getDate() const;
	void setDate( const Glib::DateTime& date );

	void updateNotes();

	bool isExpanded() const;
	void setExpanded( bool expanded );

private:
	void buttonClicked();

	void noteClicked( Note* note );

private:
	NoteCollection* m_pNotes;
	Glib::DateTime m_Date;
	Gtk::Button* m_pButton;
	Gtk::Box* m_pBox;
	bool m_bHasNotes;
};

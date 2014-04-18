#pragma once

#include <gtkmm/box.h>
#include "notecollection.h"
#include <map>
#include "calendarbutton.h"

class YearView : public Gtk::Box
{
public:
	YearView();
	virtual ~YearView();

	NoteCollection* getNotes() const;
	void setNotes( NoteCollection* notes );

	unsigned int getYear() const;
	void setYear( unsigned int year );

	void updateNotes();

private:
	void updateButtons();

private:
	NoteCollection* m_pNotes;
	unsigned int m_uiYear;
	bool m_bYearChanged;
	std::map<unsigned int, CalendarButton*> m_mapButtons;
};

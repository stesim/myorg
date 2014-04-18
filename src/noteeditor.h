#pragma once

#include <gtkmm/window.h>
#include "note.h"

namespace Gtk
{
class Box;
class Entry;
class TextView;
class Calendar;
class SpinButton;
class Button;
}

class NoteEditor : public Gtk::Window
{
public:
	NoteEditor();
	virtual ~NoteEditor();

	Note* getNote() const;
	void setNote( Note* note );

private:
	void saveClicked();

private:
	Note* m_pNote;
	Gtk::Box* m_pBox;
	Gtk::Entry* m_pTitleEntry;
	Gtk::TextView* m_pContentView;
	Gtk::Calendar* m_pCalendar;
	Gtk::SpinButton* m_pHourButton;
	Gtk::SpinButton* m_pMinuteButton;
	Gtk::Button* m_pSaveButton;
};

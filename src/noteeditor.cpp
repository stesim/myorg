#include "noteeditor.h"
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/textview.h>
#include <gtkmm/calendar.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>

NoteEditor::NoteEditor()
{
	set_default_size( 300, 400 );

	m_pBox = Gtk::manage( new Gtk::Box( Gtk::ORIENTATION_VERTICAL ) );

	m_pTitleEntry = Gtk::manage( new Gtk::Entry() );
	m_pContentView = Gtk::manage( new Gtk::TextView() );
	m_pCalendar = Gtk::manage( new Gtk::Calendar() );
	m_pHourButton = Gtk::manage( new Gtk::SpinButton() );
	m_pHourButton->set_digits( 0 );
	m_pHourButton->set_increments( 1, 4 );
	m_pHourButton->set_range( 0, 23 );
	m_pHourButton->set_value( 0 );
	m_pMinuteButton = Gtk::manage( new Gtk::SpinButton() );
	m_pMinuteButton->set_digits( 0 );
	m_pMinuteButton->set_increments( 1, 5 );
	m_pMinuteButton->set_range( 0, 59 );
	m_pMinuteButton->set_value( 0 );
	m_pSaveButton = Gtk::manage( new Gtk::Button( "Save" ) );
	m_pSaveButton->signal_clicked().connect(
			sigc::mem_fun( *this, &NoteEditor::saveClicked ) );

	Gtk::Box* hBox = Gtk::manage( new Gtk::Box( Gtk::ORIENTATION_HORIZONTAL ) );
	hBox->pack_start( *m_pHourButton, true, true );
	hBox->pack_start( *m_pMinuteButton, true, true );
	hBox->set_homogeneous( true );

	m_pBox->pack_start( *m_pTitleEntry, false, true );
	m_pBox->pack_start( *m_pContentView, true, true );
	m_pBox->pack_start( *m_pCalendar, false, true );
	m_pBox->pack_start( *hBox, false, true );
	m_pBox->pack_start( *m_pSaveButton, false, true );

	add( *m_pBox );

	m_pBox->set_sensitive( false );
}

NoteEditor::~NoteEditor()
{
}

Note* NoteEditor::getNote() const
{
	return m_pNote;
}

void NoteEditor::setNote( Note* note )
{
	m_pNote = note;

	if( m_pNote != nullptr )
	{
		set_title( m_pNote->getTitle() );
		m_pBox->set_sensitive( true );

		m_pTitleEntry->set_text( m_pNote->getTitle() );
		m_pContentView->get_buffer()->set_text( m_pNote->getContent() );

		if( m_pNote->hasDate() )
		{
			m_pCalendar->set_sensitive( true );
			
			const Glib::DateTime& date = m_pNote->getDate();
			m_pCalendar->select_month( date.get_month(), date.get_year() );
			m_pCalendar->select_day( date.get_day_of_month() );

			if( !m_pNote->isFullDay() )
			{
				m_pHourButton->set_sensitive( true );
				m_pMinuteButton->set_sensitive( true );

				m_pHourButton->set_value( date.get_hour() );
				m_pMinuteButton->set_value( date.get_minute() );
			}
			else
			{
				m_pHourButton->set_sensitive( false );
				m_pMinuteButton->set_sensitive( false );
			}
		}
		else
		{
			m_pCalendar->set_sensitive( false );
			m_pHourButton->set_sensitive( false );
			m_pMinuteButton->set_sensitive( false );
		}
	}
	else
	{
		m_pBox->set_sensitive( false );
	}
}

void NoteEditor::saveClicked()
{
	if( m_pNote != nullptr )
	{
		m_pNote->setTitle( m_pTitleEntry->get_text() );
		m_pNote->setContent( m_pContentView->get_buffer()->get_text() );
		guint year;
		guint month;
		guint day;
		m_pCalendar->get_date( year, month, day );
		m_pNote->setDate( Glib::DateTime::create_local(
					year, month, day, m_pHourButton->get_value_as_int(),
					m_pMinuteButton->get_value_as_int(),
					m_pNote->getDate().get_seconds() ) );

		close();
	}
}

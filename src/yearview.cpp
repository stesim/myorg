#include "yearview.h"

#include <glibmm/date.h>
#include <glibmm/datetime.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include "calendarbutton.h"
#include <iostream>

using Glib::Date;

YearView::YearView()
	: Gtk::Box( Gtk::ORIENTATION_HORIZONTAL ), m_pNotes( nullptr ),
	m_bYearChanged( true )
{
	this->set_homogeneous( true );

	Date date;
	date.set_time_current();
	m_uiYear = date.get_year();

	date.set_day( 1 );
	for( unsigned int i = 0; i < 12; ++i )
	{
		date.set_month(
				static_cast<Glib::Date::Month>( Glib::Date::JANUARY + i ) );

		Gtk::Box* box =
			Gtk::manage( new Gtk::Box( Gtk::ORIENTATION_VERTICAL ) );
		Gtk::Button* header =
			Gtk::manage( new Gtk::Button( date.format_string( "%B" ) ) );
		header->get_style_context()->add_class( "header" );
		box->pack_start( *header, false, true );

		pack_start( *box );
	}

	Gtk::Box* box = Gtk::manage( new Gtk::Box( Gtk::ORIENTATION_VERTICAL ) );
	Gtk::Button* header = Gtk::manage( new Gtk::Button( "General" ) );
	header->get_style_context()->add_class( "header" );
	box->pack_start( *header, false, true  );

	pack_start( *box );
}

YearView::~YearView()
{
}

NoteCollection* YearView::getNotes() const
{
	return m_pNotes;
}

void YearView::setNotes( NoteCollection* notes )
{
	m_pNotes = notes;
}

unsigned int YearView::getYear() const
{
	return m_uiYear;
}

void YearView::setYear( unsigned int year )
{
	if( year != m_uiYear )
	{
		m_uiYear = year;
		m_bYearChanged = false;
	}
}

void YearView::updateNotes()
{
	if( m_bYearChanged )
	{
		updateButtons();
		m_bYearChanged = false;
	}


	std::vector<Gtk::Widget*> boxes = get_children();
	for( unsigned int i = 0; i < 12; ++i )
	{
		Gtk::Box* box = static_cast<Gtk::Box*>( boxes[ i ] );

		std::vector<Gtk::Widget*> buttons = box->get_children();
		for( unsigned int j = 1; j < buttons.size(); ++j )
		{
			CalendarButton* btn = static_cast<CalendarButton*>( buttons[ j ] );
			btn->setNotes( m_pNotes );
			btn->updateNotes();
		}
	}

	Gtk::Box* box = static_cast<Gtk::Box*>( boxes.back() );
	std::vector<Gtk::Widget*> buttons = box->get_children();
	for( unsigned int i = buttons.size() - 1; i >= 1; --i )
	{
		box->remove( *buttons[ i ] );
	}

	unsigned int first;
	unsigned int last;
	m_pNotes->getGeneralNotes( first, last );
	for( unsigned int i = first; i <= last; ++i )
	{
		Note& note = m_pNotes->getNote( i );

		Gtk::Button* btn = Gtk::manage( new Gtk::Button( note.getTitle() ) );
		btn->set_alignment( 0.0f, 0.5f );

		box->pack_start( *btn, false, true );
	}
}

void YearView::updateButtons()
{
	m_mapButtons.clear();

	std::vector<Gtk::Widget*> boxes = get_children();
	for( unsigned int i = 0; i < 12; ++i )
	{
		Gtk::Box* box = static_cast<Gtk::Box*>( boxes[ i ] );
		std::vector<Gtk::Widget*> buttons = box->get_children();
		
		unsigned int days = Glib::Date::get_days_in_month(
				static_cast<Glib::Date::Month>( Glib::Date::JANUARY + i ),
				m_uiYear );
		int diff = buttons.size() - 1 - days;
		for( int j = 0; j < -diff; ++j )
		{
			box->pack_start(
					*Gtk::manage( new CalendarButton() ), false, true );
		}
		for( int j = 0; j < diff; ++j )
		{
			box->remove( *buttons[ buttons.size() - 1 - j ] );
		}

		buttons = box->get_children();

		for( unsigned int j = 1; j < buttons.size(); ++j )
		{
			CalendarButton* btn = static_cast<CalendarButton*>( buttons[ j ] );
			btn->setDate( Glib::DateTime::create_local(
						m_uiYear, i + 1, j, 0, 0, 0.0 ) );
			if( btn->isExpanded() )
			{
				btn->setExpanded( false );
			}
			m_mapButtons[ btn->getDate().hash() ] = btn;
		}
	}

	Glib::DateTime now = Glib::DateTime::create_now_local();
	auto iter = m_mapButtons.find( Glib::DateTime::create_local(
				now.get_year(), now.get_month(), now.get_day_of_month(),
				0, 0, 0.0 ).hash() );
	if( iter != m_mapButtons.end() )
	{
		iter->second->setExpanded( true );
	}
}

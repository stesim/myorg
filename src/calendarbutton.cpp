#include "calendarbutton.h"
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include "noteeditor.h"

CalendarButton::CalendarButton()
	: Glib::ObjectBase( "CalendarButton" ),
	Gtk::Box( Gtk::ORIENTATION_VERTICAL ),
	m_pNotes( nullptr ), m_Date( Glib::DateTime::create_now_local() ),
	m_pButton( Gtk::manage( new Gtk::Button() ) ),
	m_pBox( Gtk::manage( new Gtk::Box( Gtk::ORIENTATION_VERTICAL ) ) ),
	m_bHasNotes( false )
{
	m_pButton->set_alignment( 0.0f, 0.5f );
	m_pButton->signal_clicked().connect(
			sigc::mem_fun( *this, &CalendarButton::buttonClicked ) );

	pack_start( *m_pButton, Gtk::PACK_SHRINK );
}

CalendarButton::~CalendarButton()
{
}

NoteCollection* CalendarButton::getNotes() const
{
	return m_pNotes;
}

void CalendarButton::setNotes( NoteCollection* notes )
{
	m_pNotes = notes;
}

const Glib::DateTime& CalendarButton::getDate() const
{
	return m_Date;
}

void CalendarButton::setDate( const Glib::DateTime& date )
{
	if( date.compare( m_Date ) != 0 )
	{
		m_Date = date;

		m_pButton->set_label( m_Date.format( "%d %A" ) );

		Glib::RefPtr<Gtk::StyleContext> ctx = m_pButton->get_style_context();
		bool hasWeekendClass = ctx->has_class( "weekend" );
		if( m_Date.get_day_of_week() >= 6 )
		{
			if( !hasWeekendClass )
			{
				ctx->add_class( "weekend" );
			}
		}
		else if( hasWeekendClass )
		{
			ctx->remove_class( "weekend" );
		}

		ctx = get_style_context();
		Glib::DateTime now = Glib::DateTime::create_now_local();
		bool isToday = ( date.get_year() == now.get_year() &&
				date.get_month() == now.get_month() &&
				date.get_day_of_month() == now.get_day_of_month() );
		bool hasTodayClass = ctx->has_class( "today" );
		if( isToday )
		{
			if( !hasTodayClass )
			{
				ctx->add_class( "today" );
			}
		}
		else if( hasTodayClass )
		{
			ctx->remove_class( "today" );
		}
	}
}

void CalendarButton::updateNotes()
{
	std::vector<Widget*> children = m_pBox->get_children();
	for( int i = children.size() - 1; i >= 0; --i )
	{
		m_pBox->remove( *children[ i ] );
	}

	if( m_pNotes != nullptr )
	{
		unsigned int first;
		unsigned int last;
		m_bHasNotes = m_pNotes->getNotesByDate( m_Date, first, last );

		if( m_bHasNotes )
		{
			m_pButton->get_style_context()->add_class( "note" );

			for( unsigned int i = first; i <= last; ++i )
			{
				Note& note = m_pNotes->getNote( i );
				
				Gtk::Button* btn = Gtk::manage( new Gtk::Button() );
				btn->set_label( note.getTitle() );
				btn->signal_clicked().connect( sigc::bind( sigc::mem_fun(
								*this, &CalendarButton::noteClicked ),
							&note ) );

				m_pBox->pack_start( *btn, Gtk::PACK_SHRINK );
			}
		}
	}
	else
	{
		m_bHasNotes = false;
	}
}

bool CalendarButton::isExpanded() const
{
	return m_pBox->is_visible();
}

void CalendarButton::setExpanded( bool expanded )
{
	if( !m_bHasNotes )
	{
		return;
	}

	if( m_pBox->get_parent() == nullptr && expanded )
	{
		pack_start( *m_pBox, Gtk::PACK_SHRINK );
		if( is_visible() )
		{
			m_pBox->show_all();
		}

		get_style_context()->add_class( "expanded" );
		return;
	}

	if( expanded )
	{
		get_style_context()->add_class( "expanded" );
	}
	else
	{
		get_style_context()->remove_class( "expanded" );
	}

	m_pBox->set_visible( expanded );
}

void CalendarButton::buttonClicked()
{
	setExpanded( !isExpanded() );
}

void CalendarButton::noteClicked( Note* note )
{
	NoteEditor* editor = new NoteEditor();
	editor->setNote( note );
	editor->show_all();
}

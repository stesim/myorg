#include <iostream>
#include <gtkmm.h>
#include "transparentwindow.h"
#include "yearview.h"

TransparentWindow* win;
Glib::RefPtr<Gtk::CssProvider> css;
Glib::RefPtr<Gdk::Screen> screen;

void clicked()
{
	css->load_from_path( "style.css" );
}

bool buttonReleased( GdkEventButton* evt )
{
	if( evt->button == 2 )
	{
		if( ( evt->state & Gdk::SHIFT_MASK ) != 0 )
		{
			win->close();
		}
		else
		{
			clicked();
		}
	}
	return false;
}

#include <glibmm/datetime.h>

int main( int argc, char* argv[] )
{
	Glib::RefPtr<Gtk::Application> app =
		Gtk::Application::create( argc, argv, "org.gtkmm.examples.base" );

	TransparentWindow window;
	win = &window;
	window.set_type_hint( Gdk::WINDOW_TYPE_HINT_DOCK );
	window.set_keep_below( true );
	window.set_decorated( false );
	window.set_default_size( 200, 200 );
	window.maximize();

	screen = window.get_screen();
	gtk_widget_set_visual( GTK_WIDGET( window.gobj() ),
			screen->get_rgba_visual()->gobj() );

	css = Gtk::CssProvider::create();
	css->load_from_path( "style.css" );
	Gtk::StyleContext::add_provider_for_screen( screen, css,
			GTK_STYLE_PROVIDER_PRIORITY_APPLICATION );

	NoteCollection notes;
	notes.addNote( *new Note( "Silverstone", "6 Hours of Silverstone",
			Glib::DateTime::create_local( 2014, 4, 20, 0, 0, 0.0 ) ) );
	notes.addNote( *new Note( "Spa", "6 Hours of Spa-Francorchamps",
			Glib::DateTime::create_local( 2014, 5, 3, 0, 0, 0.0 ) ) );

	notes.addNote( *new Note( "Today", "is now!",
			Glib::DateTime::create_now_local() ) );

	notes.addNote( *new Note( "Pre-Alpha",
				"is a state myorg isn't in have yet." ) );

	YearView view;
	view.setNotes( &notes );
	view.updateNotes();

	window.add( view );
	window.show_all();

	window.get_window()->set_events( Gdk::BUTTON_RELEASE_MASK );
	window.signal_button_release_event().connect(
			sigc::ptr_fun( buttonReleased ) );
	
	return app->run(window);
}

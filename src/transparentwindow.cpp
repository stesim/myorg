#include "transparentwindow.h"

TransparentWindow::TransparentWindow()
	: Glib::ObjectBase( "TransparentWindow" )
{
	set_app_paintable( true );
	//window.signal_draw().connect( sigc::ptr_fun( onDraw ) );
}

TransparentWindow::~TransparentWindow()
{
}

bool TransparentWindow::on_draw( const Cairo::RefPtr<Cairo::Context>& cr )
{
	cr->set_source_rgba( 0.0, 0.0, 0.0, 0.5 );
	cr->set_operator( Cairo::OPERATOR_SOURCE );
	cr->paint();

	return Gtk::Window::on_draw( cr );
}

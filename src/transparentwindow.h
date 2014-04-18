#pragma once

#include <gtkmm/window.h>

class TransparentWindow : public Gtk::Window
{
public:
	TransparentWindow();
	virtual ~TransparentWindow();

	virtual bool on_draw( const Cairo::RefPtr<Cairo::Context>& cr ) override;
};

#pragma once

#include "note.h"
#include <vector>

class NoteCollection
{
public:
	NoteCollection();
	virtual ~NoteCollection();

	void addNote( Note& note );

	void removeNote( Note& note );
	void removeNote( unsigned int index );

	Note& getNote( unsigned int index ) const;

	unsigned int getNumNotes() const;
	
	bool getGeneralNotes( unsigned int& first, unsigned int& last ) const;

	bool getNotesByDate( const Glib::DateTime& date, unsigned int& first,
			unsigned int& last ) const;

private:
	inline static int compareDates( const Glib::DateTime& a,
			const Glib::DateTime& b );

private:
	std::vector<Note*> m_vecNotes;
	std::vector<Note*> m_vecGeneralNotes;
};

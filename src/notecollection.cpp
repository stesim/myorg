#include "notecollection.h"

NoteCollection::NoteCollection()
{
}

NoteCollection::~NoteCollection()
{
}

void NoteCollection::addNote( Note& note )
{
	if( note.hasDate() )
	{
		const Glib::DateTime& date = note.getDate();

		if( m_vecNotes.empty() ||
				date.compare( m_vecNotes.back()->getDate() ) >= 0 )
		{
			m_vecNotes.push_back( &note );
			return;
		}
		else if( date.compare( m_vecNotes.front()->getDate() ) <= 0 )
		{
			m_vecNotes.insert( m_vecNotes.begin(), &note );
			return;
		}

		unsigned int left = 0;
		unsigned int right = m_vecNotes.size() - 1;

		while( right - left > 1 )
		{
			unsigned int mid = ( right + left ) / 2;
			int diffMid = date.compare( m_vecNotes[ mid ]->getDate() );
			if( diffMid > 0 )
			{
				left = mid;
			}
			else
			{
				right = mid;
			}
		}

		m_vecNotes.insert( m_vecNotes.begin() + right, &note );
	}
	else
	{
		m_vecGeneralNotes.push_back( &note );
	}
}

void NoteCollection::removeNote( Note& note )
{
	for( unsigned int i = 0; i < m_vecNotes.size(); ++i )
	{
		if( m_vecNotes[ i ] == &note )
		{
			m_vecNotes.erase( m_vecNotes.begin() + i );
			return;
		}
	}
	for( unsigned int i = 0; i < m_vecGeneralNotes.size(); ++i )
	{
		if( m_vecGeneralNotes[ i ] == &note )
		{
			m_vecGeneralNotes.erase( m_vecGeneralNotes.begin() + i );
			return;
		}
	}
}

void NoteCollection::removeNote( unsigned int index )
{
	if( index < m_vecNotes.size() )
	{
		m_vecNotes.erase( m_vecNotes.begin() + index );
	}
	else
	{
		m_vecGeneralNotes.erase( m_vecGeneralNotes.begin() + ( index -
				m_vecNotes.size() ) );
	}
}

Note& NoteCollection::getNote( unsigned int index ) const
{
	return *( index < m_vecNotes.size() ?
			m_vecNotes[ index ] :
			m_vecGeneralNotes[ index - m_vecNotes.size() ] );
}

unsigned int NoteCollection::getNumNotes() const
{
	return ( m_vecGeneralNotes.size() + m_vecNotes.size() );
}

bool NoteCollection::getGeneralNotes( unsigned int& first,
		unsigned int& last ) const
{
	if( !m_vecNotes.empty() )
	{
		first = m_vecNotes.size();
		last = getNumNotes() - 1;
		return true;
	}
	return false;
}

bool NoteCollection::getNotesByDate( const Glib::DateTime& date,
		unsigned int& first, unsigned int& last ) const
{
	if( m_vecNotes.empty() ||
			compareDates( date, m_vecNotes.front()->getDate() ) < 0 ||
			compareDates( date, m_vecNotes.back()->getDate() ) > 0 )
	{
		return false;
	}

	unsigned int left;
	unsigned int right;
	
	if( compareDates( date, m_vecNotes.front()->getDate() ) == 0 )
	{
		first = 0;
	}
	else
	{
		left = 0;
		right = m_vecNotes.size() - 1;

		while( right - left > 1 )
		{
			unsigned int mid = ( right + left ) / 2;
			int diffMid = compareDates( m_vecNotes[ mid ]->getDate(), date );
			if( diffMid < 0 )
			{
				left = mid;
			}
			else
			{
				right = mid;
			}
		}

		if( compareDates( date, m_vecNotes[ right ]->getDate() ) != 0 )
		{
			return false;
		}
		else
		{
			first = right;
		}
	}

	if( compareDates( date, m_vecNotes.back()->getDate() ) == 0 )
	{
		last = m_vecNotes.size() - 1;
	}
	else
	{
		left = 0;
		right = m_vecNotes.size() - 1;

		while( right - left > 1 )
		{
			unsigned int mid = ( right + left ) / 2;
			int diffMid = compareDates( m_vecNotes[ mid ]->getDate(), date );
			if( diffMid > 0 )
			{
				right = mid;
			}
			else
			{
				left = mid;
			}
		}

		last = left;
	}
	return true;
}

int NoteCollection::compareDates( const Glib::DateTime& a,
		const Glib::DateTime& b )
{
	int yearA = a.get_year();
	int yearB = b.get_year();
	if( yearA == yearB )
	{
		int dayA = a.get_day_of_year();
		int dayB = b.get_day_of_year();
		if( dayA == dayB )
		{
			return 0;
		}
		else if( dayA > dayB )
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else if( yearA > yearB )
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

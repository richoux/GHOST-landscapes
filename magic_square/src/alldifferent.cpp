#include <cmath>
#include <algorithm>
#include <iostream>

#include "alldifferent.hpp"

double AllDifferent::binomial_with_2( int value ) const
{
	if( value <= 1 )
		return 0;
	
	if( value % 2 == 0 )
		return static_cast<double>( value - 1 ) * ( value / 2 );
	else
		return static_cast<double>( value ) * ( ( value - 1 ) / 2 );
}


AllDifferent::AllDifferent( const std::vector<int>& variables_index )
	: ghost::Constraint( variables_index )
{ }

AllDifferent::AllDifferent( const std::vector<ghost::Variable>& variables )
	: ghost::Constraint( variables )
{ }

// SOFT_ALLDIFF error function (Petit et al. 2001)
double AllDifferent::required_error( const std::vector<ghost::Variable*>& variables ) const
{
	double counter = 0;
	_count.clear();
	
	for( auto v : variables )
		if( _count.find( v->get_value() ) == _count.end() )
			_count[ v->get_value() ] = 1;
		else
			_count[ v->get_value() ] = _count[ v->get_value() ] + 1;
	
	for( const auto& [key, value] : _count )
		if( value > 1 )
			counter += binomial_with_2( value );

	return counter;
}

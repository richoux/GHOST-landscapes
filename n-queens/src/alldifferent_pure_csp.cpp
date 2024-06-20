#include <cmath>
#include <algorithm>
#include <iostream>

#include "alldifferent_pure_csp.hpp"

AllDifferentPureCSP::AllDifferentPureCSP( const std::vector<int>& variables_index )
	: ghost::Constraint( variables_index )
{ }

AllDifferentPureCSP::AllDifferentPureCSP( const std::vector<ghost::Variable>& variables )
	: ghost::Constraint( variables )
{ }

double AllDifferentPureCSP::required_error( const std::vector<ghost::Variable*>& variables ) const
{
	_count.clear();
	
	for( auto v : variables )
		if( _count.find( v->get_value() ) == _count.end() )
			_count[ v->get_value() ] = 1;
		else
			return 1.;
	
	return 0.;
}

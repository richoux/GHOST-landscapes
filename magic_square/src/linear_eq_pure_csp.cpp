#include <cmath>
#include <algorithm>
#include <iostream>

#include "linear_eq_pure_csp.hpp"

LinearEqPureCSP::LinearEqPureCSP( const std::vector<int>& variables_index, double rhs )
	: Constraint( variables_index ),
	  _rhs( rhs )
{ }

LinearEqPureCSP::LinearEqPureCSP( const std::vector<ghost::Variable>& variables, double rhs )
	: Constraint( variables ),
	  _rhs( rhs )
{ }

double LinearEqPureCSP::required_error( const std::vector<ghost::Variable*>& variables ) const
{
	_current_sum = 0.0;
	for( size_t i = 0 ; i < variables.size() ; ++i )
		_current_sum += variables[i]->get_value();

	if( _current_sum == _rhs )
		return 0.;
	else
		return 1.;
}

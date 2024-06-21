#pragma once

#include <vector>

#include <ghost/constraint.hpp>
#include <ghost/variable.hpp>

class LinearEq : public ghost::Constraint
{
	mutable double _current_sum;
	double _rhs;
	
public:
	
	LinearEq( const std::vector<int>& variables_index, double rhs );
	LinearEq( const std::vector<ghost::Variable>& variables, double rhs );
	
	double required_error( const std::vector<ghost::Variable*>& variables ) const override;
};

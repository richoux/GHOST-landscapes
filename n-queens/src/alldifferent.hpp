#pragma once

#include <vector>
#include <map>

#include <ghost/constraint.hpp>
#include <ghost/variable.hpp>

class AllDifferent : public ghost::Constraint
{
	mutable std::map<int,int> _count;
	
	double required_error( const std::vector<ghost::Variable*>& variables ) const override;
	
	double binomial_with_2( int value ) const;
	
public:
	AllDifferent( const std::vector<int>& variables_index );
	AllDifferent( const std::vector<ghost::Variable>& variables );
};

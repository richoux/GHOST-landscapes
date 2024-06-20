#pragma once

#include <vector>
#include <map>

#include <ghost/constraint.hpp>
#include <ghost/variable.hpp>

class AllDifferentPureCSP : public ghost::Constraint
{
	mutable std::map<int,int> _count;
	
	double required_error( const std::vector<ghost::Variable*>& variables ) const override;
	
public:
	AllDifferentPureCSP( const std::vector<int>& variables_index );
	AllDifferentPureCSP( const std::vector<ghost::Variable>& variables );
};

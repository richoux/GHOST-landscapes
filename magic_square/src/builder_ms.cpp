#if defined PURE_CSP
#include "linear_eq_pure_csp.hpp"
#include "alldifferent_pure_csp.hpp"
#else
#include "linear_eq.hpp"
#include "alldifferent.hpp"
#endif

#include "builder_ms.hpp"

BuilderMagicSquare::BuilderMagicSquare( int instance_size )
	: ghost::ModelBuilder(),
	  _instance_size( instance_size ),
	  _nb_vars( instance_size * instance_size),
	  _constant( instance_size * ( _nb_vars + 1 ) / 2 ),
	  _rows( std::vector< std::vector<int> >( instance_size ) ),
	  _columns( std::vector< std::vector<int> >( instance_size ) ),
	  _diagonals( std::vector< std::vector<int> >( 2 ) )	  
{
	// Prepare row variables
  for( int row = 0; row < _instance_size; ++row )
	  for( int i = 0 ; i < _instance_size ; ++i )
		  _rows[row].push_back( i + ( row * _instance_size ) );
  
  // Prepare column variables
  for( int col = 0; col < _instance_size; ++col )
	  for( int row = 0; row < _instance_size; ++row )
		  _columns[ col ].push_back( col + ( row * _instance_size ) );
	  
  // Prepare square variables
  for( int row = 0; row < _instance_size; ++row )
  {
	  _diagonals[ 0 ].push_back( row + ( row * _instance_size ) );
	  _diagonals[ 1 ].push_back( _instance_size - 1 - row + ( row * _instance_size ) );
  }
}

void BuilderMagicSquare::declare_variables()
{
  // Create variables, with domains starting from value 1
	create_n_variables( _nb_vars, 1, _nb_vars );
	
	// for( int i = 0; i < _nb_vars; ++i )
	// 	variables[i].set_value( i + 1 );
}

void BuilderMagicSquare::declare_constraints()
{
#if defined PURE_CSP
	constraints.emplace_back( std::make_shared<AllDifferentPureCSP>( variables ) );
#else
	constraints.emplace_back( std::make_shared<AllDifferent>( variables ) );
#endif
	
	for( int i = 0; i < _instance_size; ++i )
  {
#if defined PURE_CSP
	  constraints.emplace_back( std::make_shared<LinearEqPureCSP>( _rows[i], _constant ) );
	  constraints.emplace_back( std::make_shared<LinearEqPureCSP>( _columns[i], _constant ) );
#else
	  constraints.emplace_back( std::make_shared<LinearEq>( _rows[i], _constant ) );
	  constraints.emplace_back( std::make_shared<LinearEq>( _columns[i], _constant ) );
#endif
  }
  
#if defined PURE_CSP
	constraints.emplace_back( std::make_shared<LinearEqPureCSP>( _diagonals[0], _constant ) );
	constraints.emplace_back( std::make_shared<LinearEqPureCSP>( _diagonals[1], _constant ) );
#else
	constraints.emplace_back( std::make_shared<LinearEq>( _diagonals[0], _constant ) );
	constraints.emplace_back( std::make_shared<LinearEq>( _diagonals[1], _constant ) );
#endif
}

#if defined MINMS
void BuilderMagicSquare::declare_objective()
{
	objective = std::make_shared<MinCorners>( variables );
}
#endif

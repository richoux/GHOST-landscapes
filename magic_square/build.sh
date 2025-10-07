#!/bin/bash

make clean
make MYFLAGS=-DGHOST_RANDOM_WALK
mv bin/magic_square_efcsp bin/magic_square_efcsp_random_walk
mv bin/magic_square_csp bin/magic_square_csp_random_walk

make clean
make MYFLAGS=-DGHOST_HILL_CLIMBING
mv bin/magic_square_efcsp bin/magic_square_efcsp_hill_climbing
mv bin/magic_square_csp bin/magic_square_csp_hill_climbing


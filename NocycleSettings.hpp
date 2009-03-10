//
//  NocycleSettings.hpp - Until a build system with CMake or such gets 
//     set up, this is a centralization of the flags for conditional
//     compilation of the Nocycle library...mostly to do with debug
//     code.  Although the boost library is needed for much of the
//     testing, if you aren't doing a test build then it should not
//     be necessary to include any boost libraries (at least, not yet).
//
//  Copyright (c) 2009 HostileFork.com
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://hostilefork.com/nocycle for documentation.
//

#pragma once
#ifndef NOCYCLESETTINGS_HPP
#define NOCYCLESETTINGS_HPP

// Note: Regarding the debate of whether to use #define/#undef and #ifdef or 
// to use #define 0/1 and #if, I'm in the latter camp.  For rationale:
// http://stackoverflow.com/questions/135069/ifdef-vs-if-which-is-bettersafer

// Several pieces of Nocycle have self testing code.  These tests may rely
// on the boost library.  If you would like to build a version of Nocycle
// without a dependency on boost, make sure all these are set to 0.
#define NSTATE_SELFTEST 1
#define ORIENTEDGRAPH_SELFTEST 1
#define DIRECTEDACYCLICGRAPH_SELFTEST 1

// Though nocycle distinguishes between vertices that have no connections
// and those which "don't exist", boost's default assumption is that 
// all nodes in its capacity "exist".  The only way to conceptually delete 
// a boost vertex from its enclosing graph it is to remove all of its
// incoming and outgoing connections.  Though it is possible to inject
// a vertex property map to track existence, the property map adds overhead
// and may not fairly represent boost's performance in scenarios with
// large numbers of nodes when existence tracking is not needed.
#define BOOSTIMPLEMENTATION_TRACK_EXISTENCE 0

// Asserts are known to slow down the debug build.  But sometimes, you
// want to have the debug information available while still not having
// assertions run...e.g. so you can pause to see where execution is
// getting held up (a kind of poor-man's profiling).
#define DEACTIVATE_ASSERT 1
#if DEACTIVATE_ASSERT
#define nocycle_assert(expr) ((void)0)
#else
#define nocycle_assert(expr) assert(expr)
#endif

// There is an "extra tristate" we get in the canreach graph when there is a physical
// edge in the data graph.  We can use this to accelerate the invalidation process,
// but for testing purposes it's nice to make sure the algorithms aren't corrupting
// this implicitly when modifying other edges.
#define DIRECTEDACYCLICGRAPH_USER_TRISTATE 1

// If 1, then perform heavy consistency checks on the transitive closure sidestructure
// If 0, don't do the checks.
#define DIRECTEDACYCLICGRAPH_CONSISTENCY_CHECK 0

#endif
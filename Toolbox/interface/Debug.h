/* Copyright (c) 2010 - All Rights Reserved
 *   Fred Stober <stober@cern.ch>
 */

#ifndef TBDEBUG_H
#define TBDEBUG_H

#ifdef DEBUG
#include <iostream>
#define DEBUGMSG() { std::cerr << __FILE__ << ":" << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl; }
#else
#define DEBUGMSG() {}
#endif

#endif

#ifndef OSSELECTOR_HPP
#define OSSELECTOR_HPP

#ifdef __linux__
#include "EpollManager.hpp"
typedef EpollManager EventManager;
#elif defined(__APPLE__)
#include "KqueueManager.hpp"
typedef KqueueManager EventManager;
#endif

#endif  // OSSELECTOR_HPP

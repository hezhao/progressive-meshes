/************************************************************************

  MxTimer

  Copyright (C) 1998 Michael Garland.  See "COPYING.txt" for details.
  
  $Id: MxTimer.cxx,v 1.3 1998/10/26 21:09:32 garland Exp $

 ************************************************************************/

#include "MxTimer.h"

#if defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Only Windows NT supports getting proper time usage information.
// In Windows 95, we have to settle for measuring real time.
double mx_get_time()
{
    FILETIME start, end, kernel, user;

    if( !GetThreadTimes(GetCurrentThread(), &start, &end, &kernel, &user) )
    {
	// We're running under Windows 95 instead of NT.
	// Just get the current time and be done with it.
	SYSTEMTIME now;
	GetSystemTime(&now);
	SystemTimeToFileTime(&now, &user);
    }

    // Convert into something we can do math on
    LARGE_INTEGER i;
    i.LowPart = user.dwLowDateTime;
    i.HighPart = user.dwHighDateTime;

    // Convert to seconds and return
    return (double)(i.QuadPart) / 1e7;
}

#elif defined(MIX_HAVE_GETRUSAGE)
#include <sys/time.h>
#include <sys/resource.h>

double mx_get_time()
{
    struct rusage t;

    getrusage(RUSAGE_SELF, &t);

    return (double)t.ru_utime.tv_sec + (double)t.ru_utime.tv_usec/1000000;
}

#elif defined(MIX_HAVE_TIMES)

double mx_get_time()
{
    struct tms t;

    times(&t);

    return (double)(t.tms_utime) / (double)CLK_TCK;
}

#else

#error "MxTimer: No supported timing mechanism available."

#endif

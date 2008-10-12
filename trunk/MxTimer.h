#ifndef MXTIMER_INCLUDED // -*- C++ -*-
#define MXTIMER_INCLUDED
#if !defined(__GNUC__)
#  pragma once
#endif

/************************************************************************

  MxTimer

  Copyright (C) 1998 Michael Garland.  See "COPYING.txt" for details.
  
  $Id: MxTimer.h,v 1.4 1998/10/26 21:09:32 garland Exp $

 ************************************************************************/

#define MXTIME(t, cmd) { t=mx_get_time(); cmd; t=mx_get_time() - t; }

extern double mx_get_time();

// MXTIMER_INCLUDED
#endif

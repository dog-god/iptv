/*
 * Copyright (C) 2012 armite@126.com
 */

#include "config.h"
#include "SharedTimer.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"

#include <wtf/Assertions.h>
#include <wtf/CurrentTime.h>
#include <wtf/MainThread.h>

namespace WebCore {

static int _sheredTimerCount = 0;
static double _nextTimerFireTime = 0.0;

static void (*_timerFunction)();

void setSharedTimerFiredFunction(void (*func)())
{
    _timerFunction = func;
}

void fireSharedTimerFunction(void)
{
    if (_sheredTimerCount > 0 && _timerFunction){
        _sheredTimerCount--;
        _timerFunction();
    }
}

void stopSharedTimer()
{
    if(_sheredTimerCount > 0)
        _sheredTimerCount--;
}

void setSharedTimerFireInterval(double fireTime)
{
    _sheredTimerCount++;
    if (_nextTimerFireTime > fireTime)
        _nextTimerFireTime = fireTime;
}

double getSharedTimerFireTime()
{
    if(_sheredTimerCount > 0)
        return _nextTimerFireTime;

    return 1.0;
}

}




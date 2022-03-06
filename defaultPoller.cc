// can modify in this file if add some new I/O multiplexing

#include "Poller.h"
#include "EPollPoller.h"


Poller* Poller::newDefaultPoller(EventLoop* loop) {
    if (::getenv("NAIVE_USE_POLL")) {
        return nullptr;
    } else {
        return new EPollPoller(loop);
    }
}


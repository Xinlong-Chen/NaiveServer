#include "Poller.h"

#include "Channel.h"

Poller::Poller(EventLoop* loop)
    : ownerLoop_(loop) {
}

Poller::~Poller() = default;

bool Poller::hasChannel(Channel* channel) const {
    ChannelMap::const_iterator it = channels_.find(channel->fd());
    return it != channels_.end() && it->second == channel;
}

// for oop design, the function Poller::newDefaultPoller doesn't implement in there
// Design principle : Open for extensions, closed for modifications
// newDefaultPoller implement in defaultPoller

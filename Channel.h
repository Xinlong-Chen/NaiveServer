#pragma once

#include "noncopyable.h"

#include <memory>
#include <functional>

#include "Timestamp.h"

class EventLoop;


class Channel : noncopyable {
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop *loop, int fd);
    ~Channel();

    // call callback function according to event type
    void handleEvent(Timestamp recieveTime);

    // set callback function
    void setReadCallback(ReadEventCallback cb) { readCallback_  = std::move(cb); }
    void setWriteCallback(EventCallback cb)    { writeCallback_ = std::move(cb); }
    void setCloseCallback(EventCallback cb)    { closeCallback_ = std::move(cb); }
    void setErrorCallback(EventCallback cb)    { errorCallback_ = std::move(cb); }
    
    // if channel is removed, channel can't exec callback function
    void tie(const std::shared_ptr<void>&);

    int fd() const { return fd_; }
    int events() const { return events_; }
    void set_revents(int revt) { revents_ = revt; }

    void enableReading()   { events_ |= kReadEvent;   update(); }
    void disableReading()  { events_ &= ~kReadEvent;  update(); }
    void enableWriteing()  { events_ |= kWriteEvent;  update(); }
    void disableWriteing() { events_ &= ~kWriteEvent; update(); }
    void disbaleAll()      { events_ = kNodeEvent;    update(); }

    bool isNoneEvent() const { return events_ == kNodeEvent; }
    bool isReading() const   { return events_ & kReadEvent;  }
    bool isWriting() const   { return events_ & kWriteEvent; }

    int index() { return index_; }
    void set_index(int idx) { index_ = idx; }

    // one loop per thread
    EventLoop* ownerLoop() { return loop_; }
    void remove();

private:

    void update();
    void handleEventWithGuard(Timestamp recieveTime);

    static const int kNodeEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;
    const int fd_;
    int events_;
    int revents_;
    int index_;

    std::weak_ptr<void> tie_;
    bool tied_;

    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};

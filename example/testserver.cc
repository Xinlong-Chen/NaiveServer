#include <naiveserver/TcpServer.h>
#include <naiveserver/Logger.h>

#include <string>
#include <functional>

class EchoServer
{
public:
    EchoServer(EventLoop *loop,
            const InetAddress &addr, 
            const std::string &name)
        : server_(loop, addr, name)
        , loop_(loop)
    {
        server_.setConnectionCallback(
            std::bind(&EchoServer::onConnection, this, std::placeholders::_1)
        );

        server_.setMessageCallback(
            std::bind(&EchoServer::onMessage, this,
                std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
        );

        server_.setThreadNum(3);
    }
    void start()
    {
        server_.start();
    }
private:
    void onConnection(const TcpConnectionPtr &conn)
    {
        if (conn->connected())
        {
            LOG_INFO("Connection UP : %s", conn->peerAddress().toIpPort().c_str());
        }
        else
        {
            LOG_INFO("Connection DOWN : %s", conn->peerAddress().toIpPort().c_str());
        }
    }

    void onMessage(const TcpConnectionPtr &conn,
                Buffer *buf,
                Timestamp time)
    {
        std::string msg = buf->retrieveAllAsString();
        conn->send(msg);
        conn->shutdown(); //  EPOLLHUP => closeCallback_
    }

    EventLoop *loop_;
    TcpServer server_;
};

int main()
{
    // main loop
    EventLoop loop;
    InetAddress addr(8000);
    // create Acceptor ( non-blocking listenfd create & bind)
    EchoServer server(&loop, addr, "EchoServer-01"); 
    // create sub-loop, sub-loop begin
    server.start(); 
    // mainLoop's Poller begin
    loop.loop(); 

    return 0;
}
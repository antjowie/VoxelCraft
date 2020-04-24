#pragma once
#include "common/event/Event.hpp"

#include "net/Address.hpp"
#include "net/packet/Packet.hpp"
#include "net/ServerLayer.hpp"

class NetEvent : public Event
{
public:
    EVENT_CLASS_CATEGORY(EventCategory::Net)
};

class NetConnectEvent : public NetEvent
{
public:
    NetConnectEvent(Address server, const char* name) 
        : server(server)
        , name(name) {}

    Address server;
    const char* name;

    EVENT_CLASS_TYPE(EventType::NetConnect)
};

class NetConnectResponseEvent : public NetEvent
{
public:
    enum class Status
    {
        Success,
        Failed
    } status;

    NetConnectResponseEvent(Status status)
        : status(status) {}

    EVENT_CLASS_TYPE(EventType::NetConnectResponse)
};

class NetDisconnectEvent : public NetEvent
{
public:
    EVENT_CLASS_TYPE(EventType::NetDisconnect)
};

/**
 * Using these kinds of events give us multiple ways to host a server or shut one down
 * We could make it so advanced that we have an http server that we can send a request to.
 * Our http server will then dispatch a NetHostEvent event so you can start a server from 
 * a phone. It's really stupid but cool.
 */
class NetHostEvent : public NetEvent
{
public:
    NetHostEvent(ServerLayer::Config conf) : config(conf) {}
    ServerLayer::Config config;

    EVENT_CLASS_TYPE(EventType::NetHost)
};

class NetHostResponseEvent : public NetEvent
{
public:
    enum class Status
    {
        Success,
        Failed
    } status;

    NetHostResponseEvent(Status status) : status(status) {}

    EVENT_CLASS_TYPE(EventType::NetHostResponse)
};

class NetShutdownEvent : public NetEvent
{
public:
    EVENT_CLASS_TYPE(EventType::NetShutdown)
};

class NetPacketSendEvent : public NetEvent
{
public:
    NetPacketSendEvent(const Packet& packet) : packet(packet) {}
    Packet packet;

    EVENT_CLASS_TYPE(EventType::NetPacketSend)
};

class NetPacketReceiveEvent : public NetEvent
{
public:
    NetPacketReceiveEvent(const Packet& packet) : packet(packet) {}
    Packet packet;

    EVENT_CLASS_TYPE(EventType::NetPacketReceive)
};
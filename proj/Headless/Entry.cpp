#include "common/Application.hpp"

#include "net/ServerLayer.hpp"
#include "net/ClientLayer.hpp"

#include <iostream>
#include <thread>

class Game : public Layer
{
private:
    virtual void OnInit() override final
    {
        Address server;
        server.ip = sf::IpAddress::LocalHost;
        server.port = 25565;
        Publish(NetConnectEvent(server,"VoxelCraft"));
    }

    virtual void OnNotify(Event& e) override final
    {
        EventDispatcher d(e);
        d.Dispatch<NetConnectResponseEvent>([&](NetConnectResponseEvent& e)
            {
                if (e.status == NetConnectResponseEvent::Status::Success)
                {
                    std::cin.ignore();
                    m_game = std::thread([&]()
                        {
                            bool quit = false;
                            while (!quit)
                            {
                                std::string msg;
                                std::getline(std::cin, msg);

                                if (msg == "/q")
                                    quit = true;
                                Publish(NetMessageEvent(msg));
                            }
                            Exit();
                        });
                }
                else
                {
                    std::cout << "Retry...\n";
                    Address server;
                    server.ip = sf::IpAddress::LocalHost;
                    server.port = 25565;
                    Publish(NetConnectEvent(server, "VoxelCraft"));
                }
            });
    }

    virtual void OnDeinit() override final
    {
        if(m_game.joinable()) m_game.join();
    }

    std::thread m_game;
};

class Headless : public Layer
{
private:
    virtual void OnInit() override final
    {
        ServerLayer::Config conf;
        conf.address.ip = sf::IpAddress::LocalHost;
        conf.address.port = 25565;

        Publish(NetHostEvent(conf));
    }

    virtual void OnNotify(Event& e) override final
    {
        EventDispatcher d(e);
        d.Dispatch<NetHostResponseEvent>([&](NetHostResponseEvent& e)
            {
                if (e.status == NetHostResponseEvent::Status::Success)
                {
                    m_t = std::thread([&]()
                        {
                            bool quit = false;
                            std::cin.ignore();
                            while (!quit)
                            {
                                std::string msg;
                                std::getline(std::cin, msg);

                                if (msg == "/q")
                                    quit = true;
                                Publish(NetMessageEvent(msg));
                            }
                            Publish(NetShutdownEvent());
                            Exit();
                        });
                }
                else
                {
                    std::cout << "Could not start up server\n";
                    Exit();
                }
            });
    }

    virtual void OnDeinit() override final
    {
        if (m_t.joinable()) m_t.join();
    }

    std::thread m_t;
};

void CreateApplication(Application::Layers& layers)
{
    std::cout << "0 server 1 client\n";

    int i;
    std::cin >> i;
    if (i == 0)
    {
        layers.push_back(std::make_unique<ServerLayer>());
        layers.push_back(std::make_unique<Headless>());
    }
    else
    {
        layers.push_back(std::make_unique<ClientLayer>());
        layers.push_back(std::make_unique<Game>());
    }
}
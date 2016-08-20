#include <stdio.h>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

#ifndef NETFIGHT_H
#define NETFIGHT_H 1

typedef struct {
	TCPsocket Sock;
	std::string Name;
	int ID;
	bool quit = true;
} Client;

class NetFight {
private:
    int MaxClient;
    IPaddress IP;
    bool isServer;
    TCPsocket ServerSocket;
    Uint32 ipAddr;
    Uint16 Port;
    SDLNet_SocketSet SocketSet;
    std::vector<Client> Clients;
    std::string Host;
public:
     std::vector<std::string> Buffer;
private:
    int AddClient( std::string Name, int ID, TCPsocket Sock);
    bool CheckClient( std::string Name);
    Client *GetClient( std::string Name);
    int DeleteClient( std::string Name);
public:
    NetFight(); // Grundstruktur
    ~NetFight(); // löschen der restlichen daten
    int Connect( std::string sIP = "localhost", int Port = 5219);
    int StartServer( int Port = 5219);
    int SetMaxClients( int iClients);
    bool isNameValid( std::string const &str);
    void CreateSocketSet();
    int SendMsg( TCPsocket Socket, std::string Msg);
    std::string GetMsg(TCPsocket Socket);
    void Process();
};

#endif // NETFIGHT_H

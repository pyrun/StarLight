#include "NetNight.hpp"


void print(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    printf( "\n");
}

NetFight::NetFight() {
    isServer = false; // Flag zurücksetzten
    // SDL Net starten
    if(SDLNet_Init()==-1) {
        print( "SDL Net error: %s", SDLNet_GetError());
        SDL_Quit();
        return;
    }
    // Grundwert
    MaxClient = 2;
}
NetFight::~NetFight() {
    if( isServer) {
        // Löschen der Clients
        for(int i = 0; i < (int)Clients.size(); i++) {
            DeleteClient( Clients[i].Name.c_str());
            i--;
        }
    } else {
        SendMsg( ServerSocket, "quit");
    }
    SDLNet_Quit();
}
int NetFight::AddClient( std::string Name, int ID, TCPsocket Sock) {
    if( isNameValid( Name) ) {
        SendMsg( Sock, "Falscher Name");
        print( "Username '%s'hat falsche zeichen drin(%d)", Name.c_str(), ID);
        SDLNet_TCP_Close( Sock);
        return -1;
    }
    if( CheckClient( Name) == true ) { // Check ob es vorhanden ist
        SendMsg( Sock, "User schon vorhanden. Anderen Name bitte wahlen");
        print( "Konnte Nutzer '%s' nicht erstellen, schon vorhanden(%d)", Name.c_str(), ID);
        SDLNet_TCP_Close( Sock);
        return -1;
    }
    SendMsg( Sock, "Sie sind verbunden");
    Client New;
    New.Name = Name;
    New.ID = ID;
    New.Sock = Sock;
    New.quit = false;
    Clients.push_back( New);
    print( "Client '%s' wurde hinzugefugt(%d)", Name.c_str(), ID);
    return ID;
}
bool NetFight::CheckClient( std::string Name) {
    for( int i = 0; i < (int)Clients.size(); i++)  // suche nach gleichen namen
        if( Clients[i].Name == Name)
            return true;
    return false;
}

Client *NetFight::GetClient( std::string Name) {
    for( int i = 0; i < (int)Clients.size(); i++)  // suche nach gleichen namen
        if( Clients[i].Name == Name)
            return &Clients[i];
    return NULL;
}
int NetFight::DeleteClient( std::string Name) {
    if( CheckClient( Name) == false ) { // check
        print( "Client mit dem Name '%s' nicht gefunden", Name.c_str());
        return 0;
    }
    int ID;
    for( int i = 0; i < (int)Clients.size(); i++)  {// suche nach gleichen namen
        if( Clients[i].Name == Name) {
            ID = Clients[i].ID; // Für rückgabe merken
            print( "User '%s' wurde erfolgreich geloscht(%d)", Clients[i].Name.c_str(), ID);
            Clients.erase( Clients.begin() + i); // einheit löschen
            break; // Schleife abbrechen
        }
    }
    return ID;
}
int NetFight::Connect( std::string sIP, int Port) {
    SocketSet = SDLNet_AllocSocketSet(1); // Platz für sich selbst
    if(!SocketSet) {
		print("SDLNet_AllocSocketSet: %s", SDLNet_GetError());
		return -1;
	}
    isServer = false; // Is a Client
    if(SDLNet_ResolveHost( &IP, sIP.c_str(), Port) == -1) {
		print("SDLNet_ResolveHost: %s",SDLNet_GetError());
		return -1;
	}
	ServerSocket = SDLNet_TCP_Open( &IP);
	if( !ServerSocket) {
		print("SDLNet_TCP_Open: %s",SDLNet_GetError());
		return -1;
	}
	if(SDLNet_TCP_AddSocket( SocketSet, ServerSocket)==-1) {
		print("SDLNet_TCP_AddSocket: %s",SDLNet_GetError());
		return -1;
	}
	SendMsg( ServerSocket, "TheNightAlex");
    return 0;
}
int NetFight::StartServer( int Port) {
    if(SDLNet_ResolveHost(&IP, NULL, Port) == -1) {
		print("SDLNet_ResolveHost: %s",SDLNet_GetError());
		SDLNet_Quit();
		return -1;
	}
	ipAddr=SDL_SwapBE32( IP.host);
	//
	Host = SDLNet_ResolveIP( &IP);
	// Öffne Socket
	ServerSocket = SDLNet_TCP_Open( &IP);
	if( !ServerSocket) {
        print( "SDLNet_TCP_Open: %s",SDLNet_GetError());
        return -2;
	}
	// Erstelle SocketSet
	CreateSocketSet();
	isServer = true;
	return 0;
}
int NetFight::SetMaxClients( int iClients) {
    MaxClient = iClients;
    return MaxClient;
}
bool NetFight::isNameValid( std::string const &str ) {
    return str.find_first_not_of("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos;
}
void NetFight::CreateSocketSet() {
	if( SocketSet ) // Fals socketSet vorhanden ist
		SDLNet_FreeSocketSet( SocketSet);
	SocketSet = SDLNet_AllocSocketSet( MaxClient+1); // Clients platz machen
	if(! SocketSet) {
		print("SDLNet_AllocSocketSet: %s", SDLNet_GetError());
		return; // Eigentlich sollte man das programm beenden aber YOLO!
	}
	SDLNet_TCP_AddSocket( SocketSet, ServerSocket);
	for( int i=0; i < (int)Clients.size(); i++)
		SDLNet_TCP_AddSocket( SocketSet, Clients[i].Sock);
}
int NetFight::SendMsg( TCPsocket Socket, std::string Msg) {
    int Length, Result;
	/* determine the length of the string */
	Length = strlen( Msg.c_str())+1; /* add one for the terminating NULL */
	// ändere die bitreihenfolge zu endianness (Network)
	Length = SDL_SwapBE32( Length );
	// Sende die länge des stringes
	Result = SDLNet_TCP_Send( Socket, &Length, sizeof(Length));
	if( Result < (int)sizeof( Length )) {
		if( SDLNet_GetError() && strlen(SDLNet_GetError())) // meinchmal leer
			print("SDLNet_TCP_Send: %s", SDLNet_GetError());
		return 0;
	}
	// bitreihenfolge wieder zurücksetzten
	Length = SDL_SwapBE32(Length);
	// Sendet die bufferreihenfolge
	Result = SDLNet_TCP_Send( Socket, Msg.c_str(), Length);
	if( Result < Length) {
		if(SDLNet_GetError() && strlen(SDLNet_GetError())) // meichmal leer
			print("SDLNet_TCP_Send: %s", SDLNet_GetError());
		return 0;
	}

	// Sendet die länge was gesendet wurde
	return Result;
}
std::string NetFight::GetMsg(TCPsocket Socket) {
	int Length, Result;
	std::string Buffer = "";
	char *Buf;
	// Empfange die länge des Stringes
	Result = SDLNet_TCP_Recv( Socket, &Length, sizeof(Length));
	if( Result < (int)sizeof( Length)) {
		if(SDLNet_GetError() && strlen(SDLNet_GetError())) // Meinchmal leer
			print("SDLNet_TCP_Recv: %s", SDLNet_GetError());
		return Buffer;
	}
	// Bitreihenfolge zu edian wächseln ( Network)
	Length = SDL_SwapBE32(Length);
	// Checken ob die lnäge gültig ist
	if(!Length)
		return Buffer;
    Buf=(char*)malloc(Length);
	// Jetzt den String empfangen
	Result = SDLNet_TCP_Recv( Socket, Buf, Length);
	if( Result < Length) {
		if(SDLNet_GetError() && strlen(SDLNet_GetError())) // meinchmal leer
			print("SDLNet_TCP_Recv: %s", SDLNet_GetError());
		free(Buf);
		Buf=NULL;
	}
	print( "%s", Buf);
	// Umwandeln
	Buffer = Buf;
	// rückgabe
	return Buffer;
}
void NetFight::Process() {
    int NumReady = 0;
    int i;
    if( isServer == true) {
        TCPsocket sClient; // Client empfangen
        CreateSocketSet();
        NumReady = SDLNet_CheckSockets( SocketSet, (Uint32)1);
        if( NumReady == -1) {
			print("SDLNet_CheckSockets: %s",SDLNet_GetError());
			return;
        }
        if( NumReady == 0) // Keine Client
            return;
        if( SDLNet_SocketReady( ServerSocket)) {
            NumReady--;
            sClient = SDLNet_TCP_Accept( ServerSocket);
            if(sClient) {
                std::string Name;
                print( "Connection..");
                Name = GetMsg( sClient);
                if( Name != ""){
                    AddClient( Name, 0, sClient);
                } else {
                    print( "Geht nicht?");
                    SDLNet_TCP_Close( sClient);
                }
            }
        }
        // Nachrichten empfangen
        for( i = 0; NumReady && i < (int)Clients.size(); i++) {
            Client *client = &Clients[i];
            if( SDLNet_SocketReady( client->Sock)) {
                NumReady--;
                std::string Message;
                Message = GetMsg( client->Sock);
                if( Message == "quit");
                    client->quit = true;
            }
        }
        for( int i = 0; i < (int)Clients.size(); i++) {// Clients löschen
            if( Clients[i].quit == true) {
                DeleteClient( Clients[i].Name );
                i--;
            }
        }
    } else {
        NumReady = SDLNet_CheckSockets( SocketSet, 1);
		if( NumReady == -1 ) {
			print("SDLNet_CheckSockets: %s\n",SDLNet_GetError());
			return;
		}
		if( NumReady && SDLNet_SocketReady( SocketSet)) { // Resv data
            std::string Str;
            Str = GetMsg( ServerSocket);
            print( "%s", Str.c_str());
        }
    }
}

#include "stdafx.h"
#include "Main.h"

using namespace std;
//переменные для сетевой игры
const int ServerPort = 21995;
const int ClientPort = 30001;
const int ProtocolId = 0x99887766;
const float DeltaTime = 0.25f;
const float SendRate = 0.25f;
const float TimeOut = 10.0f;


bool InitializeSockets();
void ShutdownSockets();


int main(int argc, char *argv[])
{
    // initialize socket layer
    if ( !InitializeSockets() )
	{
		printf( "failed to initialize sockets\n" );
		return 1;
	}
    net::Socket gsocket( ProtocolId, TimeOut, ServerPort);
	// create socket

	printf( "creating socket on port %d\n", ClientPort );



	if ( !gsocket.Open( ClientPort ) )
	{
		printf( "failed to create socket!\n" );
		return 1;
	}

    //Выбор размера окна

	//CMain* cmain = new CMain(1280, 800);
	//CMain* cmain = new CMain(1280, 700);
	CMain* cmain = new CMain(800, 600, &gsocket);

	//Запуск процесса игры

    cmain->GameMenu(); //Запуск главного меню
    //cmain->GOMenu(); //Запуск окна GameOver
    //cmain->Loading(); //Запуск окна Loading

    ShutdownSockets();

	return 0;

}

bool InitializeSockets()
{
    #if PLATFORM == PLATFORM_WINDOWS
    WSADATA WsaData;
    return WSAStartup( MAKEWORD(2,2), &WsaData ) == NO_ERROR;
    #else
    return true;
    #endif
}

void ShutdownSockets()
{
    #if PLATFORM == PLATFORM_WINDOWS
    WSACleanup();
    #endif
}


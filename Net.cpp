    #include "Net.h"
    using namespace net;
    using namespace std;
    #include <cstdio>
	#include <winsock2.h>
	#include <ctime>
	#include <fstream>
	#pragma comment( lib, "wsock32.lib" )

extern std::string login;
	// platform independent wait for n seconds

	void wait( float seconds )
	{
		Sleep( (int) ( seconds * 1000.0f ) );
	}



    Address::Address()
    {
        address = 0;
        port = 0;
    }

    Address::Address( unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port )
    {
        this->address = ( a << 24 ) | ( b << 16 ) | ( c << 8 ) | d;
        this->port = port;
    }

    Address::Address( unsigned int address, unsigned short port )
    {
        this->address = address;
        this->port = port;
    }

    unsigned int Address::GetAddress() const
    {
        return address;
    }

    unsigned char Address::GetA() const
    {
        return ( unsigned char ) ( address >> 24 );
    }

    unsigned char Address::GetB() const
    {
        return ( unsigned char ) ( address >> 16 );
    }

    unsigned char Address::GetC() const
    {
        return ( unsigned char ) ( address >> 8 );
    }

    unsigned char Address::GetD() const
    {
        return ( unsigned char ) ( address );
    }

    unsigned short Address::GetPort() const
    {
        return port;
    }

    bool Address::operator == ( const Address & other ) const
    {
        return address == other.address && port == other.port;
    }

    bool Address::operator != ( const Address & other ) const
    {
        return ! ( *this == other );
    }



    Connection::Connection(unsigned int passed_address,
                           unsigned int protocolId,
                           int passed_port,
                           Socket * passed_socket)
    {
        address = passed_address;
        this->protocolId = protocolId;
        addressPort = Address(address, passed_port);
        lastConnect = time (NULL);
        //ClearData();
        firstTime = true;
        socket = passed_socket;
        timer = SDL_GetTicks();
        lastReceivedPacket = 0;
        lastShippedPacket = 0;
        disconnected = false;
    }

    Connection::~Connection()
    {

    }

    void Connection::Update( )
    {
        if ( lastConnect + 10 < time (NULL) )
        {
            printf( "connection timed out\n" );
            disconnected = true;
            lastConnect = time (NULL);
        }

        if(timer + 800 < SDL_GetTicks())
        {
            char data[1];

            data[0] = 254;

            Send(data, 1);

            //socket->Send( addressPort, packet, sizeof(packet) );

            timer = SDL_GetTicks();
        }
    }

    unsigned char* Connection::CreatePacket( const unsigned char data[], int size )
    {
        assert( running );
        if ( addressPort.GetAddress() == 0 )
            return false;
        unsigned char packet[size+4];
        packet[0] = (unsigned char) ( protocolId >> 24 );
        packet[1] = (unsigned char) ( ( protocolId >> 16 ) & 0xFF );
        packet[2] = (unsigned char) ( ( protocolId >> 8 ) & 0xFF );
        packet[3] = (unsigned char) ( ( protocolId ) & 0xFF );
        memcpy( &packet[4], data, size );
        return packet;
    }

    bool Connection::Send( const void * data, int size )
    {
        //assert( data );
        //assert( size > 0 );
        if ( addressPort.GetAddress() == 0 )
            return false;
        unsigned char packet[size+16];
        packet[0] = (unsigned char) ( protocolId >> 24 );
        packet[1] = (unsigned char) ( ( protocolId >> 16 ) & 0xFF );
        packet[2] = (unsigned char) ( ( protocolId >> 8 ) & 0xFF );
        packet[3] = (unsigned char) ( ( protocolId ) & 0xFF );
        packet[4] = (unsigned char)(login[0]);
        packet[5] = (unsigned char)(login[1]);
        packet[6] = (unsigned char)(login[2]);
        packet[7] = (unsigned char)(login[3]);
        packet[8] = (unsigned char)(login[4]);
        packet[9] = (unsigned char)(login[5]);
        packet[10] = (unsigned char)(login[6]);
        packet[11] = (unsigned char)(login[7]);
        packet[12] = (unsigned char) ( lastShippedPacket >> 24 );
        packet[13] = (unsigned char) ( lastShippedPacket >> 16 );
        packet[14] = (unsigned char) ( lastShippedPacket >> 8 );
        packet[15] = (unsigned char) ( lastShippedPacket );
        memcpy( &packet[16], data, size );


        lastShippedPacket++;

        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htonl( addressPort.GetAddress() );
        address.sin_port = htons( (unsigned short) addressPort.GetPort() );
        /*std::ofstream LoadedFile;
        LoadedFile.open("Log.txt");
        for(int i =0; i < size +16; i++)
            LoadedFile << int(packet[i]) << " ";
        LoadedFile << std::endl;

        LoadedFile.close();*/
        //std::cout << "sending" << std::endl;
        int sent_bytes = sendto( socket->getSocket(), (const char*)packet, size+16, 0, (sockaddr*)&address, sizeof(sockaddr_in) );

        return sent_bytes == size+16;
    }


    unsigned char* Connection::ReceivePacket( unsigned char data[], int size, unsigned int NumberOfPacket )
    {
        if(lastReceivedPacket < NumberOfPacket)
        {
            lastReceivedPacket = NumberOfPacket;
            UpdatePacket();
            return data;
        }
        return 0;

    }


    Socket::Socket( unsigned int passed_protocolId, int passed_destinationPort)
    {
        protocolId = passed_protocolId;
        socket = 0;
        destinationPort = passed_destinationPort;
        connectedClients.clear();
    }

    Socket::~Socket()
    {
        Close();
    }

    bool Socket::Open( unsigned short port )
    {
        assert( !IsOpen() );

        // create socket

        socket = ::socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

        if ( socket <= 0 )
        {
            printf( "failed to create socket\n" );
            socket = 0;
            return false;
        }

        // bind to port

        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons( (unsigned short) port );

        if ( bind( socket, (const sockaddr*) &address, sizeof(sockaddr_in) ) < 0 )
        {
            printf( "failed to bind socket\n" );
            Close();
            return false;
        }

        // set non-blocking io

        #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

            int nonBlocking = 1;
            if ( fcntl( socket, F_SETFL, O_NONBLOCK, nonBlocking ) == -1 )
            {
                printf( "failed to set non-blocking socket\n" );
                Close();
                return false;
            }

        #elif PLATFORM == PLATFORM_WINDOWS

            DWORD nonBlocking = 1;
            if ( ioctlsocket( socket, FIONBIO, &nonBlocking ) != 0 )
            {
                printf( "failed to set non-blocking socket\n" );
                Close();
                return false;
            }

        #endif

        return true;
    }

    void Socket::Close()
    {
        if ( socket != 0 )
        {
            #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
            close( socket );
            #elif PLATFORM == PLATFORM_WINDOWS
            closesocket( socket );
            #endif
            socket = 0;
        }
    }

    bool Socket::IsOpen() const
    {
        return socket != 0;
    }

    bool Socket::Send( const Address & destination, const void * data, int size )
    {
        assert( data );
        assert( size > 0 );

        if ( socket == 0 )
            return false;

        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htonl( destination.GetAddress() );
        address.sin_port = htons( (unsigned short) destination.GetPort() );

        int sent_bytes = sendto( socket, (const char*)data, size, 0, (sockaddr*)&address, sizeof(sockaddr_in) );

        return sent_bytes == size;
    }

    void Socket::Update()
    {
        for(std::map<unsigned int, Connection*>::iterator i = connectedClients.begin(); i != connectedClients.end(); ++i)
        {
            i -> second->Update( );
            if(i->second->IsDisconencted())
            {
                connectedClients.erase(i);
                //i = connectedClients.begin();
                connectedClients.clear();
                break;
            }
        }
    }

    int Socket::Receive( Address & sender, unsigned char * data, int size )
    {
        Update();
        //int size = size1+16;

        if ( socket == 0 )
            return false;

        //char * data;

        #if PLATFORM == PLATFORM_WINDOWS
        typedef int socklen_t;
        #endif

        sockaddr_in from;
        socklen_t fromLength = sizeof( from );

        int received_bytes = recvfrom( socket, (char*)data, size, 0, (sockaddr*)&from, &fromLength );

        if ( received_bytes <= 0 )
            return 0;

        unsigned int address = ntohl( from.sin_addr.s_addr );
        unsigned int port = ntohs( from.sin_port );
        if ( size != 0 &&
             size >= 16 &&
             data[0] == (unsigned char) ( protocolId >> 24 ) &&
             data[1] == (unsigned char) ( ( protocolId >> 16 ) & 0xFF ) &&
             data[2] == (unsigned char) ( ( protocolId >> 8 ) & 0xFF ) &&
             data[3] == (unsigned char) ( protocolId & 0xFF ) )
             {
                unsigned char packet[size - 4];
                memcpy( packet, &data[4], size - 4 );
                //������� ���������� �����
                std::string received_login;
                for(int i = 0; i < 8; i++)
                {
                    if(packet[i] != 0)
                    {
                        received_login += packet[i];
                    }
                    else
                        break;
                }
                unsigned int NumberOfPacket = (unsigned int)(packet[9] << 24)
                                                + (unsigned int)(packet[10]<< 16)
                                                + (unsigned int)(packet[11] << 8)
                                                + packet[12];
                unsigned char buffer[size-16];
                memcpy( buffer, &packet[12], size-16 );

                if(!(connectedClients.empty()))
                {

                    std::map<unsigned int, Connection*>::iterator result = connectedClients.find(address);

                    if (result != connectedClients.end())
                    {
                        //std::cout << "Element found: " << std::endl;
                        //��������� ����� �� ������
                        result->second->ReceivePacket(buffer, size-16, NumberOfPacket);

                        for(int i = 0; i < size; i++)
                        {
                            data[i] = 0;
                        }

                        memcpy( data, &buffer[0], size-16 );

                    }
                }
                else if(data[9] != 254)
                {
                    connectedClients[address] = new Connection(address,
                                                                    protocolId,
                                                                    port,
                                                                    this);
                    connectedClients[address]->ReceivePacket(buffer, size-16, NumberOfPacket);

                    for(int i = 0; i < size; i++)
                    {
                        data[i] = 0;
                    }

                    memcpy( data, &buffer[0], size-16 );


                }
                sender = Address(address, port);
                return received_bytes;
             }
             else
             {
                 std::cout<< "Bad packet" << std::endl;
             }


    }


// MiddleWare.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TcpSocketManager.h"
#include <list>

typedef struct PPPPPPQQQ
{
	TcpClient* tcpClient;
}TcpClientData;

TcpServer* g_server;
std::list<std::pair< TcpClient*, TcpClientData* >> g_listClient;
CRITICAL_SECTION g_csListClient;

int AcceptCallback(TcpClient* client, void* uesrParam);
int ReceiveCallback(TcpClient::MessageData * message, void * uesrParam);

int main()
{
	InitializeCriticalSection(&g_csListClient);
	Socket::GlobalInit();
	tcpSocketManager.StartServer(10086);
	g_server = tcpSocketManager.geTcpServer();
	g_server->SetAcceptCallback(AcceptCallback, nullptr);
	Sleep(INFINITE);
	return 0;
}

int AcceptCallback(TcpClient* client, void* uesrParam)
{
	TcpClientData* clientData = new TcpClientData;
	clientData->tcpClient = client;
	EnterCriticalSection(&g_csListClient);
	g_listClient.push_back(std::pair<TcpClient*, TcpClientData*>(client, clientData));
	LeaveCriticalSection(&g_csListClient);
	client->SetReceiveCallback(ReceiveCallback, clientData);


	return 0;
}

int ReceiveCallback(TcpClient::MessageData * message, void * uesrParam)
{
	TcpClientData* clientData = (TcpClientData*)uesrParam;
	if (message == nullptr)
	{
		EnterCriticalSection(&g_csListClient);

		for (auto i = g_listClient.begin(); i != g_listClient.end(); i++)
		{
			if (clientData == i->second)
			{
				if (i == g_listClient.begin())
				{
					g_server->Close();
				}
				delete i->second;
				g_listClient.erase(i);
				LeaveCriticalSection(&g_csListClient);
				return 0;
			}
		}
		LeaveCriticalSection(&g_csListClient);
	}
	switch (message->type)
	{
	case Socket::MessageType::Add:
	{
		
	}
	break;
	case Socket::MessageType::Delete:
	{
	}
	break;
	case Socket::MessageType::Modify:
	{
	}
	break;
	case Socket::MessageType::Query:
	{
	}
	break;
	}
	return 0;
}

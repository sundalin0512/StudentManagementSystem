// MiddleWare.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TcpSocketManager.h"
#include <list>
#include "tools.h"

typedef struct PPPPPPQQQ
{
	TcpClient* tcpClient;
}TcpClientData;

TcpServer* g_server;
std::list<std::pair< TcpClient*, TcpClientData* >> g_listClient;
std::pair< TcpClient*, TcpClientData* > g_sqlServer;
CRITICAL_SECTION g_csListClient;

int AcceptCallback(TcpClient* client, void* uesrParam);
int ReceiveCallback(TcpClient::MessageData * message, void * uesrParam);
int ReceiveServerCallback(TcpClient::MessageData * message, void * uesrParam);
int ReceiveClientCallback(TcpClient::MessageData * message, void * uesrParam);

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
	client->Send(MessageType::AskSC, "");

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
	case MessageType::AnsServer:
	{
		EnterCriticalSection(&g_csListClient);
		for (auto i = g_listClient.begin(); i != g_listClient.end(); i++)
		{
			if (clientData == i->second)
			{
				g_sqlServer = *i;
				g_listClient.erase(i);
				LeaveCriticalSection(&g_csListClient);
				break;
			}
		}
		LeaveCriticalSection(&g_csListClient);
		clientData->tcpClient->SetReceiveCallback(ReceiveServerCallback, clientData);
	}
	break;
	case MessageType::AnsClient:
	{
		clientData->tcpClient->SetReceiveCallback(ReceiveClientCallback, clientData);

	}
	break;
	}
	return 0;
}
int ReceiveClientCallback(TcpClient::MessageData * message, void * uesrParam)
{
	
	TcpClientData* clientData = (TcpClientData*)uesrParam;
	if (g_sqlServer.first == nullptr)
	{
		clientData->tcpClient->Send(MessageType::NoServer, "");
		return 0;
	}
	if (message == nullptr)
	{
		EnterCriticalSection(&g_csListClient);

		for (auto i = g_listClient.begin(); i != g_listClient.end(); i++)
		{
			if (clientData == i->second)
			{
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
	case MessageType::Add:
	{
		TcpClient::MessageData sendMessage;
		sendMessage.length = 0;
		sendMessage.type = MessageType::AddExcute;
		sendMessage.data = nullptr;
		int table = message->data[0];
		std::string str(message->data + 1, message->length - 1);
		std::vector<std::string> strs = split(str, "\n");
		std::string sendString =std::string("INSERT INTO ") + strTables[table] + " VALUES (";
		for (auto i = strs.begin(); i < strs.end(); i++)
		{
			sendString += "N'" + *i + "',";
		}
		sendString.pop_back();
		sendString += ")";
		sendMessage.length = sendString.size() + sizeof(TcpClient*);
		sendMessage.data = new char[sendMessage.length];
		CopyMemory(sendMessage.data, &clientData->tcpClient, sizeof(TcpClient*));
		CopyMemory(sendMessage.data + sizeof(TcpClient*), sendString.data(), sendString.size());
		g_sqlServer.first->Send(sendMessage);
	}
	break;
	case MessageType::Delete:
	{
	}
	break;
	case MessageType::Modify:
	{
	}
	break;
	case MessageType::Query:
	{
	}
	break;
	}
	return 0;
}
int ReceiveServerCallback(TcpClient::MessageData * message, void * uesrParam)
{
	TcpClientData* clientData = (TcpClientData*)uesrParam;
	if (message == nullptr)
	{
		EnterCriticalSection(&g_csListClient);
		delete g_sqlServer.second;
		g_sqlServer.first = nullptr;
		g_sqlServer.second = nullptr;
		LeaveCriticalSection(&g_csListClient);
		return 0;
	}
	TcpClient* client = (TcpClient*)*(int*)message->data;
	TcpClient::MessageData sendMessage;
	sendMessage.length = message->length - sizeof(TcpClient*);
	sendMessage.type = message->type;
	if (sendMessage.length > 0)
	{
		sendMessage.data = new char[sendMessage.length];
		CopyMemory(sendMessage.data, message->data + sizeof(TcpClient*), sendMessage.length);
	}
	else
		sendMessage.data = nullptr;
	client->Send(sendMessage);
	return 0;
}
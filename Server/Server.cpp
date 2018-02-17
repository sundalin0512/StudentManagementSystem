// Server.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Socket.h"
#include "TcpClient.h"

#import "msado15.dll" rename("EOF", "myEOF") no_namespace

_ConnectionPtr g_connection;

#define CONN_STRING "Provider=SQLOLEDB.1;Persist Security Info=False;User ID=sa;Initial Catalog=master;Data Source=192.168.137.100"

int ReceiveCallback(TcpClient::MessageData* message, void* uesrParam);

TcpClient* g_client;
int main()
{
	Socket::GlobalInit();
	CoInitialize(NULL);
	g_client = new TcpClient(10086, "127.0.0.1");
	g_client->SetReceiveCallback(ReceiveCallback, nullptr);
	TcpClient::MessageData message;
	message.length = 0;
	message.type = MessageType::Nop;
	message.data = nullptr;
	g_client->Send(message);
	try
	{
		HRESULT hr = g_connection.CreateInstance(__uuidof(Connection));

		if (FAILED(hr))
		{
			return 0;
		}
		g_connection->ConnectionString = CONN_STRING;
		g_connection->ConnectionTimeout = 10;
		hr = g_connection->Open("", "", "", adConnectUnspecified);

		if (FAILED(hr))
		{
			return 0;
		}
		printf("连接到数据库成功\r\n");

		_variant_t vt;

		_RecordsetPtr rs = g_connection->Execute("USE student",
			&vt,
			adCmdText);


		//hr = g_connection->Close();

		//if (FAILED(hr))
		//{
		//	return 0;
		//}

	}
	catch (_com_error e)
	{
		wchar_t* p = e.Description();
	}

	Sleep(INFINITE);
	try
	{
		HRESULT	hr = g_connection->Close();

		if (FAILED(hr))
		{
			return 0;
		}

	}
	catch (_com_error e)
	{
		wchar_t* p = e.Description();
	}


	return 0;
}

int ReceiveCallback(TcpClient::MessageData* message, void* uesrParam)
{
	TcpClient::MessageData *newMessage = new TcpClient::MessageData;
	newMessage->length = message->length;
	newMessage->data = new char[newMessage->length];
	memcpy_s(newMessage->data, newMessage->length, message->data, message->length);
	newMessage->type = message->type;
	switch (message->type)
	{
	case MessageType::AskSC:
	{
		g_client->Send(MessageType::AnsServer, "");
	}
	break;
	case MessageType::AddExcute:
	{
		TcpClient::MessageData sendMessage;
		sendMessage.length = 0;
		sendMessage.type = MessageType::AddFail;
		sendMessage.data = nullptr;
		sendMessage.length = sizeof(TcpClient*);
		sendMessage.data = new char[sendMessage.length];
		CopyMemory(sendMessage.data, newMessage->data, sizeof(TcpClient*));

		std::string sqlStr(newMessage->data + sizeof(TcpClient*), newMessage->length - sizeof(TcpClient*));
		auto p = split(sqlStr, " ");
		assert(p.size() >= 3);
		std::string sqlStr2 = "UPDATE tb_update_time\
			SET updateTime = (SELECT updateTime WHERE tableName = N'" + p[2] + "') + 1\
			WHERE tableName = N'" + p[2] + "'";
		try
		{
			g_connection->BeginTrans();
			_RecordsetPtr pRec = g_connection->Execute(sqlStr.c_str(),
				NULL,
				adCmdText);
			pRec = g_connection->Execute(sqlStr2.c_str(),
				NULL,
				adCmdText);
			g_connection->CommitTrans();
			sendMessage.type = MessageType::AddSuccess;
			g_client->Send(sendMessage);
		}
		catch (_com_error e)
		{
			wchar_t* p = e.Description();
			g_connection->RollbackTrans();
			sendMessage.type = MessageType::AddFail;
			g_client->Send(sendMessage);
		}

	}
	break;
	}

	return 0;
}

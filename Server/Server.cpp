// Server.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Socket.h"
#include "TcpClient.h"

#import "msado15.dll" rename("EOF", "myEOF") no_namespace

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
	message.type = TcpClient::MessageType::Nop;
	message.data = nullptr;
	g_client->Send(message);
	try
	{
		_ConnectionPtr conn;

		HRESULT hr = conn.CreateInstance(__uuidof(Connection));

		if (FAILED(hr))
		{
			return 0;
		}
		conn->ConnectionString = CONN_STRING;
		conn->ConnectionTimeout = 10;
		hr = conn->Open("", "", "", adConnectUnspecified);


		if (FAILED(hr))
		{
			return 0;
		}

		_variant_t vt;

		_RecordsetPtr rs = conn->Execute("SELECT * FROM tb_student",
			&vt,
			adCmdText);


		hr = conn->Close();

		if (FAILED(hr))
		{
			return 0;
		}

	}
	catch (_com_error e)
	{
		wchar_t* p = e.Description();
	}

	Sleep(INFINITE);
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
	}

	return 0;
}

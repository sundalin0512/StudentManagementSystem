// Server.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Socket.h"
#include "TcpClient.h"

#import "msado15.dll" rename("EOF", "myEOF") no_namespace

_ConnectionPtr g_connection;

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
		wchar_t szPath[MAXBYTE];

		GetModuleFileName(NULL, szPath, MAXBYTE);
		std::wstring strPath =L"File Name=";
		strPath+=szPath;
		strPath.erase(strPath.rfind('\\'), strPath.length() + 1);


		strPath += L"\\connect.udl";
		g_connection->ConnectionString = strPath.data();
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
		//rs = g_connection->Execute("SELECT name FROM syscolumns WHERE id = Object_Id('tb_student_course') and colid IN(SELECT keyno from sysindexkeys WHERE id = Object_Id('tb_student_course'))",
		//	&vt,
		//	adCmdText);

		//{
		//	int nCount = rs->Fields->GetCount();
		//	char szBuf[256] = { 0 };

		//	//打印表头
		//	for (int i = 0; i < nCount; i++)
		//	{
		//		_variant_t index = i;
		//		wsprintfA(szBuf, "%s ", (char*)rs->Fields->Item[(long)i]->Name);
		//		printf(szBuf);
		//	}

		//	//打印表中数据
		//	while (!rs->myEOF)
		//	{
		//		for (int i = 0; i < nCount; i++)
		//		{
		//			_variant_t vt = rs->Fields->Item[(long)i]->Value;
		//			wsprintfA(szBuf, "%s ", (char*)(_bstr_t)vt);
		//			printf(szBuf);
		//		}
		//		rs->MoveNext();
		//	}
		//}


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
	case MessageType::DeleteExcute:
	case MessageType::ModifyExcute:
	{
		TcpClient::MessageData sendMessage;
		sendMessage.length = 0;
		sendMessage.type = MessageType::Fail;
		sendMessage.data = nullptr;
		sendMessage.length = sizeof(TcpClient*);
		sendMessage.data = new char[sendMessage.length];
		CopyMemory(sendMessage.data, newMessage->data, sizeof(TcpClient*));

		std::string sqlStr(newMessage->data + sizeof(TcpClient*), newMessage->length - sizeof(TcpClient*));

		std::string sqlStr2 = "UPDATE tb_update_time\
			SET updateTime = (SELECT updateTime WHERE tableName = N'updateTime') + 1\
			WHERE tableName = N'updateTime'";

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
			sendMessage.type = MessageType::Success;
			g_client->Send(sendMessage);
		}
		catch (_com_error e)
		{
			std::string p = (char*)e.Description();
			g_connection->RollbackTrans();
			sendMessage.type = MessageType::Fail;
			sendMessage.length = sizeof(TcpClient*) + p.length();
			sendMessage.data = new char[sendMessage.length];
			CopyMemory(sendMessage.data, newMessage->data, sizeof(TcpClient*));
			CopyMemory(sendMessage.data + sizeof(TcpClient*), p.data(), p.length());
			g_client->Send(sendMessage);
		}

	}
	break;
	case MessageType::QueryExcute:
	{
		TcpClient::MessageData sendMessage;
		sendMessage.length = 0;
		sendMessage.type = MessageType::QueryFail;
		sendMessage.data = nullptr;

		std::string sqlStr(newMessage->data + sizeof(TcpClient*), newMessage->length - sizeof(TcpClient*));
		try
		{
			_variant_t vt;
			_RecordsetPtr pRec = g_connection->Execute(sqlStr.c_str(),
				&vt,
				adCmdText);

			std::string strSend;
			{
				int nCount = pRec->Fields->GetCount();
				char szBuf[256] = { 0 };
				_itoa_s(nCount, szBuf, 10);
				strSend += szBuf;
				strSend += "\n";
				//打印表头
				for (int i = 0; i < nCount; i++)
				{
					_variant_t index = i;
					strSend += (char*)pRec->Fields->Item[(long)i]->Name;
					strSend += "\n";
				}

				//打印表中数据
				while (!pRec->myEOF)
				{
					for (int i = 0; i < nCount; i++)
					{
						_variant_t vt = pRec->Fields->Item[(long)i]->Value;
						if (vt.vt != VT_NULL)
							strSend += (char*)(_bstr_t)vt;
						strSend += "\n";
					}
					pRec->MoveNext();
				}
			}
			sendMessage.type = MessageType::QuerySuccess;
			sendMessage.length = sizeof(TcpClient*) + strSend.length();
			sendMessage.data = new char[sendMessage.length];
			CopyMemory(sendMessage.data, newMessage->data, sizeof(TcpClient*));
			CopyMemory(sendMessage.data + sizeof(TcpClient*), strSend.data(), strSend.length());
			g_client->Send(sendMessage);
		}
		catch (_com_error e)
		{
			std::string p = (char*)e.Description();
			sendMessage.type = MessageType::QueryFail;
			sendMessage.length = sizeof(TcpClient*) + p.length();
			sendMessage.data = new char[sendMessage.length];
			CopyMemory(sendMessage.data, newMessage->data, sizeof(TcpClient*));
			CopyMemory(sendMessage.data + sizeof(TcpClient*), p.data(), p.length());
			g_client->Send(sendMessage);
		}
	}
	break;
	case MessageType::QueryAsk:
	{
		TcpClient::MessageData sendMessage;
		sendMessage.length = 0;
		sendMessage.type = MessageType::QueryAnsNoUpdate;
		sendMessage.data = nullptr;

		std::string sqlStr(newMessage->data + sizeof(TcpClient*), newMessage->length - sizeof(TcpClient*));
		try
		{
			_variant_t vt;
			_RecordsetPtr pRec = g_connection->Execute(sqlStr.c_str(),
				&vt,
				adCmdText);

			std::string strSend;
			int retVal = 0;
			{
				int nCount = pRec->Fields->GetCount();
				char szBuf[256] = { 0 };
				_itoa_s(nCount, szBuf, 10);

				//打印表中数据
				while (!pRec->myEOF)
				{
					for (int i = 0; i < nCount; i++)
					{
						_variant_t vt = pRec->Fields->Item[(long)i]->Value;
						strSend += (char*)(_bstr_t)vt;
						retVal = vt;
					}
					pRec->MoveNext();
				}
			}
			if (retVal == -1)
			{
				sendMessage.type = MessageType::QueryAnsNoUpdate;
			}
			else if (retVal == 0)
			{
				sendMessage.type = MessageType::QueryFail;
			}
			else
			{
				sendMessage.type = MessageType::QueryAnsUpdate;
			}
			sendMessage.length = sizeof(TcpClient*) + strSend.length();
			sendMessage.data = new char[sendMessage.length];
			CopyMemory(sendMessage.data, newMessage->data, sizeof(TcpClient*));
			CopyMemory(sendMessage.data + sizeof(TcpClient*), strSend.data(), strSend.length());
			g_client->Send(sendMessage);
		}
		catch (_com_error e)
		{
			std::string p = (char*)e.Description();
			sendMessage.type = MessageType::QueryFail;
			sendMessage.length = sizeof(TcpClient*) + p.length();
			sendMessage.data = new char[sendMessage.length];
			CopyMemory(sendMessage.data, newMessage->data, sizeof(TcpClient*));
			CopyMemory(sendMessage.data + sizeof(TcpClient*), p.data(), p.length());
			g_client->Send(sendMessage);
		}
	}
	break;

	}

	return 0;
}

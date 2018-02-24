#include "stdafx.h"
#include "ITask.h"
#include "TcpClient.h"
#include "tools.h"
#include <windows.h>
#include <assert.h>

ITask::ITask(std::pair<TcpClient*, TcpClientData*>* thisDlg, TcpClient::MessageData * message, TcpClientData* clientData) : g_sqlServer(thisDlg), receiveMessage(message), clientData(clientData) {}

ITask::~ITask()
{
	delete receiveMessage->data;
	delete receiveMessage;
}

void TaskAdd::Run()
{
	TcpClient::MessageData sendMessage;
	sendMessage.length = 0;
	sendMessage.type = MessageType::AddExcute;
	sendMessage.data = nullptr;
	int table = receiveMessage->data[0];
	std::string str(receiveMessage->data + 1, receiveMessage->length - 1);
	std::vector<std::string> strs = split(str, "\n");
	std::string sendString = std::string("INSERT INTO ") + strTables[table] + " VALUES (";
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
	g_sqlServer->first->Send(sendMessage);
}

void TaskDelete::Run()
{
	TcpClient::MessageData sendMessage;
	sendMessage.length = 0;
	sendMessage.type = MessageType::DeleteExcute;
	sendMessage.data = nullptr;
	SelectTable table = (SelectTable)receiveMessage->data[0];
	std::string str(receiveMessage->data + 1, receiveMessage->length - 1);
	std::vector<std::string> strs = split(str, "\n");

	std::string sendString = std::string("DELETE FROM ") + strTables[(int)table] + " WHERE ";
	switch (table)
	{
	case SelectTable::tb_student:
	{
		assert(strs.size() == 1);
		sendString += std::string(strKeyNames[(int)SelectKey::studentID]) + "= " + strs[0];
	}
	break;
	case SelectTable::tb_course:
	{
		assert(strs.size() == 1);
		sendString += std::string(strKeyNames[(int)SelectKey::courseID]) + "= " + strs[0];
	}
	break;
	case SelectTable::tb_class:
	{
		assert(strs.size() == 1);
		sendString += std::string(strKeyNames[(int)SelectKey::classID]) + "= " + strs[0];
	}
	break;
	case SelectTable::tb_studentCourse:
	{
		assert(strs.size() == 2);
		sendString += std::string(strKeyNames[(int)SelectKey::studentID]) + "= " + strs[0] + " AND "
			+ std::string(strKeyNames[(int)SelectKey::courseID]) + "= " + strs[1];
	}
	break;
	case SelectTable::tb_studentClass:
	{
		assert(strs.size() == 2);
		sendString += std::string(strKeyNames[(int)SelectKey::studentID]) + "= " + strs[0] + " AND "
			+ std::string(strKeyNames[(int)SelectKey::classID]) + "= " + strs[1];

	}
	break;
	}

	sendMessage.length = sendString.size() + sizeof(TcpClient*);
	sendMessage.data = new char[sendMessage.length];
	CopyMemory(sendMessage.data, &clientData->tcpClient, sizeof(TcpClient*));
	CopyMemory(sendMessage.data + sizeof(TcpClient*), sendString.data(), sendString.size());
	g_sqlServer->first->Send(sendMessage);

}
void TaskModify::Run()
{
	TcpClient::MessageData sendMessage;
	sendMessage.length = 0;
	sendMessage.type = MessageType::ModifyExcute;
	sendMessage.data = nullptr;
	SelectTable table = (SelectTable)receiveMessage->data[0];
	std::string str(receiveMessage->data + 1, receiveMessage->length - 1);
	std::vector<std::string> strs = split(str, "\n");
	std::string sendString = std::string("UPDATE ") + strTables[(int)table] + " SET ";

	switch (table)
	{
	case SelectTable::tb_student:
	{
		assert(strs.size() == 4);
		sendString += std::string(strKeyNames[(int)SelectKey::studentName]) + "= " + strs[1] + ","
			+ strKeyNames[(int)SelectKey::sex] + "= " + strs[2] + ","
			+ strKeyNames[(int)SelectKey::telephone] + "= " + strs[3]
			+ std::string("WHERE ") + strKeyNames[(int)SelectKey::studentID] + "= " + strs[0];
	}
	break;
	case SelectTable::tb_course:
	{
		assert(strs.size() == 2);
		sendString += std::string(strKeyNames[(int)SelectKey::courseName]) + "= " + strs[1]
			+ std::string("WHERE ") + strKeyNames[(int)SelectKey::courseID] + "= " + strs[0];
	}
	break;
	case SelectTable::tb_class:
	{
		assert(strs.size() == 2);
		sendString += std::string(strKeyNames[(int)SelectKey::className]) + "= " + strs[1]
			+ std::string("WHERE ") + strKeyNames[(int)SelectKey::classID] + "= " + strs[0];
	}
	break;
	case SelectTable::tb_studentCourse:
	{
		assert(strs.size() == 3);
		sendString += std::string(strKeyNames[(int)SelectKey::grade]) + "= " + strs[2]
			+ std::string("WHERE ") + strKeyNames[(int)SelectKey::studentID] + "= " + strs[0]
			+ std::string(" AND ") + strKeyNames[(int)SelectKey::courseID] + "= " + strs[1];
	}
	break;
	}

	sendMessage.length = sendString.size() + sizeof(TcpClient*);
	sendMessage.data = new char[sendMessage.length];
	CopyMemory(sendMessage.data, &clientData->tcpClient, sizeof(TcpClient*));
	CopyMemory(sendMessage.data + sizeof(TcpClient*), sendString.data(), sendString.size());
	g_sqlServer->first->Send(sendMessage);
}

void TaskQuery::Run()
{
	TcpClient::MessageData sendMessage;
	sendMessage.length = 0;
	sendMessage.type = MessageType::QueryExcute;
	sendMessage.data = nullptr;
	std::string str(receiveMessage->data, receiveMessage->length);
	std::vector<std::string> strs = split(str, "\n");
	std::string sendString = "SELECT DISTINCT ";
	for (auto i = strs[0].begin(); i < strs[0].end(); ++i)
	{
		sendString += strKeyNamesWithTable[*i - '0'];
		sendString += ",";
	}
	sendString.pop_back();
	sendString += " FROM tb_student FULL JOIN tb_student_course ON tb_student.studentID = tb_student_course.studentID \
FULL JOIN tb_course ON tb_student_course.courseID = tb_course.courseID FULL JOIN  tb_student_class ON tb_student.studentID = tb_student_class.studentID \
FULL JOIN tb_class ON tb_student_class.classID = tb_class.classID WHERE ";
	for (auto i = strs.begin() + 1; i < strs.end(); ++i)
	{
		sendString += strKeyNamesWithTable[(*i)[0] - '0'];
		sendString += "=N'";
		sendString += *++i;
		sendString += "' AND ";
	}
	sendString.erase(sendString.end() - 4, sendString.end());
	sendMessage.length = sendString.size() + sizeof(TcpClient*);
	sendMessage.data = new char[sendMessage.length];
	CopyMemory(sendMessage.data, &clientData->tcpClient, sizeof(TcpClient*));
	CopyMemory(sendMessage.data + sizeof(TcpClient*), sendString.data(), sendString.size());
	g_sqlServer->first->Send(sendMessage);

}

void TaskQueryAsk::Run()
{
	TcpClient::MessageData sendMessage;
	sendMessage.length = 0;
	sendMessage.type = MessageType::QueryAsk;
	sendMessage.data = nullptr;
	std::string str(receiveMessage->data, receiveMessage->length);
	std::vector<std::string> strs = split(str, "\n");
	std::string sendString = "IF (SELECT updateTime FROM tb_update_time WHERE tableName = N'updateTime') = ";
	sendString += strs[0];
	sendString += " SELECT -1 \
			ELSE SELECT updateTime FROM tb_update_time WHERE tableName = N'updateTime'";
	sendMessage.length = sendString.size() + sizeof(TcpClient*);
	sendMessage.data = new char[sendMessage.length];
	CopyMemory(sendMessage.data, &clientData->tcpClient, sizeof(TcpClient*));
	CopyMemory(sendMessage.data + sizeof(TcpClient*), sendString.data(), sendString.size());
	g_sqlServer->first->Send(sendMessage);

}




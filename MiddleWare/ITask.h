#pragma once
#include <map>
class TcpClient;


class ITask
{
	public:
	ITask(std::pair< TcpClient*, TcpClientData* >* sqlServer, TcpClient::MessageData* message, TcpClientData* clientData);
	virtual ~ITask();
	virtual void Run() = 0;
	std::pair< TcpClient*, TcpClientData* >* g_sqlServer;
	TcpClient::MessageData* receiveMessage;
	TcpClientData* clientData;
};


class TaskAdd :
	public ITask
{
	public:
	TaskAdd(std::pair< TcpClient*, TcpClientData* >* sqlServer, TcpClient::MessageData* message, TcpClientData* clientData) : ITask(sqlServer, message, clientData) {}
	~TaskAdd() {}

	virtual void Run() override;
};

class TaskDelete :
	public ITask
{
	public:
	TaskDelete(std::pair< TcpClient*, TcpClientData* >* sqlServer, TcpClient::MessageData* message, TcpClientData* clientData) : ITask(sqlServer, message, clientData) {}
	~TaskDelete() {}

	virtual void Run() override;
};

class TaskModify :
	public ITask
{
	public:
	TaskModify(std::pair< TcpClient*, TcpClientData* >* sqlServer, TcpClient::MessageData* message, TcpClientData* clientData) : ITask(sqlServer, message, clientData) {}
	~TaskModify() {}

	virtual void Run() override;
};

class TaskQuery :
	public ITask
{
	public:
	TaskQuery(std::pair< TcpClient*, TcpClientData* >* sqlServer, TcpClient::MessageData* message, TcpClientData* clientData) : ITask(sqlServer, message, clientData) {}
	~TaskQuery() {}

	virtual void Run() override;
};

class TaskQueryAsk :
	public ITask
{
	public:
	TaskQueryAsk(std::pair< TcpClient*, TcpClientData* >* sqlServer, TcpClient::MessageData* message, TcpClientData* clientData) : ITask(sqlServer, message, clientData) {}
	~TaskQueryAsk() {}

	virtual void Run() override;
};

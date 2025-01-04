#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <random>
#include <sstream>
#include <iomanip>
#include <vector>
#include <unordered_map>


#define TOOL_NUMBER 10000

class Tool {
public:
    Tool() = default;
    Tool(const std::string& id,const std::string& server_address,int port, int version) : 
    _tool_id(id),
    _server_address(server_address),
    _server_port(port),
    _version(version){}

    std::string getToolId() const;
    std::string getServerAddress() const;
    int getServerPort() const;
    int getVersion() const;

    bool operator<(const Tool& other) const;

    void display() const;

private:
    std::string _tool_id;
    std::string _server_address;
    int _server_port;
    int _version;
};



class Sender{
public:
    Sender(const std::string& serverIp, int port);
    void sendMessage(const std::string& message);

    ~Sender();

private:
    int sockfd;
    struct sockaddr_in _serverAddres;
};


class FlyweightFactory{
public:
    FlyweightFactory() = default;
    void sendMessageToTool(const Tool& tool, const std::string& message);

private:
    std::map<std::string, std::shared_ptr<Sender>> senderMap;
};




class ToolGenerator {
private:
    std::random_device rd;
    std::mt19937 gen;

    std::string generateToolId();
    int getPortForAddress(const std::string &address);

public:
    ToolGenerator() : gen(rd()) {}
    Tool generateTool();
};




#include "flyweight.h"


std::string Tool::getToolId() const { return _tool_id; }
std::string Tool::getServerAddress() const {return _server_address;}
int Tool::getServerPort() const {return _server_port;}
int Tool::getVersion() const { return _version; }

bool Tool::operator<(const Tool& other) const {
    if (_tool_id != other.getToolId()){
        return _tool_id < other.getToolId();            
    }
    return _version < other.getVersion();
}

void Tool::display() const {
    std::cout << "Tool ID: " << _tool_id << "\n"
                << "Server Address: " << _server_address << "\n"
                << "Server Port: " << _server_port << "\n"
                << "Version: " << _version << "\n";
}


Sender::Sender(const std::string& serverIp, int port) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sockfd){
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }

    _serverAddres.sin_family = AF_INET;
    _serverAddres.sin_port = htons(port);

    if (inet_pton(AF_INET, serverIp.c_str(), &_serverAddres.sin_addr) <= 0){
        std::cerr << "problem with givven address" <<std::endl;
        exit(1);
    }
    if (connect(sockfd, (struct sockaddr*)&_serverAddres,sizeof(_serverAddres)) < 0){
        std::cerr << "Failed To Connect " << serverIp << "  exiting .." <<  std::endl;
        exit(1);
    }
}

void Sender::sendMessage(const std::string& message){
    size_t bytesent = send(sockfd, message.c_str(), message.length(), 0);
    if(bytesent < 0){
        std::cerr << "Error Sending " <<std::endl;
    } else{
        std::cout << "Message Send Successfully" << std::endl;
    }
}

Sender::~Sender(){
    close(sockfd);
    std::cout << "closing Socket" << std::endl;
}

void FlyweightFactory::sendMessageToTool(const Tool& tool, const std::string& message){
    std::string server_ip = tool.getServerAddress();
    int server_port = tool.getServerPort();

    auto it = senderMap.find(server_ip);

    if(it == senderMap.end()){
        std::shared_ptr<Sender> newSender = std::make_shared<Sender>(server_ip, server_port);
        senderMap[server_ip] = newSender;
        newSender->sendMessage(message);
    }
    else{
        it->second->sendMessage(message);
    }
}



std::string ToolGenerator::generateToolId() {
    std::ostringstream oss;
    std::uniform_int_distribution<int> dist(0, 15);
    for (int i = 0; i < 12; ++i) {
        int hex_digit = dist(gen);
        oss << std::hex << std::nouppercase << hex_digit;
    }
    return oss.str();
}

int ToolGenerator::getPortForAddress(const std::string &address) {
    static const std::unordered_map<std::string, int> address_port_map = {
        {"172.17.0.2", 12345},
        {"172.17.0.3", 12346},
        {"172.17.0.4", 12347}};
    return address_port_map.at(address);
}

Tool ToolGenerator::generateTool() {
    static const std::vector<std::string> server_addresses = {"172.17.0.2", "172.17.0.3", "172.17.0.4"};
    static const std::vector<int> versions = {12345, 12346, 12347};

    std::uniform_int_distribution<size_t> address_dist(0, server_addresses.size() - 1);
    std::uniform_int_distribution<size_t> version_dist(0, versions.size() - 1);

    std::string tool_id = generateToolId();
    std::string server_address = server_addresses[address_dist(gen)];
    int server_port = getPortForAddress(server_address);
    int version = versions[version_dist(gen)];

    return Tool(tool_id, server_address, server_port, version);
}


// int main(void){

//     FlyweightFactory factory;

//     ToolGenerator generator;

//     Tool tools[TOOL_NUMBER];
//     for (int i=0; i < TOOL_NUMBER ; i++){
//         tools[i] = generator.generateTool();
//         factory.sendMessageToTool(tools[i], "{\nToolId: " + tools[i].getToolId() + ",\nVersion: " + std::to_string(tools[i].getVersion()) + "\n}\n");
//     }

//     return 0;
// }

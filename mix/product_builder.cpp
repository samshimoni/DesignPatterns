#include "product_builder.h"


std::string CommunicationMetadata::getProperties(){
    std::stringstream json;
    json << ",\n\t\"communicationMetadata\":\n\t{\n" <<
    "\t\t\"srcIp\":\" " << srcIp << "\",\n" <<
    "\t\t\"srcPort\":\" " << srcPort << "\",\n" <<
    "\t\t\"dstIp\":\" " << dstIp << "\",\n" <<
    "\t\t\"dstPort\":\" " << dstPort << "\",\n";
    
    json << "\t}\n";
    return json.str();
}

std::string ArpadProductAdditionalProperties::getProperties() const {
    return "\t\"arp_product\": \n\t\{\n\t\t\"ipAddress\": \"" + ipAddress + "\",\n\t\t\"macAddress\": \"" + macAddress + "\"\n\t}"   ;
}

std::string Product::toJson() const {
    std::stringstream json;
    json << "{\n" << "\t\"tool_id\":\" " << tool_id << "\",\n" <<
    "\t\"version\":\" " << version << "\",\n" <<
    "\t\"communicator\":\" " << communicator << "\",\n" <<
    "\t\"token\":\" " << token << "\",\n";

    if (additionalProperties) {
        json << additionalProperties->getProperties();
    }
    if (communicationMetadata) {
        json << communicationMetadata->getProperties();
    }

    json << "\n}";
    return json.str();
}

ProductBuilder::ProductBuilder() {
    product = std::make_unique<Product>();
}

void ProductBuilder::buildToolId(const std::string& tool_id) {
    product->tool_id = tool_id;
}

void ProductBuilder::buildToken(){
    product->token = "tcp|1234567890abcdefg";
}

void ProductBuilder::buildVersion(int version){
    product->version = version;
}

void ProductBuilder::buildCommunicator(){
    product->communicator = "TcpCommunicator";
}

void ProductBuilder::buildCommunicationMetadata(const std::string& serverAddress, int serverPort){
    product->communicationMetadata = std::make_unique<CommunicationMetadata>("192.168.1.1", 8000, serverAddress, serverPort);
}

std::unique_ptr<Product> ProductBuilder::getProduct() { return std::move(product); }

void ArpadProductBuilder::buildAdditionalProperties() {
    product->additionalProperties = std::make_unique<ArpadProductAdditionalProperties>("192.168.1.3", "abcdef123456");
}


void ProductDirector::construct(ProductBuilder& builder, Tool& tool){
    builder.buildToolId(tool.getToolId());
    builder.buildVersion(tool.getVersion());
    builder.buildCommunicator();
    builder.buildToken();
    builder.buildAdditionalProperties();  
    builder.buildCommunicationMetadata(tool.getServerAddress(), tool.getServerPort());      
}


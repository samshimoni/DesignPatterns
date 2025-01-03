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

void ProductBuilder::buildToolId(Tool& tool) {
    product->tool_id = tool.getToolId();
}

void ProductBuilder::buildToken(){
    product->token = "tcp|1234567890abcdefg";
}

void ProductBuilder::buildVersion(Tool& tool){
    product->version = tool.getVersion();
}

void ProductBuilder::buildCommunicator(){
    product->communicator = "TcpCommunicator";
}

void ProductBuilder::buildCommunicationMetadata(){
    product->communicationMetadata = std::make_unique<CommunicationMetadata>("192.168.1.1", 8000, "192.168.1.64", 50017);
}

std::unique_ptr<Product> ProductBuilder::getProduct() { return std::move(product); }

void ArpadProductBuilder::buildAdditionalProperties() {
    product->additionalProperties = std::make_unique<ArpadProductAdditionalProperties>("192.168.1.3", "abcdef123456");
}


void ProductDirector::construct(ProductBuilder& builder, Tool& tool){
    builder.buildToolId(tool);
    builder.buildVersion(tool);
    builder.buildCommunicator();
    builder.buildToken();
    builder.buildAdditionalProperties();  
    builder.buildCommunicationMetadata();      
}




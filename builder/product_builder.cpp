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

std::string SedanAdditionalProperties::getProperties() const {
    return "\t\"roof_color\": \" " + roof_color + "\"";
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

void ProductBuilder::buildToolId() {
    product->tool_id = "abcdef123456";
}

void ProductBuilder::buildToken(){
    product->token = "tcp|1234567890abcdefg";
}

void ProductBuilder::buildVersion(){
    product->version = 123456789;
}

void ProductBuilder::buildCommunicator(){
    product->communicator = "TcpCommunicator";
}

void ProductBuilder::buildCommunicationMetadata(){
    product->communicationMetadata = std::make_unique<CommunicationMetadata>("192.168.1.1", 8000, "192.168.1.64", 50017);
}

std::unique_ptr<Product> ProductBuilder::getProduct() { return std::move(product); }

void ABuilder::buildAdditionalProperties() {
    product->additionalProperties = std::make_unique<SedanAdditionalProperties>("Black");
}


void ProductDirector::construct(ProductBuilder& builder){
    builder.buildToolId();
    builder.buildVersion();
    builder.buildCommunicator();
    builder.buildToken();
    builder.buildAdditionalProperties();  
    builder.buildCommunicationMetadata();      
}


int main(){
    ProductDirector director;
    ABuilder aBuilder;
    director.construct(aBuilder);

    std::unique_ptr<Product> aProduct = aBuilder.getProduct();

    std::cout << aProduct->toJson() << std::endl;
}



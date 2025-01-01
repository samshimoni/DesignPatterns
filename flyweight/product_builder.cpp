#include <iostream>
#include <memory>
#include <string>
#include <sstream>




class CommunicationMetadata {
private:
    std::string srcIp;
    int srcPort;
    std::string dstIp;
    int dstPort;

public:
    CommunicationMetadata(std::string srcIp, int srcPort, std::string dstIp, int dstPort) : 
        srcIp(srcIp),
        srcPort(srcPort),
        dstIp(dstIp),
        dstPort(dstPort) {}

    std::string getProperties(){
        std::stringstream json;
        json << ",\n\t\"communicationMetadata\":\n\t{\n" <<
        "\t\t\"srcIp\":\" " << srcIp << "\",\n" <<
        "\t\t\"srcPort\":\" " << srcPort << "\",\n" <<
        "\t\t\"dstIp\":\" " << dstIp << "\",\n" <<
        "\t\t\"dstPort\":\" " << dstPort << "\",\n";
        
        json << "\t}\n";
        return json.str();
    }
};

class IAdditinalProperties{
public:
    virtual std::string getProperties() const = 0;
    virtual ~IAdditinalProperties() = default;
};

class SedanAdditionalProperties : public IAdditinalProperties{
public:
    std::string roof_color;
    SedanAdditionalProperties(const std::string& roof_color) : roof_color(roof_color){}

    std::string getProperties() const override {
        return "\t\"roof_color\": \" " + roof_color + "\"";
    }
};


class Product {
public:
    std::string token;
    std::string communicator;
    int version;
    std::string tool_id;
    
    std::unique_ptr<CommunicationMetadata> communicationMetadata;
    std::unique_ptr<IAdditinalProperties> additionalProperties;

    std::string toJson() const {
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
};

class ProductBuilder{
protected:
    std::unique_ptr<Product> product;
public:
    ProductBuilder() {
        product = std::make_unique<Product>();
    }

    virtual void buildAdditionalProperties() = 0;

    void buildToolId() {
        product->tool_id = "abcdef123456";
    }

    void buildToken(){
        product->token = "tcp|1234567890abcdefg";
    }

    void buildVersion(){
        product->version = 123456789;
    }

    void buildCommunicator(){
        product->communicator = "TcpCommunicator";
    }

    void buildCommunicationMetadata(){
        product->communicationMetadata = std::make_unique<CommunicationMetadata>("192.168.1.1", 8000, "192.168.1.64", 50017);
    }

    std::unique_ptr<Product> getProduct() { return std::move(product); }
    virtual ~ProductBuilder() {}
};


class ABuilder : public ProductBuilder{
public:
    void buildAdditionalProperties() override {
        product->additionalProperties = std::make_unique<SedanAdditionalProperties>("Black");
    }
};

class ProductDirector{
public:
    void construct(ProductBuilder& builder){
        builder.buildToolId();
        builder.buildVersion();
        builder.buildCommunicator();
        builder.buildToken();
        builder.buildAdditionalProperties();  
        builder.buildCommunicationMetadata();      
    }
};

int main(){
    ProductDirector director;
    ABuilder aBuilder;
    director.construct(aBuilder);

    std::unique_ptr<Product> aProduct = aBuilder.getProduct();

    std::cout << aProduct->toJson() << std::endl;
}



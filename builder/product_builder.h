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

    std::string getProperties();
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

    std::string getProperties() const override;
};


class Product {
public:
    std::string token;
    std::string communicator;
    int version;
    std::string tool_id;
    
    std::unique_ptr<CommunicationMetadata> communicationMetadata;
    std::unique_ptr<IAdditinalProperties> additionalProperties;

    std::string toJson() const;
};


class ProductBuilder{
protected:
    std::unique_ptr<Product> product;
public:
    ProductBuilder();

    virtual void buildAdditionalProperties() = 0;
    void buildToolId();
    void buildToken();
    void buildVersion();
    void buildCommunicator();
    void buildCommunicationMetadata();

    std::unique_ptr<Product> getProduct();
    virtual ~ProductBuilder() = default;
};

class ABuilder : public ProductBuilder{
public:
    void buildAdditionalProperties() override;
};


class ProductDirector{
public:
    void construct(ProductBuilder& builder);
};

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include "flyweight.h"




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

class ArpadProductAdditionalProperties : public IAdditinalProperties{
public:
    std::string ipAddress;
    std::string macAddress;
    ArpadProductAdditionalProperties(const std::string& ipAddress, const std::string& macAddress) : ipAddress(ipAddress), macAddress(macAddress){}

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
    void buildToolId(Tool& tool);
    void buildToken();
    void buildVersion(Tool& tool);
    void buildCommunicator();
    void buildCommunicationMetadata();

    std::unique_ptr<Product> getProduct();
    virtual ~ProductBuilder() = default;
};

class ArpadProductBuilder : public ProductBuilder{
public:
    void buildAdditionalProperties() override;
};


class ProductDirector{
public:
    void construct(ProductBuilder& builder, Tool& tool);
};

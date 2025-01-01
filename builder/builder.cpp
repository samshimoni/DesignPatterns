#include <iostream>
#include <memory>
#include <string>
#include <sstream>

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


class Car {
public:
    std::string model;
    std::string engine;
    int weels;
    std::string color;
    std::unique_ptr<IAdditinalProperties> additionalProperties;

    std::string toJson() const {
        std::stringstream json;
        json << "{\n" << "\t\"model\":\" " << model << "\",\n" <<
        "\t\"engine\":\" " << engine << "\",\n" <<
        "\t\"weels\":\" " << weels << "\",\n" <<
        "\t\"color\":\" " << color << "\",\n";

        if (additionalProperties) {
            json << additionalProperties->getProperties();
        }

        json << "\n}";
        return json.str();
    }
};

class CarBuilder{
protected:
    std::unique_ptr<Car> car;
public:
    CarBuilder() {
        car = std::make_unique<Car>();
    }

    virtual void buildModel() = 0;
    virtual void buildEngine() = 0;
    virtual void buildWeels() = 0;
    virtual void buildColor() = 0;
    virtual void buildAdditionalProperties() = 0;

    std::unique_ptr<Car> getCar() { return std::move(car); }
    virtual ~CarBuilder() {}
};


class SedanBuilder : public CarBuilder{
public:
    void buildModel() override { car->model = "sedan"; }
    void buildEngine() override { car->engine = "V8"; }
    void buildWeels() override { car->weels = 4; }
    void buildColor() override { car->color = "Red"; }

    void buildAdditionalProperties() override {
        car->additionalProperties = std::make_unique<SedanAdditionalProperties>("Black");
    }
};

class CarDirector{
public:
    void construct(CarBuilder& builder){
        builder.buildModel();
        builder.buildEngine();
        builder.buildWeels();
        builder.buildColor();
        builder.buildAdditionalProperties();        
    }
};

int main(){
    CarDirector director;
    SedanBuilder sedanBuilder;
    director.construct(sedanBuilder);

    std::unique_ptr<Car> sedan = sedanBuilder.getCar();

    std::cout << sedan->toJson() << std::endl;
}



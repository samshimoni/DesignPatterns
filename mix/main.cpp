#include "flyweight.h"
#include "product_builder.h"


int main(){
    FlyweightFactory factory;
    ToolGenerator generator;
    Tool tools[TOOL_NUMBER];
    for (int i=0; i < TOOL_NUMBER ; i++){
        tools[i] = generator.generateTool();
        // factory.sendMessageToTool(tools[i], "{\nToolId: " + tools[i].getToolId() + ",\nVersion: " + std::to_string(tools[i].getVersion()) + "\n}\n");
        // factory.sendMessageToTool(tools[i], aProduct->toJson());
    }


    ProductDirector director;
    ArpadProductBuilder arpadProductBuilders[TOOL_NUMBER];

    for (int i=0; i< TOOL_NUMBER; i++){
        director.construct(arpadProductBuilders[i], tools[i]);
        std::unique_ptr<Product> arpadProduct = arpadProductBuilders[i].getProduct();
        std::cout << arpadProduct->toJson() << std::endl;
        factory.sendMessageToTool(tools[i], arpadProduct->toJson());
    }
}
#include "flyweight.h"
#include "product_builder.h"


int main(){
    FlyweightFactory factory;
    ToolGenerator generator;
    Tool tools[TOOL_NUMBER];

    ProductDirector director;
    ArpadProductBuilder arpadProductBuilders[TOOL_NUMBER];

    for (int i=0; i < TOOL_NUMBER ; i++){
        tools[i] = generator.generateTool();
    }

    for (int i=0; i< TOOL_NUMBER; i++){
        director.construct(arpadProductBuilders[i], tools[i]);
        std::unique_ptr<Product> arpadProduct = arpadProductBuilders[i].getProduct();
        // std::cout << arpadProduct->toJson() << std::endl;
        factory.sendMessageToTool(tools[i], arpadProduct->toJson());
    }
}
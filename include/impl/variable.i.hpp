#include <vector>       // Vector manipulation  -> std::vector, ...
#include <iostream>     // I/O operations       -> std::cout,   ...

namespace ccsat{
    
void Variable::setValue(std::string input){
    value = input;
}

Variable::Variable() {}
    
Variable::Variable(std::string i){
    setValue(i);
}
    
std::string Variable::getValue(){
    return value;
}

}   // namespace 'ccsat'

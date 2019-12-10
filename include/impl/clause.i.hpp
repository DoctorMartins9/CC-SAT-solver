#include <vector>       // Vector manipulation  -> std::vector, ...
#include <iostream>     // I/O operations       -> std::cout,   ...

namespace ccsat{
        
    void Clause::setSecondValue(Variable input){
        v2 = input;
    }

    void Clause::setFirstValue(Variable input){
        v1 = input;
    }
    
    void Clause::setEqual(bool eq){
        is_equal = eq;
    }

    Clause::Clause(){}
    
    Clause::Clause(Variable v_1, Variable v_2, bool is_equal){
        setFirstValue(v_1);
        setSecondValue(v_2);
        setEqual(is_equal);
    }

    std::string Clause::getClause(){
        std::string str = "";
        str += v1.getValue();
        std::string eq = is_equal ? "=" : "!=" ;
        str += eq;
        str += v2.getValue();
        return str;
    }

    Variable Clause::getFirstVariable(){
        return v1;
    }
    
    Variable Clause::getSecondVariable(){
        return v2;
    }
    
    bool Clause::isEqual(){
        return is_equal;
    }

}   // namespace 'ccsat'

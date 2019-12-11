namespace ccsat{

    Sat::Sat(){}

    Sat::Sat(Formula input ){
        f = input;
    }

    Sat::Sat(std::string input){
        initialize_DAG(input);
    }

    Formula Sat::get_formula(){
        return f;
    }

    void Sat::set_formula(Formula input){
        f = input;
    }

    void Sat::initialize_DAG(std::string input){

        
        // Divide clauses_string of formula_string
        std::vector<std::string> a_clause;
        while(input.find_first_of("&") != std::string::npos){
            uint64_t end = input.find_first_of("&");
            a_clause.push_back(input.substr(0,end));
            input.erase(0,end+1);
        }
        a_clause.push_back(input);

        // Divide variables_string of clause_string
        std::vector<std::string> a_node;
        std::vector<bool> a_sign;

        for (int i = 0; i < a_clause.size(); i++){
            // equal
            if(a_clause[i].find_first_of("!") == std::string::npos){
                uint64_t end = a_clause[i].find_first_of("=");
                a_node.push_back(a_clause[i].substr(0,end));
                a_node.push_back(a_clause[i].substr(end+1,a_clause[i].size()-1));
                a_sign.push_back(true);
            }
            // not-equal
            else{
                uint64_t end = a_clause[i].find_first_of("!");
                a_node.push_back(a_clause[i].substr(0,end));
                a_node.push_back(a_clause[i].substr(end+2,a_clause[i].size()-1));
                a_sign.push_back(false);
            }
        }
        std::cout << a_node[0] << std::endl;
        std::cout << a_node[1] << std::endl;
        std::cout << a_node[2] << std::endl;
        std::cout << a_node[3] << std::endl;
    }

}   // namespace 'ccsat'

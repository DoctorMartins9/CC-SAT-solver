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

    std::vector<Node> Sat::get_nodes(){
        return n_set;
    }

    // Return arguments of a function
    std::vector<std::string> Sat::split_arguments(std::string s){
        std::vector<std::string> splitted;
        // If there is only a costant
        if(s.find_first_of(",") == std::string::npos){
            splitted.push_back(s);
            return splitted;
        }
        
        // If there is a comma
        uint64_t level = 0;
        std::vector<uint64_t> comma_pos;
        comma_pos.push_back(0);
        for(uint64_t i = 0; i < s.size(); i++){
            if(s[i] == '('){
                level++;
            }
            else if(s[i] == ')'){
                level--;
            }
            else if(s[i] == ',' && level == 0){
                comma_pos.push_back(i);
            }
        }

        // Split the string
        // No commas
        if(comma_pos.size()==1){
            splitted.push_back(s);
            return splitted;
        }
        // 2 commas
        if(comma_pos.size()==2){
            for(uint64_t i = 1; i < comma_pos.size();i++){
                uint64_t delta = comma_pos[i] - comma_pos[i-1];
                std::string string = s.substr(comma_pos[i-1],delta);
                splitted.push_back(string);
            }
            splitted.push_back(s.substr(comma_pos[comma_pos.size()-1]+1));
            return splitted;
        }
        // More than 2 comma
        // Split the first
        splitted.push_back(s.substr(0,comma_pos[1]));
        // Split the n-1
        for(uint64_t i = 2; i < comma_pos.size();i++){
            uint64_t delta = comma_pos[i] -1 - comma_pos[i-1];
            std::string string = s.substr(comma_pos[i-1] +1 ,delta);
            splitted.push_back(string);
        }
        // Split the last
        splitted.push_back(s.substr(comma_pos[comma_pos.size()-1]+1));
        return splitted;
    }

    // Return arguments of a function
    static std::vector<std::string> split(std::string s){
        std::vector<std::string> splitted;
        // If there is only a costant
        if(s.find_first_of(",") == std::string::npos){
            splitted.push_back(s);
            return splitted;
        }
        
        // If there is a comma
        uint64_t level = 0;
        std::vector<uint64_t> comma_pos;
        comma_pos.push_back(0);
        for(uint64_t i = 0; i < s.size(); i++){
            if(s[i] == '('){
                level++;
            }
            else if(s[i] == ')'){
                level--;
            }
            else if(s[i] == ',' && level == 0){
                comma_pos.push_back(i);
            }
        }

        // Split the string
        // No commas
        if(comma_pos.size()==1){
            splitted.push_back(s);
            return splitted;
        }
        // 2 commas
        if(comma_pos.size()==2){
            for(uint64_t i = 1; i < comma_pos.size();i++){
                uint64_t delta = comma_pos[i] - comma_pos[i-1];
                std::string string = s.substr(comma_pos[i-1],delta);
                splitted.push_back(string);
            }
            splitted.push_back(s.substr(comma_pos[comma_pos.size()-1]+1));
            return splitted;
        }
        // More than 2 comma
        // Split the first
        splitted.push_back(s.substr(0,comma_pos[1]));
        // Split the n-1
        for(uint64_t i = 2; i < comma_pos.size();i++){
            uint64_t delta = comma_pos[i] -1 - comma_pos[i-1];
            std::string string = s.substr(comma_pos[i-1] +1 ,delta);
            splitted.push_back(string);
        }
        // Split the last
        splitted.push_back(s.substr(comma_pos[comma_pos.size()-1]+1));
        return splitted;
    }

    // Transforma a string into a node
    uint64_t Sat::transform_node(std::string n){
            #ifdef PARSER
            std::cout << "transform_node -> "<< n << std::endl;
            #endif
            // Costant
            if(n.find_first_of("(") == std::string::npos){
                #ifdef PARSER
                std::cout << "costant <-"<< n << std::endl;
                #endif
                // If the costant is initialized yet
                for(int j = 0; j < n_set.size() ; j++){
                    if(n_set[j].get_fn() == n){
                        return n_set[j].get_id();
                    }
                }
                // Add the node
                uint64_t id = static_cast<uint64_t>(n_set.size());
                std::vector<uint64_t> args;
                std::vector<uint64_t> ccpar;
                Node node = Node(n,id,args,id,ccpar);
                n_set.push_back(node);
                return id;
            }
            // Function
            else {
                // Function name
                std::string fun_name = n.substr(0,n.find_first_of("("));
                // Function argument
                int end = n.find_last_of(")");
                int init = n.find_first_of("(");
                std::string fun_argument = n.substr(init+1,end-(init+1));
                
                #ifdef PARSER
                std::cout << "function <- "<< fun_name << " : " << fun_argument << std::endl;
                #endif

                // We have arguments list
                std::vector<std::string> args_list = split_arguments(fun_argument);
                
                // Now we have to capture the arguments id
                std::vector<uint64_t> id_args;
                for(int i = 0; i < args_list.size();i++){
                    id_args.push_back(transform_node(args_list[i]));
                }
                // Find if exists already this function
                for(uint64_t i = 0; i < n_set.size() ; i++ ){
                    if(fun_name == n_set[i].get_fn()){
                        if( id_args == n_set[i].get_args() )
                            return i;
                    }
                }
                // Finally we can create the function node with the right arguments
                uint64_t id = n_set.size();
                std::vector<uint64_t> ccpar;
                Node node = Node(fun_name,id,id_args,id,ccpar);
                n_set.push_back(node);
                return id;
            }
            // Return 999 in case of error
            assert(false);
            return 999;
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
            #ifdef PARSER
            std::cout << a_clause[i] << std::endl;
            #endif
            // !atom(x) -> cons(car(x),cdr(x)) = x
            if(a_clause[i].find("!atom") != std::string::npos ){
                std::string s =  a_clause[i].substr(6,a_clause[i].rfind(")")-6);
                std::string cons = "cons(car(" + s + "),cdr(" + s + "))";
                a_node.push_back(cons);
                a_node.push_back(s);
                a_sign.push_back(true);
            }
            // atom(x)
            else if(a_clause[i].find("atom") != std::string::npos ){
                std::string s = a_clause[i].substr(5,a_clause[i].rfind(")")-5);
                uint64_t id = transform_node(s);
                atoms.push_back(id);
                #ifdef PARSER
                std::cout << "atom <- " << id << std::endl;
                #endif
                
            }
            // equal
            else if(a_clause[i].find_first_of("!") == std::string::npos){
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

        // From node string to Node class in n_set
        std::vector<uint64_t> id_set;
        for(int i = 0; i < a_node.size();i++){
            id_set.push_back(transform_node(a_node[i]));
        }

        // Create formula
        for(int i = 0; i < a_sign.size(); i++){
            Clause c = Clause(n_set[id_set[2*i]],n_set[id_set[2*i+1]],a_sign[i]);
            f.add_clause(c);
        }

        // Now we have to assign ccpar
        for(uint64_t i = 0; i < n_set.size() ; i++ ){
            // If is a function
            if(n_set[i].get_args().size() != 0){
               std::vector<uint64_t> id_sons = n_set[i].get_args();
               for(int j = 0; j < id_sons.size();j++){
                   n_set[id_sons[j]].add_ccpar(i);
               } 
            }
        }
    }

    static std::vector<std::string> detect_store(std::string input){
        #ifdef DEBUG
        std::cout << "-----------\n" << "detect store" << std::endl;
        #endif
        std::string initial = input;
        // Divide clauses_string of formula_string
        std::vector<std::string> a_clause;
        while(input.find_first_of("&") != std::string::npos){
            uint64_t end = input.find_first_of("&");
            a_clause.push_back(input.substr(0,end));
            input.erase(0,end+1);
        }
        a_clause.push_back(input);
        // Divide variables_string of clause_string
        std::string to_add;
        std::vector<std::string> a_node;
        std::vector<bool> a_sign;
        for (int i = 0; i < a_clause.size(); i++){
            // !atom(x)
            if(a_clause[i].find("!atom") != std::string::npos ){
                to_add += "a_clause[i]"; 
                to_add += "&";
            }
            // atom(x)
            else if(a_clause[i].find("atom") != std::string::npos ){
                to_add += "a_clause[i]"; 
                to_add += "&";                
            }
            // equal
            else if(a_clause[i].find_first_of("!") == std::string::npos){
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

        // Detect if there aren't store
        std::vector<std::string> formulas;
        for(int i = 0; i < a_node.size(); i++){
            // Change select(store) -> 1 | 2
            if(a_node[i].find("select(store(")!= std::string::npos ){
                #ifdef DEBUG
                std::cout << a_node[i] << std::endl;
                #endif
                
                // Split into -> store(...),j
                int start_sel = a_node[i].find_first_of("(")+1;
                int end_sel = a_node[i].find_last_of(")");
                std::string select_string = a_node[i].substr(start_sel,end_sel-start_sel);
                std::vector<std::string> select_args = split(select_string);
                
                // Split into -> x,i,v
                int start_sto = select_args[0].find_first_of("(")+1;
                int end_sto = select_args[0].find_last_of(")");
                std::string store_string = select_args[0].substr(start_sto,end_sto-start_sto);
                std::vector<std::string> store_args = split(store_string);
                #ifdef DEBUG
                std::cout << store_string << std::endl;
                std::cout << store_args[0] << " " << store_args[1] << " " << store_args[2] << std::endl;
                #endif

                // Detect the place to inject new clauses
                int init = initial.find(a_node[i]);
                int length = a_node[i].size();
                #ifdef DEBUG
                std::cout << "_____" << std::endl;
                std::cout << "1: " << initial.substr(0,init) << std::endl;
                std::cout << "2: " << initial.substr(init+length) << std::endl;                
                std::cout << "_____" << std::endl;
                #endif
                std::string part1 = initial.substr(0,init);
                std::string part2 = initial.substr(init+length);
                
                // Create first string formula
                std::string first = "";
                std::string second = "";

                // Detect the left or the right operands
                if(part1[part1.size()-1]=='='){
                    first = first + store_args[2]+ "&";
                    first = first + select_args[1] + "=" + store_args[1];
                    second = second + "select(" + store_args[0] + "," + select_args[1] + ")"+ "&";
                    second = second + select_args[1] + "!=" + store_args[1];
                }
                else{
                    first = first + select_args[1] + "=" + store_args[1] + "&";
                    first += store_args[2];
                    second = second + select_args[1] + "!=" + store_args[1] + "&";
                    second = second + "select(" + store_args[0] + "," + select_args[1] + ")";
                }    
                first = part1 + first + part2;
                second = part1 + second + part2;

                #ifdef DEBUG
                std::cout << "_____" << std::endl;
                std::cout << "1: " << first << std::endl;
                std::cout << "2: " << second << std::endl;                
                std::cout << "_____" << std::endl;
                #endif
                // Exit
                formulas.push_back(first);
                formulas.push_back(second);
                break;
            }
        }
        if(formulas.size()==0){
            #ifdef DEBUG
            std::cout << "store not detected" << "\n-----------" << std::endl;
            #endif
            formulas.push_back(initial);
        }
        #ifdef DEBUG
        for(int i = 0; i < formulas.size(); i ++)
            std::cout << formulas[i] << std::endl;
        #endif
        return formulas;
    }


    // Classic Congruence Closure algorithm

    // FIND i
    uint64_t Sat::FIND(uint64_t index){
        if(n_set[index].get_find() == index)
            return index;
        return FIND(n_set[index].get_find());
    }
    
    // UNION i1 i2
    void Sat::UNION(uint64_t i1, uint64_t i2){

        #ifdef DEBUG
        std::cout << "UNION ";
        std::cout << i1;
        std::cout << " ";
        std::cout << i2 << std::endl;
        #endif
        i1 = n_set[FIND(i1)].get_id();
        i2 = n_set[FIND(i2)].get_id();
        n_set[i2].set_find(n_set[i1].get_find());
        for(int i = 0; i < n_set[i2].get_ccpar().size();i++){
            n_set[i1].add_ccpar(n_set[i2].get_ccpar().at(i));
        }
        std::vector<uint64_t> empty_ccpar;
        n_set[i2].set_ccpar(empty_ccpar);
    }
    
    // CCPAR i
    std::vector<uint64_t> Sat::CCPAR(uint64_t index){
        return n_set[(FIND(index))].get_ccpar();
    }
    
    // CONGRUENT i1 i2
    bool Sat::CONGRUENT(uint64_t i1, uint64_t i2){
        bool congruent1 = ( n_set[i1].get_fn() == n_set[i2].get_fn() ) &&
                         ( n_set[i1].get_args().size() == n_set[i2].get_args().size() );
        
        bool congruent2 = true;
        for(uint64_t i = 0; i < n_set[i1].get_args().size();i++){
            if (FIND(n_set[i1].get_args().at(i)) != FIND(n_set[i1].get_args().at(i)))
                congruent2 = false;
        }

        bool congruent = congruent1 & congruent2;

        #ifdef DEBUG
        std::cout << "CONGRUENT ";
        std::cout << i1;
        std::cout << " ";
        std::cout << i2 ;
        std::cout << " = ";
        std::cout << congruent << std::endl;
        #endif

        return congruent;
    }
    
    // MERGE i1 i2
    void Sat::MERGE(uint64_t i1, uint64_t i2){

        #ifdef DEBUG
        std::cout << "MERGE ";
        std::cout << i1;
        std::cout << " ";
        std::cout << i2 << std::endl;
        #endif
        // if i1 and i2 are not the same
        if(FIND(i1) != FIND(i2) ){
            std::vector<uint64_t> P1 = CCPAR(i1);
            std::vector<uint64_t> P2 = CCPAR(i2);
            UNION(i1,i2);
            // Search for son
            for(uint64_t i = 0; i < P1.size();i++){
                for(uint64_t j = 0; j < P2.size();j++){

                    #ifdef DEBUG
                    std::cout << "MERGE ";
                    std::cout << P1[i];
                    std::cout << " ";
                    std::cout << P2[j];
                    std::cout << " ?" << std::endl;
                    #endif

                    if(FIND(P1[i]) != FIND(P2[j]) && CONGRUENT(P1[i], P2[j]) ){
                        #ifdef DEBUG
                        std::cout << "------------" << std::endl;
                        print_status();
                        std::cout << "------------" << std::endl;
                        #endif                        
                        MERGE(P1[i],P2[j]);
                    }
                }
            }
        }
    }

    // Theory of list
    bool Sat::list_congruence_closure(){
        // Pre-process
        for(uint64_t i = 0; i < n_set.size() ; i++ ){
            if(n_set[i].get_fn() == "cons"){
                // Add car(n) and cdr(n) to DAG (IF NOT EXIST!)
                uint64_t id = n_set.size();
                std::vector<uint64_t> cons_args = n_set[i].get_args();
                std::vector<uint64_t> args;
                std::vector<uint64_t> ccpar;
                args.push_back(i);
                // Search if the node car already exists
                // CAR
                for(uint64_t j = 0; j < n_set.size(); j++){
                    if(n_set[j].get_fn() == "car" && n_set[j].get_args().at(0) == i ){
                        id = j;
                    }
                }
                if(id == n_set.size()){
                    Node car = Node("car",id,args,id,ccpar);
                    n_set.push_back(car);
                }
                n_set[i].add_ccpar(id);
                MERGE(id, n_set[i].get_args().at(0));
                // CDR
                id = n_set.size();
                for(uint64_t j = 0; j < n_set.size(); j++){
                    if(n_set[j].get_fn() == "cdr" && n_set[j].get_args().at(0) == i ){
                        id = j;
                    }
                }
                if(id == n_set.size()){
                    Node cdr = Node("cdr",id,args,id,ccpar);
                    n_set.push_back(cdr);
                }
                n_set[i].add_ccpar(id);
                MERGE(id, n_set[i].get_args().at(1));
            }
        }
        // Theory congruence closure
        if(classic_congruence_closure()){
            #ifdef DEBUG
            std::cout << "Euality theory passed" << std::endl;
            #endif 
            for(uint64_t i = 0; i < atoms.size();i++){
                // Check if an atom is in the same cc of cons
                for(uint64_t j = 0; j < n_set.size();j++){
                    #ifdef DEBUG
                    std::cout << FIND(atoms[i]) << "--" << FIND(j) << std::endl;
                    #endif
                    if(FIND(atoms[i]) == FIND(j) && n_set[j].get_fn()=="cons"){
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    }

    // Theory of equality
    bool Sat::classic_congruence_closure(){
        std::vector<Clause> clause = f.get_formula();
        #ifdef DEBUG
        std::cout << "------------" << std::endl;
        print_status();
        std::cout << "------------" << std::endl;
        #endif
        // For every equality in formula merge
        for(uint64_t i = 0; i < clause.size(); i++){
            if(clause[i].get_equal()){
                MERGE(clause[i].get_first().get_id(),clause[i].get_second().get_id());
            }
        }
        #ifdef DEBUG
        std::cout << "------------" << std::endl;
        print_status();
        std::cout << "------------" << std::endl;
        #endif
        // Check not equality
        for(uint64_t i = 0; i < clause.size(); i++){
            if(!clause[i].get_equal()){
                if(FIND(clause[i].get_first().get_id()) == FIND(clause[i].get_second().get_id()))
                    return false;
            }
        }
        return true;
    }

    void Sat::print_status(){
        std::cout << "node\t\tfind\t\tccpar"<<std::endl;
        std::cout << "________________________________________"<<std::endl;
        std::vector<Node> nodi = n_set;
        for(int i = 0; i < nodi.size() ; i++){
            std::cout << nodi[i].get_id();
            std::cout << nodi[i].get_fn();

            // ARGS PRINT
            if(nodi[i].get_args().size()>0){
                std::cout << "->";
                for (int h = 0; h < nodi[i].get_args().size(); h++)
                    std::cout << nodi[i].get_args().at(h);
            }
            std::cout << "\t\t";

            // FIND PRINT
            std::cout << nodi[i].get_find();
            std::cout << "\t\t";


            // CCPAR PRINT
            if(nodi[i].get_ccpar().size() > 0){
                for (int  h = 0; h < nodi[i].get_ccpar().size(); h++){
                    std::cout << nodi[i].get_ccpar().at(h);
                }
            }
            else{
                std::cout << "-";
            }
            std::cout << std::endl;
            
        }
        std::cout << "________________________________________"<<std::endl;
    }

    static bool well_formed(std::string s){
        // Check if all parentesis are closed
        uint64_t open = 0;
        uint64_t close = 0;
        for(int i = 0; i < s.size() ; i++)
            if(s[i]=='(')
                open++;

        for(int i = 0; i < s.size() ; i++)
            if(s[i]==')')
                close++;

        if(open != close)
            return false;
        return true;
    }

    static bool solve(std::string s){
        if(well_formed(s)){
            // Base case
            if(s.find("select(store(") == std::string::npos){
                Sat sat = Sat(s);
                if(sat.list_congruence_closure()){
                    return true;
                }
                return false;
            }
            // Recursive case
            std::vector<std::string> formulas = detect_store(s); 
            for(int i = 0; i < formulas.size(); i++){
                if(solve(formulas[i])){
                    return true;
                }
            }
            return false;
        }
        // Raise error
        assert(false);
        return true;
    }
    static void solve_threads(std::promise<bool> result , std::string s){
        if(well_formed(s)){
            // Base case
            if(s.find("select(store(") == std::string::npos){
                Sat sat = Sat(s);
                if(sat.list_congruence_closure()){
                    result.set_value(true);
                }
                result.set_value(false);
            }
            // Recursive case
            std::vector<std::string> formulas = detect_store(s); 
            for(int i = 0; i < formulas.size(); i++){
                if(solve(formulas[i])){
                    result.set_value(true);
                }
            }
            result.set_value(false);
        }
        assert(false);
    }
    static bool solve_parallel(std::string s){
        if(well_formed(s)){
            
            // Base case
            if(s.find("select(store(") == std::string::npos){
                Sat sat = Sat(s);
                if(sat.list_congruence_closure()){
                    return true;
                }
                return false;
            }
            
            // Parallelism
            std::vector<std::string> formulas = detect_store(s);
            
            auto first = std::async(std::launch::async,solve, formulas[0]);
            auto second = std::async(std::launch::async,solve, formulas[1]);
            
            bool r1 = first.get();
            bool r2 = second.get();
            if(r1 || r2)
                return true;
            return false;
        }
        // Raise error
        assert(false);
        return true;
    }

    static bool SOLVE(std::string input,std::string mode){
        // Count & split occurrence of "|"
        std::vector<std::string> formula;
        while(input.find_first_of("|") != std::string::npos){
            uint64_t pos = input.find_first_of("|");
            formula.push_back(input.substr(0,pos));
            input = input.substr(pos+1,input.size()-pos);
        }
        formula.push_back(input);

        // Sequential mode
        if(mode == "S"){
            for(int i = 0; i < formula.size(); i++){
                if(solve(formula[i].substr(1,formula[i].size()-2)))
                    return true;
            }
            return false;
        }
        // Parallel mode
        else if(mode == "P"){
            int cores = std::thread::hardware_concurrency();
            cores = 16384;
            int run = int(formula.size()/cores);
            for(int c = 0; c < run ; c++){
                std::vector<std::future<bool>> futures;
                for(int i = 0 ; i < cores ; i++ ){
                    futures.push_back(std::async(std::launch::async,solve,formula[cores*c+i].substr(1,formula[cores*c+i].size()-2)));
                }
                for(int i = 0 ; i < cores ; i++ ){
                    if(futures[i].valid() && futures[i].get()==true)
                        return true;
                }
            }
            return false;
        }
        else{
            std::cout << "Error: wrong mode" << std::endl;
            return false;
        }
    }

}   // namespace 'ccsat'

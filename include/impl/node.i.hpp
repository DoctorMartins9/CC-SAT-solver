namespace ccsat{

Node::Node(){}

Node::Node(std::string fn_i, int id_i, std::vector<int> args_i, 
                             int find_i,std::vector<int> ccpar_i){
    fn = fn_i;
    id = id_i;
    args = args_i;
    find = find_i;
    ccpar = ccpar_i;
}

std::string Node::get_fn(){
    return fn;
}

int Node::get_id(){
    return id;
}

std::vector<int> Node::get_args(){
    return args;
}

std::vector<int> Node::get_ccpar(){
    return ccpar;
}

int Node::get_find(){
    return find;
}

void Node::set_find(int find_i){
    find = find_i;
}

void Node::set_ccpar(std::vector<int> ccpar_i){
    ccpar = ccpar_i;
}

void Node::add_ccpar(int ccpar_i){
    for(int i = 0; i < ccpar.size();i++)
        if(ccpar[i]==ccpar_i)
            return;
    ccpar.push_back(ccpar_i);
}

bool Node::is_equal(Node input){
    return fn == input.get_fn() && id == input.get_id() && args == input.get_args() && find == input.get_find() && ccpar == input.get_ccpar();
}

}   // namespace 'ccsat'

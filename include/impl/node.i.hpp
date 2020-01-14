namespace ccsat{

Node::Node(){}

Node::Node(std::string fn_i, uint_fast16_t id_i, std::vector<uint_fast16_t> args_i, 
                             uint_fast16_t find_i,std::vector<uint_fast16_t> ccpar_i){
    fn = fn_i;
    id = id_i;
    args = args_i;
    find = find_i;
    ccpar = ccpar_i;
}

std::string Node::get_fn(){
    return fn;
}

uint_fast16_t Node::get_id(){
    return id;
}

std::vector<uint_fast16_t> Node::get_args(){
    return args;
}

std::vector<uint_fast16_t> Node::get_ccpar(){
    return ccpar;
}

uint_fast16_t Node::get_find(){
    return find;
}

void Node::set_find(uint_fast16_t find_i){
    find = find_i;
}

void Node::set_ccpar(std::vector<uint_fast16_t> ccpar_i){
    ccpar = ccpar_i;
}

void Node::add_ccpar(uint_fast16_t ccpar_i){
    for(int i = 0; i < ccpar.size();i++)
        if(ccpar[i]==ccpar_i)
            return;
    ccpar.push_back(ccpar_i);
}

bool Node::is_equal(Node input){
    return fn == input.get_fn() && id == input.get_id() && args == input.get_args() && find == input.get_find() && ccpar == input.get_ccpar();
}

}   // namespace 'ccsat'

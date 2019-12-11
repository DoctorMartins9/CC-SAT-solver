namespace ccsat{

Node::Node(){}

Node::Node(std::string fn_i, uint64_t id_i, std::vector<uint64_t> args_i, 
                             uint64_t find_i,std::vector<uint64_t> ccpar_i){
    fn = fn_i;
    id = id_i;
    args = args_i;
    find = find_i;
    ccpar = ccpar_i;
}

std::string Node::get_fn(){
    return fn;
}

uint64_t Node::get_id(){
    return id;
}

std::vector<uint64_t> Node::get_args(){
    return args;
}

std::vector<uint64_t> Node::get_ccpar(){
    return ccpar;
}

uint64_t Node::get_find(){
    return find;
}

void Node::set_find(uint64_t find_i){
    find = find_i;
}

void Node::set_ccpar(std::vector<uint64_t> ccpar_i){
    ccpar = ccpar_i;
}

}   // namespace 'ccsat'

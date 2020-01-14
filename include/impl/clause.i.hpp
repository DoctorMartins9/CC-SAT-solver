namespace ccsat{

    Clause::Clause(){}
    
    Clause::Clause(Node n_1, Node n_2, bool is_equal_i){
        n1 = n_1;
        n2 = n_2;
        is_equal = is_equal_i;
    }
    
    void Clause::set_second(Node input){
    }

    void Clause::set_first(Node input){
    }
    
    void Clause::set_equal(bool eq){
    }

    Node Clause::get_first(){
        return n1;
    }
    
    Node Clause::get_second(){
        return n2;
    }
    
    bool Clause::get_equal(){
        return is_equal;
    }

    bool Clause::equal(Clause input){
        return n1.is_equal(input.get_first()) && n2.is_equal(input.get_second()) && is_equal == input.get_equal();
    }

}   // namespace 'ccsat'

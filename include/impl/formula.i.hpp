namespace ccsat{

    Formula::Formula(){}

    Formula::Formula(std::vector<Clause> input ){
        v_set = input;
    }

    uint64_t Formula::get_size(){
        return v_set.size();
    }

    void Formula::add_clause(Clause input){
        v_set.push_back(input);
    }

    std::vector<Clause> Formula::get_formula(){
        return v_set;
    }

}   // namespace 'ccsat'

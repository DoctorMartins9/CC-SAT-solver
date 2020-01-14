namespace ccsat{

    Formula::Formula(){}

    Formula::Formula(std::vector<Clause> input ){
        v_set = input;
    }

    uint_fast16_t Formula::get_size(){
        return v_set.size();
    }

    void Formula::add_clause(Clause input){
        v_set.push_back(input);
    }

    std::vector<Clause> Formula::get_formula(){
        return v_set;
    }

    std::string Formula::get_string(){
        std::string str = "";
        for(int i = 0; i < v_set.size() ; i++){
            str += v_set[i].get_first().get_fn();
            if(v_set[i].get_first().get_args().size() != 0){
                str +="(";
                for(int j = 0; j<v_set[i].get_first().get_args().size();j++){
                    str += v_set[i].get_first().get_args().at(j);
                }
                str += ")";
            }
            std::string segno = v_set[i].get_equal() ? "=" : "!=";
            str += segno;
            str += v_set[i].get_second().get_fn();
            if(i != v_set.size()-1)
                str += "&";
        }
        return str;
    }

}   // namespace 'ccsat'

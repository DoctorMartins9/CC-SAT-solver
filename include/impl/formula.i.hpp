namespace ccsat{

    Formula::Formula(){}

    Formula::Formula(std::vector<Clause> input ){
        v_set = input;
    }

    uint64_t Formula::getSize(){
        return v_set.size();
    }

    std::string Formula::getFormula(){
        
        std::string str = "F:{ ";
        
        for( uint64_t i = 0 ; i < getSize() ; i++ ){
            str += v_set[i].getClause();
            if(i != getSize()-1)
                str += " ; ";
        }
        str += " }";
        return str;
    }

    void Formula::addClause(Clause input){
        v_set.push_back(input);
    }

}   // namespace 'ccsat'

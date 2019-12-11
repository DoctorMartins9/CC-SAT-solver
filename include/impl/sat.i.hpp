namespace ccsat{

    Sat::Sat(){}

    Sat::Sat(Formula input ){
        f = input;
    }

    Formula Sat::get_formula(){
        return f;
    }

    void Sat::set_formula(Formula input){
        f = input;
    }

}   // namespace 'ccsat'

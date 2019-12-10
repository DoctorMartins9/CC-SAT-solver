namespace ccsat{

    CC::CC(){}

    CC::CC(Formula input ){
        f = input;
    }

    Formula CC::getFormula(){
        return f;
    }

    void CC::setFormula(Formula input){
        f = input;
    }

}   // namespace 'ccsat'

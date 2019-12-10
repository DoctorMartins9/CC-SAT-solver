namespace ccsat{
    
void Variable::setValue(std::string input){
    value = input;
}

Variable::Variable() {}
    
Variable::Variable(std::string i){
    setValue(i);
}
    
std::string Variable::getValue(){
    return value;
}

}   // namespace 'ccsat'

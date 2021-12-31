struct astNodeBase;

//any poly object of 15 ptr sizes
using astNode = ratgr::PolyObject<astNodeBase, 16>;


struct astNodeBase{
    virtual std::string_view NodeName();

    virtual ~astNode();
}




struct astFunctionDefinition {
    static const char[] name = "FunctionDefinition";
    virtual std::string_view NodeName() { return name; }

    ~astFunctionDefinition() override {};
}

struct ObjectDefinition {

} 



LoadedSymbols: SymbolTable

SymbolWaiting 












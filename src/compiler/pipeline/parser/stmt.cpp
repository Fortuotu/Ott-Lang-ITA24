#include "parser.hpp"

Stmt* Parser::stmt() {
    return nullptr;
}

Decl* Parser::parse_decl() {
    consumer.check();

    switch (consumer.get_type()) {
    case TokenType::KW_FUNCTION:
        return parse_func_decl();
    default:
        return nullptr;
    }    
} 

FuncDecl* Parser::parse_func_decl() {
    FuncDecl func_decl;

    consumer.consume(TokenType::KW_FUNCTION);
    consumer.consume(TokenType::)
}

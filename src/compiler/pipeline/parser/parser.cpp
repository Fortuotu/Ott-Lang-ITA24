#include "compiler/pipeline/parser/parser.hpp"

AST* Parser::parse() {
    AST* ast = new AST();

    Stmt* stmt = nullptr;

    while (!consumer.out_of_tokens()) {
        stmt = parse_stmt();
        if (!stmt) {
            std::cout << "Syntax error.\n";
            std::exit(EXIT_FAILURE);
        }

        ast->stmts.push_back(stmt);
    }

    ParseAnalyser analyser;
    analyser.analyze(ast);

    return ast;
}

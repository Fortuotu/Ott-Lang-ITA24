#include "compiler/pipeline/parser/parser.hpp"

AST* Parser::parse() {
    AST* ast = new AST();

    Stmt* decl = nullptr;

    while (!consumer.out_of_tokens()) {
        decl = parse_decl();
        if (!decl) {
            std::cout << "Syntax error.\n";
            std::exit(EXIT_FAILURE);
        }

        ast->decls.push_back(decl);
    }

    if (!env.all_future_defs_assured()) {
        std::cout << "All names not defined.\n";
        std::exit(EXIT_FAILURE);
    }

    return ast;
}

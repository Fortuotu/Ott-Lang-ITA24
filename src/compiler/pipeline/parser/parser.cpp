#include "compiler/pipeline/parser/parser.hpp"

AST* Parser::parse() {
    Decl* node = nullptr;

    while ((node = parse_decl()) != nullptr) {
        ast->decls.push_back(node);
    }

    if (!consumer.out_of_tokens()) {
        std::cout << "Only declarations allowed in top level of script.\n";
        std::exit(EXIT_FAILURE);
    }

    return ast;
}

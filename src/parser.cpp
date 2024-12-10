#include "parser.hpp"

Parser::Parser() {

}

Parser::~Parser() {
    
}

ASTNode *Parser::GenerateAST(std::vector<Token>& tokens) {
    ASTNode *root = new ASTNode(ASTNodeType::ROOT);
    ASTNode **last_scope_handle = &root->data.root.next;

    ASTNode *node = nullptr;
    ASTNode *idfier = nullptr;

    for (size_t i = 0; i < tokens.size(); ++i) {
        switch (tokens[i].type) {
        case TokenType::FUNCTION:
            node = new ASTNode(ASTNodeType::FUNC_DEF);
            
            idfier = new ASTNode(ASTNodeType::IDENTIFIER);
            idfier->data.idfier.name = tokens[++i].value;

            ++i;
            
            ASTNode *arg_idfier;
            while (tokens[i].type == TokenType::IDENTIFIER) {
                arg_idfier = new ASTNode(ASTNodeType::IDENTIFIER);
                arg_idfier->data.idfier.name = tokens[i].value;

                node->data.func_def.args.push_back(arg_idfier);

                ++i;
            }
            
            node->data.func_def.name = idfier;

            node->data.func_def.body = new ASTNode(ASTNodeType::STMT_SEQ);

            *last_scope_handle = node->data.func_def.body;
            last_scope_handle = &node->data.func_def.body;
            break;
        default:
            break;
        }
    }

    return root;
}

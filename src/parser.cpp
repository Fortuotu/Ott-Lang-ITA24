#include "parser.hpp"

#include "iostream"

AST* Parser::GenerateAST(TokenStream& tokens) {
    Token tok;

    AST* ast = new AST();

    while (true) {
        tok = tokens.CheckToken();
        if (tok.type == TokenType::TOKENS_END) {
            return ast;
        }

        ast->stmts.push_back(ParseStmt(tokens));
    }
}

Expr* Parser::ParseExpr(TokenStream& tokens) {
    return ParseEquality(tokens);
}

Expr* Parser::ParseEquality(TokenStream& tokens) {
    Token tok;

    Expr* root = ParseCondition(tokens);

    tok = tokens.CheckToken();
    if (tok.type == TokenType::EQUAL || tok.type == TokenType::NOT_EQUAL) {
        Token operator_ = tokens.ConsumeToken();
        Expr* cond = ParseCondition(tokens);

        root = new BinaryExpr(operator_.type, root, cond);
    }

    return root;
}

Expr* Parser::ParseCondition(TokenStream& tokens) {
    Token tok;

    Expr* root = ParseTerm(tokens);

    tok = tokens.CheckToken();
    if (tok.type == TokenType::GREATER || tok.type == TokenType::LESS ||
        tok.type == TokenType::GREATER_OR_EQUAL || tok.type == TokenType::LESS_OR_EQUAL) {
        
        Token operator_ = tokens.ConsumeToken();
        Expr* cond = ParseCondition(tokens);

        root = new BinaryExpr(operator_.type, root, cond);
    }

    return root;
}

Expr* Parser::ParseTerm(TokenStream& tokens) {
    Token tok;

    Expr* root = ParseFactor(tokens);

    tok = tokens.CheckToken();
    if (tok.type == TokenType::ADD || tok.type == TokenType::SUBTRACT) {
        Token operator_ = tokens.ConsumeToken();
        Expr* term = ParseTerm(tokens);

        root = new BinaryExpr(operator_.type, root, term);
    }

    return root;
}

Expr* Parser::ParseFactor(TokenStream& tokens) {
    Token tok;

    Expr* root = ParseUnary(tokens);

    tok = tokens.CheckToken();
    if (tok.type == TokenType::MULTIPLY || tok.type == TokenType::DIVIDE) {
        Token operator_ = tokens.ConsumeToken();
        Expr* factor = ParseFactor(tokens);

        root = new BinaryExpr(operator_.type, root, factor);
    }

    return root;
}

Expr* Parser::ParseUnary(TokenStream& tokens) {
    Token tok;

    Expr* root = nullptr;

    tok = tokens.CheckToken();
    if (tok.type == TokenType::NOT || tok.type == TokenType::SUBTRACT) {
        root = new UnaryExpr(tok.type, ParseUnary(tokens));

        return root;
    }

    root = ParseGrouping(tokens);

    return root;
}

Expr* Parser::ParseGrouping(TokenStream& tokens) {
    Token tok;

    Expr* root = nullptr;

    tok = tokens.ConsumeToken();

    if (tok.type == TokenType::OPEN_PARENTHESES) {
        root = new GroupingExpr(ParseExpr(tokens));

        tok = tokens.ConsumeToken();
        if (tok.type != TokenType::CLOSE_PARENTHESES) {
            // error
            std::cout << "Expected closing parentheses\n";
            exit(1);
        }
        return root;
    }

    if (tok.type == TokenType::INT_LITERAL) {
        root = new LiteralExpr(tok.type, tok.value);
    } else if (tok.type == TokenType::IDENTIFIER) {
        root = new IdfExpr(tok.value);
    }

    return root;
}

Stmt* Parser::ParseStmt(TokenStream& tokens) {
    Token tok;

    tok = tokens.CheckToken();

    switch (tok.type) {
    case TokenType::PRINT:
        return ParsePrint(tokens);
    case TokenType::VAR:
        return ParseVarDecl(tokens);
    case TokenType::IDENTIFIER:
        return ParseAssign(tokens);
    case TokenType::THEN:
        return ParseBlock(tokens);
    case TokenType::IF:
        return ParseIf(tokens);
    case TokenType::FUNCTION:
        return ParseFuncDecl(tokens);
    default:
        break;
    }

    return nullptr;
}

Stmt* Parser::ParsePrint(TokenStream& tokens) {
    Token tok;

    tok = tokens.ConsumeToken(); // Consume 'PRINT' token
    tok = tokens.ConsumeToken(); // Consume '(' token

    Stmt* root = new PrintStmt(ParseExpr(tokens));

    tok = tokens.ConsumeToken(); // Consume ')' token

    return root;
}

static VarDecl* ParseVar(TokenStream& tokens) {
    Token tok;

    VarDecl* var = new VarDecl();

    tok = tokens.ConsumeToken(); // Consume 'VAR' token

    tok = tokens.ConsumeToken(); // Consume IDENTIFIER
    var->identifier = tok.value;

    return var;
}

Stmt* Parser::ParseVarDecl(TokenStream& tokens) {
    Token tok;

    VarDecl* var_decl = ParseVar(tokens);

    tok = tokens.ConsumeToken(); // Consume '=' token

    var_decl->initializer = ParseExpr(tokens); // Consume expression

    return var_decl;
}

Stmt* Parser::ParseAssign(TokenStream& tokens) {
    Token tok;

    Stmt* root = nullptr;

    std::string l;
    Expr* r = nullptr;

    tok = tokens.ConsumeToken(); // IDENTIFIER
    l = tok.value;

    tok = tokens.ConsumeToken(); // =

    r = ParseExpr(tokens);

    root = new AssignStmt(l, r);

    return root;
}

Stmt* Parser::ParseIf(TokenStream& tokens) {
    Token tok;
    
    Stmt* root = nullptr;

    Expr* cond = nullptr;
    Stmt* stmt = nullptr;

    tok = tokens.ConsumeToken(); // 'IF'
    tok = tokens.ConsumeToken(); // '('

    cond = ParseExpr(tokens);

    tok = tokens.ConsumeToken(); // ')'

    stmt = ParseStmt(tokens);

    root = new IfStmt(cond, stmt);

    return root;
}

Stmt* Parser::ParseBlock(TokenStream& tokens) {
    Token tok;

    Block* blck = new Block();

    tok = tokens.ConsumeToken(); // 'THEN'

    while (true) {
        tok = tokens.CheckToken();
        if (tok.type == TokenType::END) {
            break;
        }
        
        blck->stmts.push_back(ParseStmt(tokens));
    }

    tok = tokens.ConsumeToken(); // 'END'

    return blck;
}

Stmt* Parser::ParseFuncDecl(TokenStream& tokens) {
    Token tok;

    FuncDecl* fn = new FuncDecl();

    tok = tokens.ConsumeToken(); // 'FUNCTION'

    tok = tokens.ConsumeToken(); // IDENTIFIER

    fn->name = tok.value;

    tok = tokens.ConsumeToken(); // '('

    while (true) {
        tok = tokens.CheckToken();

        if (tok.type == TokenType::VAR) {
            fn->args.push_back(ParseVar(tokens));

            tok = tokens.CheckToken();

            if (tok.type == TokenType::COMMA) {
                tok = tokens.ConsumeToken(); // ','
                continue;
            } else if (tok.type == TokenType::CLOSE_PARENTHESES) {
                break;
            }
        } else if (tok.type == TokenType::CLOSE_PARENTHESES) {
            break;
        } else break;
    }

    tok = tokens.ConsumeToken(); // ')'

    tok = tokens.CheckToken();
    if (tok.type != TokenType::THEN) {
        printf("Expected block scope\n");
        exit(1);
    }
    fn->body = ParseBlock(tokens);

    return fn;
}

#include "ast.hpp"

#include <iostream> 

// See fail on koeravesi, ara seda vaata :)

void token_type_to_str(TokenType tt, std::string& s) {
    s.clear();
    switch (tt)
    {
    case TokenType::ADD:
        s = '+';
        break;
    case TokenType::SUBTRACT:
        s = '-';
        break;
    case TokenType::MULTIPLY:
        s = '*';
        break;
    case TokenType::DIVIDE:
        s = '/';
        break;
    case TokenType::GREATER:
        s = '>';
        break;
    case TokenType::LESS:
        s = '<';
        break;
    case TokenType::GREATER_OR_EQUAL:
        s = ">=";
        break;
    case TokenType::LESS_OR_EQUAL:
        s = "<=";
        break;
    case TokenType::NOT:
        s = '!';
        break;
    default:
        break;
    }
}

void ExprPrinter::space() {
    buf.push_back(' ');
}

void ExprPrinter::visitBinaryExpr(BinaryExpr& expr) {
    buf.push_back('(');
    
    expr.left->accept(*this);
    space();

    token_type_to_str(expr.op, temp);
    buf.append(temp);

    space();
    expr.right->accept(*this);

    buf.push_back(')');
}

void ExprPrinter::visitLiteralExpr(LiteralExpr& expr) {
    buf.push_back('(');
    buf.append(expr.val);
    buf.push_back(')');
}

void ExprPrinter::visitUnaryExpr(UnaryExpr& expr) {
    buf.push_back('(');

    token_type_to_str(expr.op, temp);
    buf.append(temp);

    expr.operand->accept(*this);

    buf.push_back(')');
}

void ExprPrinter::visitGroupingExpr(GroupingExpr& expr) {
    buf.push_back('(');

    buf.append("group ");

    expr.expr->accept(*this);

    buf.push_back(')');
}

void ExprPrinter::print(Expr* expr) {
    expr->accept(*this);

    std::cout << buf << std::endl;
}

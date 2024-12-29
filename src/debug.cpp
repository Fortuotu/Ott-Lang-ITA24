#include "debug.hpp"

void print_tokens(TokenStream& tokens) {
    int i = 0;
    for (Token& t : tokens.InternalVector()) {
        if (i == tokens.selector_)
            printf("%s <- NEXT SELECTED\n", t.value.c_str());
        else
            printf("%s\n", t.value.c_str());
        ++i;
    }
}

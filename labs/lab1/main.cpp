#include <memory>
#include "dialogue.hpp"
#include "service.hpp"
#include "lex_version.hpp"
#include "lexer_context.h"

int main() {
    auto rel = std::make_unique<lex_version>();
    auto serv = std::make_unique<service>(*rel);
    auto dia = std::make_unique<dialogue>(*serv);
    dia->main_dialogue();
    return 0;
}

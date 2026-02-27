
#include <memory>


#include "dialogue.hpp"


#include "service.hpp"
#include "src/impls/smc_version/lexer_context.h"

int main() {
    auto rel = std::make_unique<lexer_context>();
    auto serv = std::make_unique<service>(*rel);
    auto dia = std::make_unique<dialogue>(*serv);
    dia->main_dialogue();
    return 0;
}

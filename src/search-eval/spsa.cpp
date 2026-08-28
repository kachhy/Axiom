#include "spsa.h"
#include "search-eval/search.h"
#include "uci/uci.h"

#ifdef SPSA_TUNE

// Storage for the mutable terms.
#define TUNABLE_DEF_INT(name, def, min, max, cend) int name = def;
#define TUNABLE_DEF_REAL(name, def, min, max, cend, scale) TunableReal name{ def, scale };

SEARCH_TUNABLES(TUNABLE_DEF_INT, TUNABLE_DEF_REAL)

#undef TUNABLE_DEF_INT
#undef TUNABLE_DEF_REAL

// The LMR table is derived from LMR_VALUE and LMR_SCALAR, so every setter
// rebuilds it. It's cheap enough since it's done between each game.
#define TUNABLE_REG_INT(name, def, min, max, cend) \
    setOption(#name, SpinOption{ min, max, def, [](int v) { name = v; initLMR(); } });
#define TUNABLE_REG_REAL(name, def, min, max, cend, scale) \
    setOption(#name, SpinOption{ min, max, def, [](int v) { name.raw = v; initLMR(); } });

void registerTunables() { SEARCH_TUNABLES(TUNABLE_REG_INT, TUNABLE_REG_REAL) }

#undef TUNABLE_REG_INT
#undef TUNABLE_REG_REAL

#else

void registerTunables() { }

#endif // SPSA_TUNE

// OpenBench input format: name, int, default, min, max, c_end, r_end
#define TUNABLE_SPSA_INT(name, def, min, max, cend) \
    std::cout << #name << ", int, " << def << ", " << min << ", " << max << ", " << cend << ", 0.002\n";
#define TUNABLE_SPSA_REAL(name, def, min, max, cend, scale) TUNABLE_SPSA_INT(name, def, min, max, cend)

void printSPSAInput() { SEARCH_TUNABLES(TUNABLE_SPSA_INT, TUNABLE_SPSA_REAL) }

#undef TUNABLE_SPSA_INT
#undef TUNABLE_SPSA_REAL

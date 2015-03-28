#include "computerGazEnum.h"
#include "langEnum.h"

class ConfigComputer {
	gazType computerGaz=gazType::Air;
	lang default_lang=lang::eng;
	int units;
public:
	void set_values(char, int);
};

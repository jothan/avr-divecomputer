#include "computerGazEnum.h"
#include "langEnum.h"

class ConfigComputer {
	gazType computerGaz=Air;
	lang default_lang=eng;
	int units;
public:
	void set_values(char, int);
};

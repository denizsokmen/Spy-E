#ifndef KEYMAPPER_H_INC
#define KEYMAPPER_H_INC

#include "SDL.h"
#include <string>

class KeyMapper {

public:
	void mapKey(std::string key, Uint32 eventType);
	KeyMapper();
	~KeyMapper();
};

#endif

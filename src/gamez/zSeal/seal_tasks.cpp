#include "seal.h"

void* CTAction::Parse(_zrdr* reader)
{
	// Look inside the "action" tag to find a string value
	/*
	* action 
	(
		state (YOUR_STATE_HERE)
		auto_return (true)
	)
	*/
	const char* action = zrdr_findstring(reader, "action");
	unsigned int state = zrdr_finduint(reader, "state", &state, 1);
	bool auto_return = zrdr_findbool(reader, "auto_return", &auto_return);

	if (action != NULL)
	{
		void* block = calloc(16, 1);
	}
}
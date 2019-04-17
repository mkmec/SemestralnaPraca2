#pragma once

template <typename T, typename O>
class Kriterium
{
public:
	virtual T ohodnot(O& object) = 0;
	
};


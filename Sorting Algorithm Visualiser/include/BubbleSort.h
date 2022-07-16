#pragma once

#include "SortInterface.h"

class BubbleSort : public SortInterface
{
public:
	BubbleSort();
	~BubbleSort();

	virtual void Update();
	virtual void Render();
};
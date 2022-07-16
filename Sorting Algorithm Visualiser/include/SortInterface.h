#pragma once

class SortInterface
{
public:
	SortInterface() = default;
	~SortInterface() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;
};
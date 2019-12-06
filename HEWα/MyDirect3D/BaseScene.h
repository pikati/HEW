#pragma once
#include "main.h"

class BaseScene
{
public:
	virtual ~BaseScene() {};
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;
};


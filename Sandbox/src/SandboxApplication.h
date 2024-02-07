#pragma once

#include <Fjord.h>

class Sandbox : public Fjord::Application
{
public:
	Sandbox();
	~Sandbox();

protected:
	void UpdateInternal() override;
};
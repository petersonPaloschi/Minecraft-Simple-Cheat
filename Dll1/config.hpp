/*
#pragma once

// used: iostream
#include <iostream>

// used: ifstream
#include <fstream>

//jsoncpp
#include "../dependencies/json/json.hpp"
#include "../dependencies/json/json-forwards.hpp"

#define CONFIG_PATH xorstr_("c:\\config.json")

class c_config
{
public:
	c_config();
	void load();
	void save();

	struct
	{

		bool recraft = false;

	} settings;

private:

};
extern c_config config;

*/
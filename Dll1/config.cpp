/*
#include "config.hpp"

namespace fs = std::filesystem;

c_config::c_config()
{
	// @TODO: get a folder to save configs
}

void c_config::save()
{
	std::ofstream out(CONFIG_PATH);

	if (!out.is_open())
	{
		std::cout << xorstr_("cant open file") << std::endl;
		return;
	}

	Json::Value save;

	save[xorstr_("misc")][xorstr_("bhop")] = settings.recraft;

	out << save;

	out.close();
}

void c_config::load()
{
	std::ifstream in(CONFIG_PATH);

	if (!in.good())
	{
		std::cout << xorstr_("config doesnt exists, saving default") << std::endl;
		save();
	}

	if (!in.is_open())
	{
		std::cout << xorstr_("cant open file") << std::endl;
		return;
	}

	Json::Value load;

	in >> load;

	settings.bhop = load[xorstr_("misc")][xorstr_("bhop")].asBool();
	settings.triggerbot = load[xorstr_("triggerbot")][xorstr_("active")].asBool();
	settings.triggerbot_key = load[xorstr_("triggerbot")][xorstr_("key")].asInt();

	in.close();
}

*/
#include <iostream>
#include <jsoncpp/json/json.h>
#include <fstream>
#include "builder.h"

char* get_param_value(int argc, char* argv[], std::string param_name, std::string param_compact_name)
{
	for(int i = 1; i < argc; i = i + 2)
	{
		if(argv[i] == param_name || argv[i] == param_compact_name) return argv[i + 1];
	}

	return new char;
}

Json::Value get_template_content(char* template_path)
{
	std::ifstream template_file(template_path, std::ifstream::binary);
	Json::Value template_content;

	template_file >> template_content;

	return template_content;
}

int main(int argc, char* argv[])
{
	if(!argc >= 1) 
	{
		throw printf("Invalid argument!");
		return 0;
	};

	char* template_path = get_param_value(argc, argv, "--template-path", "-tp");
	
	if(strlen(template_path) == 0)
	{
		throw printf("Invalid argument!");
		return 0;
	}

	Json::Value template_content = get_template_content(template_path);

	builder::build(template_content);

	return 0;
}

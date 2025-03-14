#include "builder.h"
#include <jsoncpp/json/json.h>
#include <fstream>

void builder::read_file_content(Json::Value file_content_row)
{
	for (const auto& item : file_content_row)
	{
		//File_Content file_content = new File_Content(item.value()["id"], item.value()["path"]);
		std::cout << item;
	}	
}

void builder::build_structure()
{
	
}

void builder::build(Json::Value template_content)
{
	builder::File_Content file_content = builder::read_file_content(template_content["file-content"]);
}

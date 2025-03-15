#include "builder.h"
#include <jsoncpp/json/json.h>
#include <fstream>
#include <iostream>
#include <filesystem>

void read_file_content(Json::Value file_content_row)
{
	for (const auto& item : file_content_row)
	{
		File_Content* file_content = new File_Content(item["id"].asString(), item["path"].asString());
		std::cout << "file content loaded successful: " << file_content->loaded_successful << std::endl;
	}	
}

void create_folder(std::string* path)
{
	std::cout << "creating folder in: " << *path << std::endl;
	std::filesystem::create_directories(*path);
}

void create_file(std::string path, std::string content)
{
	std::cout << "creating file in: " << path << std::endl;
	std::ofstream outfile(path);
	outfile << content;
	outfile.close();
}

void create_folder_content(std::string* path, Json::Value current_object, Json::Value current_object_key)
{
	// file
	if (current_object.isString())
	{
		std::string temp_path_file = *path + "/" + current_object_key.asString();
		create_file(temp_path_file, current_object.asString());
	}
	// folder
	else if (current_object.isObject())
	{
		*path = *path + "/" + current_object_key.asString();
		create_folder(path);
		build_structure(path, current_object);
	}
}

void build_structure(std::string* structure_path, Json::Value parent_object)
{
	std::string* new_path = structure_path;

	for(const auto& object_child : parent_object.getMemberNames())
	{
		create_folder_content(new_path, parent_object[object_child], object_child);
	}

	//free(new_path);
}

void build(Json::Value template_content)
{
	std::string root_folder = std::string(".");
	read_file_content(template_content["file-content"]);
	build_structure(&root_folder, template_content["structure"]);
}

#include "builder.h"
#include <jsoncpp/json/json.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

std::vector<File_Content *> read_file_content(Json::Value file_content_row)
{
	std::vector<File_Content *> all_file_content;
	
	for (const auto& item : file_content_row)
	{
		File_Content* file_content = new File_Content(item["id"].asString(), item["path"].asString(), item["tags"]);

		all_file_content.push_back(file_content);
		std::cout << "file content loaded successful: " << file_content->loaded_successful << std::endl;
	}

	return all_file_content;
}

void create_folder(std::string path)
{
	std::cout << "creating folder in: " << path << std::endl;
	std::filesystem::create_directories(path);
}

std::string check_file_content_id(std::string id, std::vector<File_Content *> all_file_content)
{
	for (File_Content* file_content : all_file_content)
	{
		if(file_content->check_id(id)) return file_content->content;	
	}

	return id;
}

void create_file(std::string path, std::string content_id, std::vector<File_Content *> all_file_content)
{
	std::cout << "creating file in: " << path << std::endl;
	std::ofstream outfile(path);
	outfile << check_file_content_id(content_id, all_file_content);
	outfile.close();
}

void create_folder_content(std::string path, Json::Value current_object, Json::Value current_object_key, std::vector<File_Content *> all_file_content)
{
	std::string temp_path_file = path + "/" + current_object_key.asString();

	// file
	if (current_object.isString())
	{
		create_file(temp_path_file, current_object.asString(), all_file_content);
	}
	// folder
	else if (current_object.isObject())
	{
		create_folder(temp_path_file);
		build_structure(temp_path_file, current_object, all_file_content);
	}
}

void build_structure(std::string structure_path, Json::Value parent_object, std::vector<File_Content *> all_file_content)
{
	std::string new_path = structure_path;

	for(const auto& object_child : parent_object.getMemberNames())
	{
		create_folder_content(new_path, parent_object[object_child], object_child, all_file_content);
	}

	//free(new_path);
}

void build(Json::Value template_content)
{
	std::string root_folder = std::string(".");
	std::vector<File_Content *> all_file_content;

	all_file_content = read_file_content(template_content["file-content"]);
	build_structure(root_folder, template_content["structure"], all_file_content);
}

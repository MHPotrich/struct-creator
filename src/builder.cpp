#include "builder.h"
#include <jsoncpp/json/json.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include "builder.h"
#include "file_content.h"
#include "folder_tag.h"

std::vector<FileContent*> read_file_content(Json::Value file_content_row)
{
	std::vector<FileContent*> all_file_content;
	
	for(const auto& item : file_content_row)
	{
		FileContent* file_content = new FileContent(item["id"].asString(), item["path"].asString(), item["tags"]);

		all_file_content.push_back(file_content);
		std::cout << "file content loaded successful: " << file_content->loaded_successful << "\n";
	}

	return all_file_content;
}

std::vector<FolderTag*> read_folder_tags(Json::Value folder_tags)
{
	std::vector<FolderTag*> all_folder_tags;

	for(const auto& tag: folder_tags)
	{
		FolderTag* folder_tag = new FolderTag(tag["id"].asString(), tag["value"].asString());

		all_folder_tags.push_back(folder_tag);
		std::cout << "folder tag " << folder_tag->get_id() << " loaded successful" << "\n";
	}

	return all_folder_tags;
}

void create_folder(std::string path)
{
	std::cout << "creating folder in: " << path << std::endl;
	std::filesystem::create_directories(path);
}

std::string check_file_content_id(std::string id, std::vector<FileContent*> all_file_content)
{
	for (FileContent* file_content : all_file_content)
	{
		if(file_content->check_id(id)) return file_content->content;	
	}

	return id;
}

void create_file(std::string path, std::string content_id, std::vector<FileContent*> all_file_content)
{
	std::cout << "creating file in: " << path << std::endl;
	std::ofstream outfile(path);
	outfile << check_file_content_id(content_id, all_file_content);
	outfile.close();
}

void create_folder_content(std::string path, Json::Value current_object, Json::Value current_object_key, std::vector<FileContent*> all_file_content, std::vector<FolderTag*> folder_tags)
{
	// file
	if (current_object.isString())
	{
		std::string temp_path_file = path + "/" + current_object_key.asString();
		create_file(temp_path_file, current_object.asString(), all_file_content);
	}
	// folder
	else if (current_object.isObject())
	{
		std::string temp_path_file = path + "/" + find_folder_tag(current_object_key.asString(), folder_tags);
		create_folder(temp_path_file);
		build_structure(temp_path_file, current_object, all_file_content, folder_tags);
	}
}

void build_structure(std::string structure_path, Json::Value parent_object, std::vector<FileContent*> all_file_content, std::vector<FolderTag*> folder_tags)
{
	std::string new_path = structure_path;

	for(const auto& object_child : parent_object.getMemberNames())
	{
		create_folder_content(new_path, parent_object[object_child], object_child, all_file_content, folder_tags);
	}
}

void build(Json::Value template_content, char* destination_path)
{
	std::string destination_path_string = std::string(destination_path);

	if(destination_path_string.empty()) destination_path_string = "."; 

	std::string root_folder = std::string(destination_path_string);
	std::vector<FileContent*> all_file_content = read_file_content(template_content["file-content"]);
	std::vector<FolderTag*> folder_tags = read_folder_tags(template_content["folder-tags"]);

	build_structure(root_folder, template_content["structure"], all_file_content, folder_tags);
}

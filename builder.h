#include <jsoncpp/json/json.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

#ifndef BUILDER_H
#define BUILDER_H

class File_Content
{
private:
	std::string id;
	std::string path;

	void update_dynamic_tags()
	{
		if (this->tags.empty()) return;

		for(int i = 0; i < this->tags.size(); i++)
		{
			std::string tag_value;
			std::string tag_target = "<<" + tags[i] + ">>";
			
			std::cout << tag_target << " tag value: ";
			std::cin >> tag_value;

			size_t tag_position = this->content.find(tag_target);

			while(tag_position != std::string::npos)
			{
				this->content.replace(tag_position, tag_target.size(), tag_value);
				tag_position = this->content.find(tag_target, tag_position + tag_value.size());
			}
		}		
	}

	bool load_content()
	{
		if(this->path.empty()) return false;

		std::cout << "loding content from: " << this->path << std::endl;

		std::string content;
		std::ifstream content_file(this->path);

		while (getline (content_file, content))
		{
			std::string string_content(content);
			std::cout << "content loading from " << this->path << " " << string_content << std::endl;
			this->content += string_content;
		}

		this->update_dynamic_tags();

		content_file.close();

		return true;
	}

public:
	bool loaded_successful = false;
	std::string content;
	std::vector<std::string> tags;

	File_Content(std::string id, std::string file_path, Json::Value tags)
	{
		this->id = id;
		this->path = file_path;

		for(const auto& tag : tags)
		{
			this->tags.push_back(tag.asString());
		}

		this->loaded_successful = load_content();
	}

	bool check_id(std::string id)
	{
		return this->id == id;
	}	
};
	
std::vector<File_Content *> read_file_content(Json::Value file_content_row);
void create_folder(std::string path);
std::string check_file_content_id(std::string id, std::vector<File_Content *> all_file_content);
void create_file(std::string path, std::string content, std::vector<File_Content *> all_file_content);
void create_folder_content(std::string path, Json::Value current_object, Json::Value current_object_key, std::vector<File_Content *> all_file_content);
void build_structure(std::string structure_path, Json::Value parent_object, std::vector<File_Content *> all_file_content);
void build(Json::Value template_content);

#endif /* BUILDER_H */

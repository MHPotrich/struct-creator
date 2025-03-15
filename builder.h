#include <jsoncpp/json/json.h>
#include <fstream>

#ifndef BUILDER_H
#define BUILDER_H

class File_Content
{
private:
	std::string id;
	std::string path;

	void update_dynamic_tags()
	{
		// todo: replace tags to values asked to the user through runtime.		
	}

	bool load_content()
	{
		if(this->path.empty()) return false;

		std::string content;
		std::ifstream content_file(this->path);

		while (getline (content_file, content))
		{
			this->content = this->content + content;
		}

		this->update_dynamic_tags();

		content_file.close();

		return true;
	}

public:
	bool loaded_successful = false;
	std::string content;

	File_Content(std::string id, std::string file_path)
	{
		this->id = id;
		this->path = file_path;
		this->loaded_successful = load_content();
	}	
};
	
void read_file_content(Json::Value file_content_row);
void create_folder(std::string* path);
void create_file(std::string path, std::string content);
void create_folder_content(std::string* path, Json::Value current_object, Json::Value current_object_key);
void build_structure(std::string* structure_path, Json::Value parent_object);
void build(Json::Value template_content);

#endif /* BUILDER_H */

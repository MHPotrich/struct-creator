#ifndef FILE_CONTENT_H
#define FILE_CONTENT_H

#include <string>
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

class FileContent
{
	private:
		std::string id;
		std::string path;

		void update_dynamic_tags()
		{
			for(const auto& tag: this->tags)
			{
				std::string tag_value = tag["value"].asString();
				std::string tag_target = "<<" + tag["id"].asString() + ">>";

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
		Json::Value tags;

		FileContent(std::string id, std::string file_path, Json::Value tags)
		{
			this->id = id;
			this->path = file_path;
			this->tags = tags;
			this->loaded_successful = load_content();
		}

		bool check_id(std::string id)
		{
			return this->id == id;
		}
};


#endif /* FILE_CONTENT_H */

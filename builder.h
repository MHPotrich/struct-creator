#include <jsoncpp/json/json.h>
#include <fstream>

#ifndef BUILDER_H
#define BUILDER_H

namespace builder 
{
	class File_Content
	{
	private:
		std::string id;
		std::string path;

		void update_dynamic_tags()
		{
			
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
	void build_structure();
	void build(Json::Value template_content);
}

#endif /* BUILDER_H */

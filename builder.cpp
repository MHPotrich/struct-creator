#include <jsoncpp/json/json.h>
#include <fstream>

class File_Content
{
	private:
		std::id;
		std::string path;

		void update_dynamic_tags()
		{
			
		}

		bool load_content()
		{
			if(!path) return false;

			std::string content;
			ifstream content_file(this->path);

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

		File_content(std::string id, std::string file_path)
		{
			this->id = id;
			this->path = file_path;
			this->loaded_successful = load_content();
		}	
}

void read_file_content(Json::Value file_content_row)
{
	for (const auto& item : file_content_row)
	{
		//File_Content file_content = new File_Content(item.value()["id"], item.value()["path"]);
	}	
}

void build_structure()
{
	
}

void build(Json::Value template_content)
{
	File_Content file_content = read_file_content(template_content["file-content"]);

}

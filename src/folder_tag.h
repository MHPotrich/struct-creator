#ifndef FOLDER_TAG_H
#define FOLDER_TAG_H

#include <string>
#include <vector>

class FolderTag
{
	private:
		std::string id;
		std::string value;

	public:
		FolderTag(std::string id, std::string value)
		{
			this->id = "<<" + id + ">>";
			this->value = value;
		}

		std::string get_id()
		{
			return this->id;
		}

		bool has_tag(std::string folder_name)
		{
			return folder_name.find(this->id, 0) != std::string::npos;
		}

		std::string find_replace_tag(std::string folder_name)
		{
			int start_tag_index = folder_name.find(this->id, 0);
			int end_tag_index = start_tag_index + this->id.length();

			return folder_name.replace(start_tag_index, end_tag_index, this->value);
		}
};

std::string find_folder_tag(std::string raw_folder_name, std::vector<FolderTag*> folder_tags);

#endif /* FOLDER_TAG_H */

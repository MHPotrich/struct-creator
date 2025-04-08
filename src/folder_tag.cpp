#include "folder_tag.h"

std::string find_folder_tag(std::string raw_folder_name, std::vector<FolderTag*> folder_tags)
{
	std::string updated_folder_name = raw_folder_name;

	for(const auto& tag: folder_tags)
	{	
		if(tag->has_tag(raw_folder_name))
		{
			updated_folder_name = tag->find_replace_tag(raw_folder_name);
			break;
		}
	}

	return updated_folder_name;
}

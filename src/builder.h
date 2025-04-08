#ifndef BUILDER_H
#define BUILDER_H

#include <jsoncpp/json/value.h>
#include <vector>
#include "file_content.h"
#include "folder_tag.h"

std::vector<FileContent*> read_file_content(Json::Value file_content_row);
std::vector<FolderTag*> read_folder_tags(Json::Value folder_tags);
void create_folder(std::string path);
std::string check_file_content_id(std::string id, std::vector<FileContent*> all_file_content);
void create_file(std::string path, std::string content_id, std::vector<FileContent*> all_file_content);
void create_folder_content(std::string path, Json::Value current_object, Json::Value current_object_key, std::vector<FileContent*> all_file_content, std::vector<FolderTag*> folder_tags);
void build_structure(std::string structure_path, Json::Value parent_object, std::vector<FileContent*> all_file_content, std::vector<FolderTag*> folder_tags);
void build(Json::Value template_content, char* destination_path);

#endif /* BUILDER_H */

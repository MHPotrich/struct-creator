# struct-creator
A tool focused on create folder and file structure in a way that it is simple and easy to replicate.

## Todo list
- [x] read a json file with the structure the tool needs to follow.
- [x] make possible to set a default content for files.
- [ ] give the option to compress the structure in a zip file.
- [x] default content must tags where will get replaced with content give by the user when build the structure.
- [ ] make possible to define a folder name with a tag

## Usage

- `--template-path` or `--tp`: to reference the template file path.

```
$ struct-creator --template-path ./template.json
```

## Compilation

```
g++ -o creator builder.cpp main.cpp -ljsoncpp
```

### Requirements

- jsoncpp: `$ apt install libjsoncpp-dev`

## Template

- `file-content`(required):
This object contains another objects that represents the content of file. These children objects must have the path to file where the content will get copied, the id to be referenced in the sctruture object and a object tags that list the reserved names that will get replaced in building process.

- `structure`(required):
Object that represents the folder structure. every object inside the structure object that has your value as a array will be considered a folder and the object with a string as your value will be considered file.

Ps: an object with string as content must be file-content id, if the file-content was not found, it will be used the object value as the file content.

tags are indentified inside file rounded by `<<` and `>>`.

template example:
```json
{
	"file-content": [
		{
			"path": "./text.txt",
			"id": "content-text-1",
			"tags": [
				"price",
				"displayName"
			]
		}
	],
	"structure": {
		"folder-root": {
			"children-folder": {
				"file-2.txt": "content-text-1",
				"file-3.txt": "content-text-1"
			},
			"file-1.txt": "content-text-1"
		}
	}
}
```
file-content example:
```html
<div>
	<h1><<displayName>></h1>
	<h3>$ <<price>></h3>
</div>
```

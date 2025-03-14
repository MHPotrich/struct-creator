# struct-creator
A tool focused on create folder and file structure in a way that it is simple and easy to replicate.

## Todo list
- [ ] read a json file with the structure the tool needs to follow.
- [ ] make possible to set a default content for files.
- [ ] give the option to compress the structure in a zip file.
- [ ] default content must tags where will get replaced with content give by the user when build the structure.

## Usage

- `--template-path` or `--tp`: to reference the template file path.

```
$ struct-creator --template-path ./template.json
```

## Compilation

```
g++ -o creator main.cpp -ljsoncpp
```

### Requirements

- jsoncpp: `$ apt install libjsoncpp-dev`


# struct-creator
A tool focused on create folder and file structure in a way that it is simple and easy to replicate.

## todo list
[] read a json file with the structure the tool needs to follow.
[] make possible to set a default content for files.
[] give the option to compress the structure in a zip file.
[] default content must tags where will get replaced with content give by the user when build the structure.

## usage
```
$ struct-creator ./template.json
```

## Compilation

```
g++ -o creator main.cpp -ljsoncpp
```

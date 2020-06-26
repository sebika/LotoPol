# Useful tips

### Create a tree from database with:
```sh
$ make createTree
```

### Update the tree:
- make sure to have a serialized tree in `output` folder
- add **new draws** to `input/update` file
- the program will update the existing `database` and remove the contents of the `update` file
```sh
$ make updateTree
```

### To simply run the program:
```sh
$ make
```

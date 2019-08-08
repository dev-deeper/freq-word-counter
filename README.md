# Simple word frequency counter
A simple word frequency counter calculates number of words in the certain file.

Displays results to stdout (by default) or writes to a file.
### Description
* A word is a set of Latin letters, a-zA-Z.
* Any other character is considered a space.
* Words must be lowercase.
* Words should be sorted by frequency and then alphabetically.

### Build project
```
make
make test
```

### Example
```
$ cat in.txt
The time has come, the Walrus said,
to talk of many things...
```
```
$ ./freq -i in.txt -o out.txt
```
```
$ cat out.txt
    2 the
    1 come
    1 has
    1 many
    1 of
    1 said
    1 talk
    1 things
    1 time
    1 to
    1 walrus
```


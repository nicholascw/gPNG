# gPNG
A tiny utility that encode GPG message into PNG format.
(It actually encodes any binary that is throw into its stdin that has no 0x00)

License [GPLv3](LICENSE)

[CHANGELOG](CHANGELOG.md)

### Dependencies
png++

### Compile

> If you are Arch Linux user, try out AUR/gpng-git.

```bash
cmake .
make
```

### Usage
See `gPNG -h` you shall see.

### Sample
```bash
gpg --armor --export 0x8c18f6b0 | gpng g2p sample.png
```
##### Output

![1](sample.png)

# gPNG
A tiny utility that encode GPG message into PNG format
(It actually encodes any binary that is throw in stdin that has no 0xff or 0x00 in the binary input)

### License
GPLv3

### Dependencies
png++

### Compile

> If you are Archlinux user, try out AUR/gpng-git.

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

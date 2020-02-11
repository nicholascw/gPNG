//
// Created by nicholas on 2020/2/11.
//

#ifndef GNUPNG_BUILDINFO_H
#define GNUPNG_BUILDINFO_H
const char* proj_name="GnuPNG";
const char* license="Copyright (C) 2020 Nicholas Wang <me@nicho1as.wang>\n"
                    "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n"
                    "This is free software: you are free to change and redistribute it.\n"
                    "There is NO WARRANTY, to the extent permitted by law.\n\n";

const char* ver="0.1";

const char* usage="Usage: GnuPNG [p2g | g2p] [file]\n"
                  "    If output file not set, will output in stdout\n"
                  "Options:\n"
                  "    g2p            gpg to png\n"
                  "    p2g            png to gpg\n"
                  "    -h, --help     Show this help information.\n\n"
                  "Example:\n"
                  "    echo \"something\" | gpg -se -r [key] --sign-with [key] --armor | GnuPNG g2p out.png\n"
                  "    gpg <(GnuPNG p2g in.png)\n\n";
                  "Notice:\n"
                  "    The current version scheme recommends the --armor option in gpg, "
                  "since the length is not stored in the image output.\n";


#endif //GNUPNG_BUILDINFO_H

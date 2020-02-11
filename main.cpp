#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <png++/image.hpp>
#include <png++/rgb_pixel.hpp>
#include "buildinfo.h"

using std::string, std::cout, std::cin, std::endl, std::cerr;

void show_help();

void g2p(char *out);

void p2g(char *in);

int main(int argc, char **argv) {
    if(argc == 3) {
        string arg1 = string(argv[1]);
        if(arg1 == "g2p") {
            if(!access(argv[2], F_OK)) cerr << "\033[1;33mWARN\033[0m File exists, will be overwritten.\n";
            g2p(argv[2]);
        } else if(arg1 == "p2g") {
            if(access(argv[2], R_OK)) {
                perror(argv[0]);
                exit(1);
            }
            p2g(argv[2]);
        }
    } else show_help();
    return 0;
}

void g2p(char *out) {
    freopen(nullptr, "rb", stdin);
    size_t buf_size = 256, count = 0;
    auto *buf = (png::byte *) calloc(sizeof(png::byte), buf_size);
    do {
        buf[count++] = getc(stdin);
        if(count > buf_size) {
            auto *tmp_buf = (png::byte *) realloc(buf, buf_size * 2);
            if(tmp_buf) buf = tmp_buf;
            else {
                cerr << "OOM!\n";
                free(buf);
                exit(1);
            }
            buf_size = buf_size * 2;
        }
    } while(buf[count - 1] != 0xff); // 0xff==EOF in unsigned char
    buf[count - 1] = 0x00;
    count += 3 - (count % 3 ? count % 3 : 3);
    png::uint_32 img_side = std::ceil(std::sqrt(count / 3));
    png::image<png::rgb_pixel> canvas(img_side * 4, img_side * 4);
    png::byte *ptr = buf;
    png::rgb_pixel pix;
    for(png::uint_32 x = 0; x < img_side; x++) {
        for(png::uint_32 y = 0; y < img_side; y++) {
            if(ptr > buf + count)
                pix = png::rgb_pixel(0,0,0);
            else
                pix = png::rgb_pixel(*ptr, *(ptr + 1), *(ptr + 2));
            for(uint8_t i = 0; i < 4; i++)
                for(uint8_t j = 0; j < 4; j++)
                    canvas.set_pixel(x * 4 + i, y * 4 + j, pix);
            ptr += 3;
        }
    }
    free(buf);
    canvas.write(out);
    if(access(out, F_OK)) cerr << "\033[1;31mERROR\033[0m Write file error.\n";
}

void p2g(char *in) {
    png::image<png::rgb_pixel> canvas(in);
    if(canvas.get_height() != canvas.get_width()) {
        cerr << "\033[1;31mERROR\033[0m Scheme requires a square PNG file.\n";
        exit(1);
    }
    if((canvas.get_height() % 4) || (canvas.get_width() % 4)) {
        cerr << "\033[1;31mERROR\033[0m Scheme requires width and height are multiples of 4.\n";
        exit(1);
    }
    png::uint_32 img_side = canvas.get_width() / 4;
    unsigned char *buf = (unsigned char *) malloc(img_side * img_side * 3);
    unsigned char *ptr = buf;
    for(png::uint_32 x = 0; x < img_side; x++) {
        for(png::uint_32 y = 0; y < img_side; y++) {
            png::rgb_pixel pix = canvas.get_pixel(x * 4, y * 4);
            for(uint8_t i = 0; i < 4; i++)
                for(uint8_t j = 0; j < 4; j++) {
                    png::rgb_pixel tmp_pix = canvas.get_pixel(x * 4 + i, y * 4 + j);
                    if(pix.green != tmp_pix.green
                       || pix.blue != tmp_pix.blue
                       || pix.red != tmp_pix.red) {
                        cerr << "\033[1;33mWARN\033[0m inconsistent pixel (" << x * 4 + i
                             << ", " << y * 4 + j << ").\n";
                    }
                }
            *ptr = pix.red;
            *(ptr + 1) = pix.green;
            *(ptr + 2) = pix.blue;
            ptr += 3;
        }
    }
    cout << buf;
    free(buf);
}

void show_help() {
    cout << proj_name << " " << ver << endl << license << usage;
}

#!/usr/bin/env python


from PIL import Image
import sys
import os



class Rgb565ImageScanner(object):
    next_idx = 0
    palette = {}  # 16bit color -> palette index
    images = {}

    def __init__(self, variable_prefix='icon_algorithm_', palette_variable='palette'):
        self.variable_prefix = variable_prefix
        self.palette_variable = palette_variable


    #define CL(_r,_g,_b) ((((_r)&0xF8)<<8)|(((_g)&0xFC)<<3)|((_b)>>3))

    def rgb888to565(self, rgb):
        # r = (rgb[0] >> 3) & 0x1F
        # g = (rgb[1] >> 2) & 0x3F
        # b = (rgb[2] >> 3) & 0x1F
        return ((rgb[0] & 0xF8)<<8) | ((rgb[1] & 0xFC)<<3) | (rgb[2] >>3)
        # return (r << 11) + (g << 5) + b

    def read_file(self, filename):
        img = Image.open(filename).convert('RGB')

        paletted_image = []

        for pixel in img.getdata():
            color = self.rgb888to565(pixel)
            if color not in self.palette:
                self.palette[color] = self.next_idx
                self.next_idx += 1
            idx = self.palette[color]
            paletted_image.append(idx)
        self.images[filename] = dict(
            data=paletted_image,
            width=img.size[0],
            height=img.size[1]
        )

    def dump_c(self, outfile):
        #header
        outfile.write("#ifndef {define}\n#define {define}\n\n#include <inttypes.h>\n\n".format(define="ICONS_H"));

        #palette
        outfile.write("const uint16_t {prefix}{var}[] = {{".format(
            prefix=self.variable_prefix,
            var=self.palette_variable
        ));

        reverse_palette = {v: k for k,v in self.palette.items()}
        for i in range(0,self.next_idx):
            if i != 0:
                outfile.write(",");
            outfile.write("0x{:04x}".format(reverse_palette[i]))

        #end of pallete
        outfile.write("};\n\n\n")




        #image data arrays
        for filename, image in self.images.items():
            name, ext = os.path.splitext(os.path.basename(filename))
            outfile.write("const uint8_t {prefix}{name}[] = {{".format(
                prefix=self.variable_prefix,
                name=name
            ))
            first = True
            for b in image['data']:
                if not first:
                    outfile.write(",");
                else:
                    first = False
                outfile.write("{}".format(b))
            outfile.write("};\n");

        # icon definitions
        outfile.write("\n\nstruct icon_t {\n  uint8_t width;\n  uint8_t height;\n  const uint8_t *icon;\n};\n\n");
        i = 0
        for filename, image in self.images.items():
            name, ext = os.path.splitext(os.path.basename(filename))
            outfile.write("#define ICON_{name} {i}\n".format(name=name, i=i))
            i += 1


        i = 0
        outfile.write("const struct icon_t ICONS[] = {\n");
        for filename, image in self.images.items():
            name, ext = os.path.splitext(os.path.basename(filename))
            if i != 0:
                outfile.write(",\n");
            outfile.write("  {{{width},{height}, {prefix}{name}}}".format(
                width=image['width'],
                height=image['height'],
                prefix=self.variable_prefix,
                name=name,
            ))
            i += 1
        outfile.write("\n};\n\n");


        #end of define
        outfile.write("\n\n#endif\n");




if __name__ == '__main__':
    scanner = Rgb565ImageScanner()
    for filename in sys.argv[1:]:
        scanner.read_file(filename)

    scanner.dump_c(sys.stdout)

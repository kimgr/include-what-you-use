#!/usr/bin/env python

##===--- generate_qt_mappings.py - creates .imp files for Qt --------------===##
#
#                     The LLVM Compiler Infrastructure
#
# This file is distributed under the University of Illinois Open Source
# License. See LICENSE.TXT for details.
#
##===----------------------------------------------------------------------===##

"""
This script generates the Qt mapping file according to given Qt include
directory

Example usage :

   $ ./generate_qt_mappings.py /usr/include/x86_64-linux-gnu/qt5 qt5_11.imp

"""

from __future__ import print_function
import argparse
import glob
import os
import re
import sys


def main(qt_include_dir, output_file):
    symbols_map = []
    includes_map = []

    headers = glob.glob(os.path.join(args.qt_include_dir, '**/*[!.h]'))
    for header in headers:
        if os.path.isdir(header):
            continue

        class_name = os.path.basename(header)
        module_name = os.path.basename(os.path.dirname(header))

        symbols_map += ['{ symbol: [ "%s", "private", ' % class_name
                        + '"<%s>", "public" ] }' % class_name]

        with open(header, 'r') as f:
            content = f.read()

        includes = re.findall(r'#include "(.*)\.h"', content)
        for include in includes:
            includes_map += [
                '{ include: [ "@[\\"<](%s/)?%s\\\\.h[\\">]", ' % (
                    module_name, include)
                + '"private", "<%s>", "public" ] }' % class_name]

    with open(args.output_file, 'w') as f:
        print("# Do not edit! This file was generated by the script %s." %
              os.path.basename(__file__), file=f)
        print("[", file=f)
        print("  %s" % ",\n  ".join(symbols_map + includes_map), file=f)
        print("]", file=f)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("qt_include_dir", help="Qt include directoy")
    parser.add_argument("output_file", help="Generated output mapping file")
    args = parser.parse_args()
    sys.exit(main(args.qt_include_dir, args.output_file))

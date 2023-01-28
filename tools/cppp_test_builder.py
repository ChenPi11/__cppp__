#!/bin/env python3
'''
 * @package cppp_test_builder
 * @file tools/cppp_test_builder.py
 * @copyright Copyright (C) 2023
 * @date 2023-1-27
 * @language Python
 * @brief C++ Plus Builder console base

C++ Plus Test Program builder

LICENCE MIT Licence
'''
import platform
import sys


def test_build():
    try:
        if(platform.uname()[0]=="Windows"):
            import cppp_test_builder_msbuild as tb
            tb.test_builder_main()
        else:
            import cppp_test_builder_gcc as tb
            tb.test_builder_main()
    except KeyboardInterrupt:
        sys.exit(3)
    except SystemExit:
        raise

if(__name__=="__main__"):
    test_build()

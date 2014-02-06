# Copyright (c) 2011 The Chromium Embedded Framework Authors.
# Portions copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

from gclient_util import *
import os, sys

# The CEF root directory is the parent directory of _this_ script.
cef_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir))

print "\nChecking CEF and Chromium revisions..."
gyper = [ 'python', 'tools/check_revision.py' ]
RunAction(cef_dir, gyper)

print "\nGenerating CEF version header file..."
gyper = [ 'python', 'tools/make_version_header.py',
          '--header', 'include/cef_version.h',
          '--cef_version', 'VERSION',
          '--chrome_version', '../chrome/VERSION',
          '--cpp_header_dir', 'include' ]
RunAction(cef_dir, gyper)

print "\nPatching build configuration and source files for CEF..."
patcher = [ 'python', 'tools/patcher.py', 
            '--patch-config', 'patch/patch.cfg' ];
RunAction(cef_dir, patcher)

print "\nGenerating CEF project files..."
os.environ['CEF_DIRECTORY'] = os.path.basename(cef_dir);
gyper = [ 'python', 'tools/gyp_cef', 'cef.gyp', '-I', 'cef.gypi' ]
# for windows we have to build all deps
# gyper = [ 'python', 'tools/gyp_cef', 'cef.gyp', '-I', 'cef.gypi', '-Dwerror=']

# Desura-specific arguments, added using 'extend' to ease future merging.
gyper.extend((
    '-Dwerror=',
    '-Dproprietary_codecs=1',
##  '-Dffmpeg_branding=@CEF_FFMPEG_BRANDING@',
##  see desura-app/cmake/modules/CheckOptions.cmake
##  '-Dffmpeg_branding=Chrome',         # if H264_SUPPORT
    '-Dffmpeg_branding=Chromium',       # if not H264_SUPPORT
    ))

# Additional Desura-specific arguments are platform-dependent.
if sys.platform.startswith("win"):
    gyper.extend((
        '-Dchromium_win_pch=1',
        '-Dmsvs_multi_core_compile=1',
        ))
else:
    gyper.extend((
        '-Duse_cups=0',
        '-Duse_gconf=0',
        '-Duse_gnome_keyring=0',
        '-Duse_kerberos=0',
        '-Duse_system_bzip2=1',
        '-Duse_system_flac=1',
        '-Duse_system_icu=0',
        '-Duse_system_libevent=1',
        '-Duse_system_libjpeg=1',
        '-Duse_system_libpng=1',
        '-Duse_system_libwebp=0',
        '-Duse_system_libxml=1',
        '-Duse_system_speex=1',
        '-Duse_system_v8=0',
        '-Duse_system_xdg_utils=1',
        '-Duse_system_yasm=1',
        '-Duse_system_zlib=1',
        ))

RunAction(cef_dir, gyper)

desura-cef3
===========

The two branches of this repository support the Vendor Branch strategy:
https://wiki.lindenlab.com/wiki/Mercurial_Vendor_Branches

vendor_svncef3 is the unmodified Google source.
master contains Linden modifications.

However, this is not a standalone repository. It must be checked out under the
Google Chromium source tree as src/cef. Please see
https://wiki.lindenlab.com/wiki/Desura/CEF for build instructions.

NOTE: One of the CEF build scripts requires a commit message line in a
specific format for each update from Google source. Specifically, every time
you merge a new vendor_svncef3 update to the master branch, the commit message
must include a line of the form:

git-svn-id: @1503

where '1503' represents the Subversion revision number of the updated Google
code.
=======

Build Windows
-----------

 * Get depot tools from https://src.chromium.org/svn/trunk/tools/depot_tools.zip and add it to your path
 * In a new folder run "fetch --nohooks chromium --nosvn=True"
 * cd to the source dir
 * run "gclient sync --revision src@[revision] --jobs 8 --force" (replace revision with the value from CHROMIUM_BUILD_COMPATIBILITY.txt)
 * Clone this repo into src/cef
 * run "set GYP_GENERATORS='ninja'"
 * cd src/cef
 * run "cef_create_projects.bat"
 * cd up a dir
 * run "ninja -C out/Debug cef_desura"

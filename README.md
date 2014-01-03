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

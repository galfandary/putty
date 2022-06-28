PuTTY Config Patch
==================

### Supports Unix style configuration on Windows (.putty) in CSV form.
The first line ("Def" below) is the default settings.<br>
This is a sample use (transposed for display):

<pre>
Name,Def,Main
RemoteCommand,exec /bin/bash,exec /bin/bash
TermWidth,120,120
TermHeight,40,40
ScrollbackLines,4000,4000
PingInterval,5,5
HostName,!,host.org
UserName,jdoe,jdoe
LocalUserName,jdoe,jdoe
Protocol,ssh,ssh
PortNumber,22,22
PublicKeyFile,C:\Users\jdoe\OneDrive\id.ppk,==
</pre>

### Build on Fedora 34:

* dnf install cmake mingw64-filesystem mingw64-gcc
* cp /path/storage.c windows/
* git am /path/patch.dif
* mingw64-cmake .
* cmake --build .

This works on my Win10 and Win11 Home editions
and on my work Win10 Enterprise edition.<br>
Tested with git hash f579b3c0.

P.S. (my illustrious contribution to the project thus far):<br>
https://git.tartarus.org/?p=simon/putty.git;a=commitdiff;h=24a4340

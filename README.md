PuTTY Config Patch
==================

### Supports Unix style configuration on Windows (.putty) in CSV form:

<pre>
Name,RemoteCommand,TermWidth,TermHeight,ScrollbackLines,PingInterval,HostName,UserName,LocalUserName,Protocol,PortNumber,PublicKeyFile,
Def,exec /bin/bash,120,40,4000,5,!,jdoe,jdoe,ssh,22,C:\Users\jdoe\OneDrive\id.ppk,
Main,exec /bin/bash,120,40,4000,5,host.org,jdoe,jdoe,ssh,22,C:\Users\jdoe\OneDrive\id.ppk,
</pre>

### Build on Fedora 34:

* dnf install mingw64-filesystem mingw64-gcc
* cp /path/storage.c windows/
* git am /path/storage.dif
* mingw64-cmake .
* cmake --build .

This works on my Win10 and Win11 Home editions but is currently
crashing on my work Win10 Enterprise edition - investigating.

P.S. (my illustrious contribution to the project thus far):
https://git.tartarus.org/?p=simon/putty.git;a=commitdiff;h=24a4340

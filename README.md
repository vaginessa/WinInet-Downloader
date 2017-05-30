WinInet-Downloader
========

Basic downloader with progress bar using WinInet supporting SSL and SHA-256 verification.

Usage:  
Downloader.exe [options] &lt;url&gt; &lt;filename&gt;

Available options:  
/bubble - enables request info bubble  
/ignore - allows user to bypass security  
/ignore-expired  
/ignore-wrong-host  
/ignore-revoked  
/ignore-untrusted-root  
/ignore-wrong-usage  
/passive - no user interaction  
/passive:&lt;exit code&gt; - conditionally passive  
/proxy-name:&lt;list of proxy servers&gt;  
/proxy-bypass:&lt;list of hosts&gt;  
/secure - enforces https on http URLs  
/sha256:&lt;hash&gt; - enables sha256 verification  
/timeout:&lt;milliseconds&gt;  
/topmost - keeps window on top of z-order  
/useragent:&lt;name&gt;

Compiles to an ~22KB EXE with VS without fiddling (CRT not used).

![Screenshot](https://github.com/datadiode/WinInet-Downloader/blob/master/screenshot.png)

# TCP Splitting Proxy (TCPSProxy) README

TCPSProxy splits a TCP connection between a set of servers. TCPSProxy
is currently in early development and should not be used inany production 
envrionment.

## Background

TCPSProxy was created to easily write to mulitple redis masters as if they are
one, though it could be used for other purposes.

## Acknowledgements

Thanks to [Robert Ingalls](http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html) for providing biolerplate code for working with IP sockets.

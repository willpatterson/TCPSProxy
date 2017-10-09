# TCP Splitting Proxy (TCPSProxy) README

TCPSProxy is a reverse proxy that splits a TCP connection between a set of
servers. TCPSProxy is currently in early development and should not be used in
any production envrionment.

## Background

TCPSProxy was created to easily write to mulitple redis masters as if they are
one, though it could be used for other purpouses.

## Major TODOs:

* memory safe buffers
* implement connection queue
* async reads/writes
* config parsing
* output diff with conflict resolution policies

#!/usr/bin/env python

#c'e ancora da implementare la comunicazione bidirezionale.
#riferirsi a https://docs.python.org/2/library/socket.html

import socket
import sys

port = 8267
timeout = None

if len(sys.argv) == 2:
    timeout = float(sys.argv[1])

#create an INET, STREAMing socket
servsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#make socket immediately reusable
servsock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

#bind the socket to a public host,
# and a well-known port
servsock.bind((socket.gethostname(), port))
#become a server socket
servsock.listen(5)

while True:
    print 'Waiting for clients on port', port

    try:
        #accept connections from outside
        (clisock, address) = servsock.accept()
        clisock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        clisock.settimeout(timeout)
        print '--- Receiving from', address[0],'---'
        while True:
            try:
                data = clisock.recv(1)
                if not data: break
                sys.stdout.write(data)
            except socket.timeout:
                print "--- Timed Out:", timeout, "seconds ---"
                break
            except KeyboardInterrupt:
                print '--- Server closed connection ---'
                break
        clisock.close()
    except KeyboardInterrupt:
        sys.exit()

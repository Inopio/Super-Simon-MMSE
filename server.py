import socket
from _thread import *

nbplayer = 0
running = True

def threadClient(ip, port, socket):

    print("Creating new thread for host %s %s" % (ip, port, ))


    while (True):
        try:
            resp = socket.recv(2048).decode()
            if not resp :
                print("null")
                break
            print("Connection from : %s %s" % (ip, port, ))

            if(nbplayer >= 2) :
                running = True
                data = "good"
                socket.send(str.encode(data))

        except:
            break
    print("Lost connexion")
    running = False
    socket.close()

if __name__ == "__main__":
    tcpsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcpsock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    tcpsock.bind(("127.0.0.1", 2001))

    while True:
        if(not running):
            break
        tcpsock.listen(10)
        print( "Listening")
        (socket, (ip, port)) = tcpsock.accept()
        nbplayer = nbplayer + 1
        print( "next")


        if nbplayer < 2 :
            print("Waiting for at least two players...")
        else:
            print("Enough player has joined, we can start :)")

        start_new_thread(threadClient,(ip, port, socket))
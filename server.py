import socket
from _thread import *

nbPlayer = 0
running = True

def threadClient(ip, port, socket):
    global running
    global nbPlayer

    print("Creating new thread for host %s %s" % (ip, port, ))
    socket.send(str.encode("Hello Server"))

    while (True):
        try:
            resp = socket.recv(2048).decode()
            if not resp :
                print("null")
                break
            print("Connection from : %s %s" % (ip, port, ))
            print("Received : ", resp)
            if resp == "game":
                #running = True
                data = str(nbPlayer)
                data = str.encode(data)  
                socket.send(data)

            if(nbPlayer >= 4) :
                running = True
                data = "good"
                socket.send(str.encode(data))

        except:
            break

    print("Lost connexion")
    nbPlayer = nbPlayer - 1
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
        nbPlayer = nbPlayer + 1
        print( "next")


        if nbPlayer < 4 :
            print("Waiting for at least two players...")
        else:
            print("Enough player has joined, we can start :)")

        start_new_thread(threadClient,(ip, port, socket))
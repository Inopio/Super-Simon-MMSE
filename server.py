import socket
from _thread import *

nbPlayer = 0
running = True
playerList = []
socketList = []

def threadClient(ip, port, socket):
    global running
    global nbPlayer

    print("Creating new thread for host %s %s" % (ip, port, ))
    socket.send(str.encode("Hello Server"))

    while (True):
        try:
            resp = socket.recv(2048).decode()
            if not resp :
                print("Null")
                break
            if resp == "game":
                myNb = -1
                for i in range (len(playerList)):
                    if(playerList[i] == port):
                        myNb = i
                data = str(myNb)
                data = str.encode(data)  
                socket.send(data)

            elif resp == "perdu":
                print(resp)
                for s in socketList :
                    s.send(str.encode("perdu"))
            else:
                socket.send(str.encode("Connection maintain"))

            if(nbPlayer >= 4) :
                running = True
                data = "good"
                socket.send(str.encode(data))
            
        except:
            break

    print("Lost connexion")
    nbPlayer = nbPlayer - 1
    #running = False
    socket.close()

if __name__ == "__main__":
    tcpsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcpsock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    tcpsock.bind(("192.168.1.38", 2356))

    while True:
        #if(not running):
            #break
        tcpsock.listen(10)
        print( "Listening")
        (socket, (ip, port)) = tcpsock.accept()
        nbPlayer = nbPlayer + 1

        playerList.append(port)
        print("sockets :")
        socketList.append(socket)
        print(socketList)

        if nbPlayer < 4 :
            print("Waiting for at least two players...")
            
        else:
            print("Enough player has joined, we can start :)")

        start_new_thread(threadClient,(ip, port, socket))
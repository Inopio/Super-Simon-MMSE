import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 2001))

#receivedMyNb = False
nbPlayer = -1

while(True):
    s.send(str.encode("game"))
    try:
        data = s.recv(2048).decode()
        if not data :
            print("Null received")
            break
        else :
            #print(data)
            if(data == "good"):
                print("WOUHOU!")

            elif(data.isnumeric()):
                nbPlayer = data
                print("var from server")
                print("nbplayer = ", nbPlayer)
                receivedMyNb = True
                #break

            else:
                #s.send(str.encode("game"))
                print("Not enough players :(")
    except:
        print("Connection closed")
        break
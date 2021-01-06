import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 2001))

s.send(str.encode("ok"))
print("Sent !")
while(True):
    try:
        data = s.recv(2048).decode()
        if not data :
            print("Null received")
            break
        else :
            print(data)
            if(data == "good"):
                print("WOUHOU!")
            else:
                print("Not enough players :(")
    except:
        print("Except ok?")
        break
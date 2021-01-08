import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 2001))



while(True):
    try:
        s.send(str.encode("game"))
        data = s.recv(2048).decode()
        if not data :
            print("Null received")
            break
        else :
            print(data)
            if(data == "good"):
                print("WOUHOU!")

            elif(data.isnumeric()):
                nbPlayer = data
                print("var from server")
                print("nbplayer = ", nbPlayer)
                #break

            else:
                #s.send(str.encode("game"))
                print("Not enough players :(")
    except:
        print("Connection closed")
        break



''' TODO:
- Check l'envoi utilisateur -> checkMove()
envoyer au joueur via Serial COM le joueur actuel
pour afficher sur LCD later '=-> sendToArduino()

- Ameliorer la prise en charge du nombre de participant
qui n'est pas encore fonctionnelle
''' 
'''
def round():
    global pattern
    global nbRounds

    for i in range (requiredNbPlayers):
        player = pattern.append(random.randint(a=1, b=requiredNbPlayers))
        print(player)
    nbRounds = len(pattern) / requiredNbPlayers
'''

''' 
if(finishedRound):
    print("You passed the round ",nbRounds)
    round()

elif(isGameOver):
    pattern = []
    nbRounds = 0
    round()'''
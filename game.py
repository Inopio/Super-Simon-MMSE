import random
import server

pattern = []
nbRounds = 0
isGameOver = False
finishedRound = False

def round():
    for i in range (4):
        player = pattern.append(random.randint(a=1, b=4))
        print(player)
    nbRounds = len(pattern) / 4
    

def game():
    #global server.running
    #global server.nbplayer
    
    while(server.running):
        print("var from server")
        print("nbplayer = ", server.nbplayer)
        #print("running = ", server.running)
        break
        if(finishedRound):
            print("You passed the round ",nbRounds)
            round()
        elif(isGameOver):
            pattern = []
            nbRounds = 0
            round()

game()
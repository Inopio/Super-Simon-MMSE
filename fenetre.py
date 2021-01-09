import pygame

pygame.init()

BLUE = 43,191,247
WHITE = 255, 255, 255
YELLOW = 247,219,43
RED = 255, 0, 0
ORANGE = 247, 87,43
GREEN = 86,247,43

player_counter = 0

pygame.display.set_caption('Simon')
screen = pygame.display.set_mode((640, 480))
    
rect_color = BLUE
loop = True
in_game = True
click = False
rect = True
player_list= ["Player 1","Player 2","Player 3","Player 4"]
player_color_list = [RED,YELLOW,GREEN,BLUE]

for i in range (0,4):
    player_number = player_list[i]
    player_color = player_color_list[i]
    

myfont = pygame.font.SysFont("Comic Sans MS", 30) 
while loop:
    if(player_counter == 4):
        loop = False
    background = pygame.Surface(screen.get_size())
    background.fill(ORANGE)

    # Ajout du fond dans la fenêtre
    screen.blit(background, (0, 0))
    if(rect == True):
        rect_green = pygame.draw.rect(screen, rect_color, [250, 15, 125, 50])

    # retourne 1 si le curseur est au dessus du rectangle
        mouse_xy = pygame.mouse.get_pos()
        over_button = rect_green.collidepoint(mouse_xy)

    #police d'écriture
        

    if(click == True):
        label = myfont.render(player_number, 1, player_color)
    else:
        label = myfont.render("Join Game", 1, YELLOW)

    screen.blit(label, rect_green) 
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
                loop = False
        elif event.type == pygame.MOUSEBUTTONDOWN and over_button:
            click = True
            rect_color = WHITE
            rect = False

    # Actualisation de l'affichage
    pygame.display.flip()

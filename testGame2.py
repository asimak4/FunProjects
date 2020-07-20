import pygame
import sys
import random

WIDTH = 500
HEIGHT = 500
WHITE = (255,255,255)
BLUE = (0,0,255)
RED = (255,0,0)

screen = pygame.display.set_mode((WIDTH,HEIGHT))

player_size = 20
player_pos = [300,HEIGHT-(player_size)*3]
game_Over = False
while(not game_Over):
	for event in pygame.event.get():
		# quitting the screen
		if event.type == pygame.QUIT:
			sys.exit()
	screen.fill(WHITE)
	#[(x1, y1), (x2, y2), (x3, y3)]
	#bright, bleft,top
	
	x = player_pos[0]
	y = player_pos[1]
	#player = pygame.draw.rect(screen,BLUE,(player_pos[0],player_pos[1],player_pos[2]))
	
	#x = bottom right corner
	#y = bottom left corner
	#z = top point
	leftWallPos = [0,0]
	rightWallPos = [400,0]

	keystate = pygame.key.get_pressed()
	if(keystate[pygame.K_UP]):
		y -= 10
	elif(keystate[pygame.K_DOWN]):
		if(player_pos[1] < 480):
			y += 10
	elif(keystate[pygame.K_LEFT]):
		if(player_pos[0] > 100):
			x -= 10
	elif(keystate[pygame.K_RIGHT]):
		if(player_pos[0] < 380):
			x += 10
	player_pos[1] = y
	player_pos[0] = x


	# refreshing the background from the red dot tracing 
	screen.fill(WHITE)
	player = pygame.draw.rect(screen,BLUE,(player_pos[0],player_pos[1],player_size,player_size)) 
	leftWall = pygame.draw.rect(screen, RED,(leftWallPos[0],leftWallPos[1],100,500))
	rightWall = pygame.draw.rect(screen, RED,(rightWallPos[0],rightWallPos[1],100,500))

	

	pygame.display.update()
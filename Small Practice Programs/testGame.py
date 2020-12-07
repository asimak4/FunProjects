import pygame
import sys
import random

pygame.init()

WIDTH = 600
HEIGHT = 400

RED = (255,0,0)
BLACK = (0,255,0)
BLUE = (0,0,255)
YELLOW = (255,255,0)

myFont = pygame.font.SysFont("monospace",35)


#displaying the screen with the designated size
screen = pygame.display.set_mode((WIDTH,HEIGHT))

player_size = 33
# pos = width, height
player_pos = [300,HEIGHT-40]

score = 0
SPEED = 1

enemy_size = 10
enemy_pos = [random.randint(0,WIDTH-enemy_size),0]
enemy_list = [enemy_pos]

player_sprite = pygame.image.load("player.png")#.convert()
#p_rect = player_sprite.get_rect()

enemy_sprite = pygame.image.load("enemy.png")#.convert()
#e_rect = player_sprite.get_rect()

#displaying the screen with the designated size

size = player_sprite.get_size()
# create a x/2 bigger image than self.image
player_sprite = pygame.transform.scale(player_sprite, (int(size[0]/2), int(size[1]/2)))


#screen = pygame.display.set_mode((WIDTH,HEIGHT))

game_Over = False

clock = pygame.time.Clock()
def set_level(score,SPEED):
	if(score < 40):
		SPEED = 11
	elif(score < 60):
		SPEED = 12
	elif(score < 80):
		SPEED = 13
	elif(score > 100):
		SPEED = 15
	return SPEED


def update_enemy_position(enemy_list,score):
	for idx,enemy_pos in enumerate(enemy_list):
		if enemy_pos[1] >= 0 and enemy_pos[1] < HEIGHT:
			enemy_pos[1] += SPEED
		else:
			enemy_list.pop(idx)
			score += 1
	return score

def collision_check(enemy_list,player_pos):
	for enemy_pos in enemy_list:
		if(detect_coll(enemy_pos,player_pos)):
			return True
	return False

def add_ememies(enemy_list):
	delay = random.random()
	if(len(enemy_list) < 10) and delay < 0.2:
		x_pos = random.randint(0,WIDTH-enemy_size)
		y_pos = 0
		enemy_list.append([x_pos,y_pos])

def draw_enemy(enemy_list):
	for enemy_pos in enemy_list:
		screen.blit(enemy_sprite,(enemy_pos[0],enemy_pos[1]))
		#pygame.draw.rect(screen,BLUE,(enemy_pos[0],enemy_pos[1],enemy_size,enemy_size))


def detect_coll(player_pos,enemy_pos):
	p_x = player_pos[0]
	p_y = player_pos[1]

	e_x = enemy_pos[0]
	e_y = enemy_pos[1]

	if(e_x >= p_x and e_x < (p_x + player_size)) or (p_x >= e_x and p_x < (e_x + enemy_size)):
		if(e_y >= p_y and e_y < (p_y + player_size)) or (p_y >= e_y and p_y < (e_y+enemy_size)):
			return True
	return False
	#if pygame.sprite.collide_rect(p_rect, e_rect): 
	#	print(yes)
	#collideCheck = pygame.sprite.collide_mask(p_rect, e_rect)
	#collideCheck = pygame.sprite.spritecollide(player_sprite, enemy_sprite, True)
	#return True

#making the game loop 
while(not game_Over):
	for event in pygame.event.get():
		# quitting the screen
		if event.type == pygame.QUIT:
			sys.exit()
	x = player_pos[0]
	keystate = pygame.key.get_pressed()
	if(keystate[pygame.K_LEFT]):
		if(player_pos[0] > 0):
			x -= 16 
	elif(keystate[pygame.K_RIGHT]):
		if(player_pos[0] < 570):
			x += 16
	player_pos[0] = x


	# refreshing the background from the red dot tracing 
	screen.fill(BLACK)

	add_ememies(enemy_list)
	score = update_enemy_position(enemy_list,score)
	#print(score)

	SPEED = set_level(score,SPEED)


	text = "Score: " + str(score) 
	label = myFont.render(text,1,YELLOW)
	screen.blit(label,(WIDTH-200, HEIGHT-20))
	
	if(collision_check(enemy_list,player_pos)):
		game_Over = True
		break

	draw_enemy(enemy_list)
	screen.blit(player_sprite,(player_pos[0],player_pos[1]))
	#pygame.draw.rect(screen,RED,(player_pos[0],player_pos[1],player_size,player_size))

	pygame.display.update()



print("Thank you for playing! Your final score was: " + str(score))


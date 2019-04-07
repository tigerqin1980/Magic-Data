"""
Created on Fri Sept 7  10:56 2018

@author: Graham
"""

import pygame
import sys
import time
import random
from pygame.locals import *


# 定义颜色变量
redColour = pygame.Color(255,0,0)
blackColour = pygame.Color(0,0,0)
whiteColour = pygame.Color(255,255,255)
greyColour = pygame.Color(150,150,150)
LightGrey = pygame.Color(220,220,220)


# 定义gameOver函数
def gameOver(playSurface, score):
    # 显示GAME OVER并定义字体以及大小
    gameOverFont = pygame.font.Font('arial.ttf', 72)
    gameOverSurf = gameOverFont.render('Game Over', True, greyColour)
    gameOverRect = gameOverSurf.get_rect()
    gameOverRect.midtop = (320, 125)
    playSurface.blit(gameOverSurf, gameOverRect)
    # 显示分数并定义字体和大小
    scoreFont = pygame.font.Font('arial.ttf', 48)
    scoreSurf = scoreFont.render('SCORE: ' + str(score), True, greyColour)
    scoreRect = scoreSurf.get_rect()
    scoreRect.midtop = (320, 225)
    playSurface.blit(scoreSurf, scoreRect)
    pygame.display.flip()  # 刷新显示界面
    # 休眠5秒后自动关闭
    time.sleep(5)
    pygame.quit()
    sys.exit()


# 定义main函数
def main():
    # 初始化pygame
    pygame.init()
    fpsClock = pygame.time.Clock()

    # 创建pygame显示层
    playSurface = pygame.display.set_mode((640, 480))
    # 定义标题
    pygame.display.set_caption('Snake Go!')
    # 加载资源图片，game.ico包含在最后的文件中
    image = pygame.image.load('game.ico')
    # 设置图标
    pygame.display.set_icon(image)

    # 初始化变量
    snakePosition = [100, 100]  # 蛇头位置
    snakeSegments = [[100, 100], [80, 100], [60, 100]]  # 初始长度为3个单位
    raspberryPosition = [300, 300]  # 树莓位置
    raspberrySpawned = 1  # 树莓个数
    direction = 'right'  # 初始方向
    changeDirection = direction
    score = 0  # 初始分数
    while True:
        # 检测例如按键等pygame事件
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == KEYDOWN:
                # 判断键盘事件
                if event.key == K_RIGHT or event.key == ord('d'):
                    changeDirection = 'right'
                if event.key == K_LEFT or event.key == ord('a'):
                    changeDirection = 'left'
                if event.key == K_UP or event.key == ord('w'):
                    changeDirection = 'up'
                if event.key == K_DOWN or event.key == ord('s'):
                    changeDirection = 'down'
                if event.key == K_ESCAPE:  # 按esc退出游戏
                    pygame.event.post(pygame.event.Event(QUIT))

        # 判断是否输入了反方向
        if changeDirection == 'right' and not direction == 'left':
            direction = changeDirection
        if changeDirection == 'left' and not direction == 'right':
            direction = changeDirection
        if changeDirection == 'up' and not direction == 'down':
            direction = changeDirection
        if changeDirection == 'down' and not direction == 'up':
            direction = changeDirection

        # 根据方向移动蛇头的坐标
        if direction == 'right':
            snakePosition[0] += 20
        if direction == 'left':
            snakePosition[0] -= 20
        if direction == 'up':
            snakePosition[1] -= 20
        if direction == 'down':
            snakePosition[1] += 20

        # 将蛇头的位置加入列表之中
        snakeSegments.insert(0, list(snakePosition))

        # 判断是否吃掉了树莓
        if snakePosition[0] == raspberryPosition[0] and snakePosition[1] == raspberryPosition[1]:
            raspberrySpawned = 0
        else:
            snakeSegments.pop()  # 每次将最后一单位蛇身踢出列表

        # 如果吃掉树莓，则重新生成树莓
        if raspberrySpawned == 0:
            x = random.randrange(1, 32)
            y = random.randrange(1, 24)
            raspberryPosition = [int(x*20), int(y*20)]
            raspberrySpawned = 1
            score += 1
            

        # 绘制pygame显示层
        playSurface.fill(blackColour)
        for position in snakeSegments[1:]:  # 蛇身为白色
            pygame.draw.rect(playSurface, whiteColour, Rect(position[0], position[1], 20, 20))
        pygame.draw.rect(playSurface, LightGrey, Rect(snakePosition[0], snakePosition[1], 20, 20))  # 蛇头为灰色
        pygame.draw.rect(playSurface, redColour, Rect(raspberryPosition[0], raspberryPosition[1], 20, 20))  # 树莓为红色
        # 刷新pygame显示层
        pygame.display.flip()

        # 判断是否死亡
        if snakePosition[0] > 620 or snakePosition[0] < 0:  # 超出左右边界
            gameOver(playSurface, score)
        if snakePosition[1] > 460 or snakePosition[1] < 0:  # 超出上下边界
            gameOver(playSurface, score)
        for snakeBody in snakeSegments[1:]:  # 蛇碰到自己身体
            if snakePosition[0] == snakeBody[0] and snakePosition[1] == snakeBody[1]:
                gameOver(playSurface, score)

        # 控制游戏速度,长度越长速度越快
        if len(snakeSegments) < 40:
            speed = 6 + len(snakeSegments)//4
        else:
            speed = 16
        fpsClock.tick(speed)


if __name__ == "__main__":
    main()

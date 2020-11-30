import math
import random
import pygame
import tkinter as tk
from tkinter import messagebox
import numpy as np
from ctypes import c_void_p, c_double, c_int, cdll
from numpy.ctypeslib import ndpointer

pygame.init()


def setup(win, state):
    win.fill((0, 0, 255))

    for i in range(6):
        for j in range(7):
            pygame.draw.circle(win, (0, 0, 0), (j*100+50, i*100+50), 40)
            if state[i][j] == 1:
                pygame.draw.circle(win, (255, 0, 0), (j*100+50, i*100+50), 38)
            elif state[i][j] == -1:
                pygame.draw.circle(win, (0, 255, 0), (j*100+50, i*100+50), 38)

    pygame.display.update()


def isMovesLeft(state):

    for j in range(7):
        if state[0][j] == 0:
            return True

    return False


def checkWin(state):

    for i in range(6):
        for j in range(4):
            if state[i][j] == 1 and state[i][j+1] == 1 and state[i][j+2] == 1 and state[i][j+3] == 1:
                return 10
            elif state[i][j] == -1 and state[i][j+1] == -1 and state[i][j+2] == -1 and state[i][j+3] == -1:
                return -10

    for i in range(3):
        for j in range(7):
            if state[i][j] == 1 and state[i+1][j] == 1 and state[i+2][j] == 1 and state[i+3][j] == 1:
                return 10
            elif state[i][j] == -1 and state[i+1][j] == -1 and state[i+2][j] == -1 and state[i+3][j] == -1:
                return -10

    for i in range(3):
        for j in range(4):
            if state[i][j] == 1 and state[i+1][j+1] == 1 and state[i+2][j+2] == 1 and state[i+3][j+3] == 1:
                return 10
            elif state[i][j] == -1 and state[i+1][j+1] == -1 and state[i+2][j+2] == -1 and state[i+3][j+3] == -1:
                return -10

    for i in range(3):
        for j in range(3, 7):
            if state[i][j] == 1 and state[i+1][j-1] == 1 and state[i+2][j-2] == 1 and state[i+3][j-3] == 1:
                return 10
            elif state[i][j] == -1 and state[i+1][j-1] == -1 and state[i+2][j-2] == -1 and state[i+3][j-3] == -1:
                return -10

    return 0


def first_empty(state, col):

    temp = -1

    for i in range(6):

        if int(state[i][col]) != 0:
            break

        temp = i

    return temp


def move(win, state, col, player):

    temp = first_empty(state, col)

    if temp < 0:
        return False

    else:
        state[temp][col] = player
        setup(win, state)
        return True


def changePlayer(currPlayer):

    if currPlayer == 1:
        return -1
    else:
        return 1


def message_box(subject, content):
    root = tk.Tk()
    root.attributes("-topmost", True)
    root.withdraw()

    messagebox.showinfo(subject, content)

    try:
        root.destroy()
    except:
        pass


def reset(win):
    state = np.zeros((6, 7))
    setup(win, state)
    currPlayer = -1
    return state, currPlayer


def compMove(win, b):

    bestScore = -100

    best_x = 0
    best_y = 0

    lib = cdll.LoadLibrary("./minimax.so")
    c_sum = lib.minimax  # c_sum is the name of our C function
    c_sum.restype = np.int

    for j in [3, 2, 4, 1, 5, 0, 6]:

        i = first_empty(b, j)

        if i < 0:
            continue

        b[i][j] = 1
        score = c_sum(c_void_p(b.ctypes.data), 0,
                      False, -1000, 1000, 8)
        b[i][j] = 0

        print(j, score)

        if score > bestScore:
            bestScore = score
            best_x = i
            best_y = j

    b[best_x][best_y] = 1
    setup(win, b)


def main():

    win = pygame.display.set_mode((700, 600))
    clock = pygame.time.Clock()
    state = np.zeros((6, 7))

    setup(win, state)

    flag = True

    currPlayer = -1

    comp_move = True

    while flag:

        pygame.time.delay(50)
        clock.tick(10)

        if comp_move == True:
            comp_move = False
            compMove(win, state)

        else:

            for event in pygame.event.get():

                if event.type == pygame.QUIT:
                    pygame.quit()

                if event.type == pygame.MOUSEBUTTONUP:
                    x, _ = pygame.mouse.get_pos()

                    if (move(win, state, x//100, currPlayer) == False):
                        continue

                    # currPlayer = changePlayer(currPlayer)
                    comp_move = True

        if (checkWin(state) == 10):
            message_box("Red won!", "Play again")
            state, currPlayer = reset(win)

        if (checkWin(state) == -10):
            message_box("Green won!", "Play again")
            state, currPlayer = reset(win)

        if (isMovesLeft(state) == False):
            message_box("Draw!", "Play again")
            state, currPlayer = reset(win)


main()

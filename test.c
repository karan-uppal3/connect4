#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int MOVES[] = {3, 2, 4, 1, 5, 0, 6};

bool isMovesLeft(double *state)
{
    for (int j = 0; j < 7; j++)
    {
        if ((int)state[j] == 0)
            return true;
    }

    return false;
}

int checkWin(double *state)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((int)state[i * 7 + j] == 1 && (int)state[i * 7 + j + 1] == 1 && (int)state[i * 7 + j + 2] == 1 && (int)state[i * 7 + j + 3] == 1)
            {
                return 10;
            }
            else if ((int)state[i * 7 + j] == -1 && (int)state[i * 7 + j + 1] == -1 && (int)state[i * 7 + j + 2] == -1 && (int)state[i * 7 + j + 3] == -1)
            {
                return -10;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if ((int)state[i * 7 + j] == 1 && (int)state[(i + 1) * 7 + j] == 1 && (int)state[(i + 2) * 7 + j] == 1 && (int)state[(i + 3) * 7 + j] == 1)
            {
                return 10;
            }
            else if ((int)state[i * 7 + j] == -1 && (int)state[(i + 1) * 7 + j] == -1 && (int)state[(i + 2) * 7 + j] == -1 && (int)state[(i + 3) * 7 + j] == -1)
            {
                return -10;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((int)state[i * 7 + j] == 1 && (int)state[(i + 1) * 7 + j + 1] == 1 && (int)state[(i + 2) * 7 + j + 2] == 1 && (int)state[(i + 3) * 7 + j + 3] == 1)
            {
                return 10;
            }
            else if ((int)state[i * 7 + j] == -1 && (int)state[(i + 1) * 7 + j + 1] == -1 && (int)state[(i + 2) * 7 + j + 2] == -1 && (int)state[(i + 3) * 7 + j + 3] == -1)
            {
                return -10;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 3; j < 7; j++)
        {
            if ((int)state[i * 7 + j] == 1 && (int)state[(i + 1) * 7 + j - 1] == 1 && (int)state[(i + 2) * 7 + j - 2] == 1 && (int)state[(i + 3) * 7 + j - 3] == 1)
            {
                return 10;
            }
            else if ((int)state[i * 7 + j] == -1 && (int)state[(i + 1) * 7 + j - 1] == -1 && (int)state[(i + 2) * 7 + j - 2] == -1 && (int)state[(i + 3) * 7 + j - 3] == -1)
            {
                return -10;
            }
        }
    }

    return 0;
}

int first_empty(double *state, int col)
{
    int temp = -1;

    for (int i = 0; i < 6; i++)
    {
        if ((int)state[i * 7 + col] != 0)
            break;
        temp = i;
    }

    return temp;
}

int evaluate(double *state)
{
    int ctr1 = 0, ctr2 = 0;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if ((int)state[i * 7 + j] == 1 && (int)state[i * 7 + j + 1] == 1 && (int)state[i * 7 + j + 2] == 1)
            {
                ctr1 += 2;
            }
            else if ((int)state[i * 7 + j] == -1 && (int)state[i * 7 + j + 1] == -1 && (int)state[i * 7 + j + 2] == -1)
            {
                ctr2 += 2;
            }
        }
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if ((int)state[i * 7 + j] == 1 && (int)state[i * 7 + j + 1] == 1)
            {
                ctr1++;
            }
            else if ((int)state[i * 7 + j] == -1 && (int)state[i * 7 + j + 1] == -1)
            {
                ctr2++;
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if ((int)state[i * 7 + j] == 1 && (int)state[(i + 1) * 7 + j] == 1 && (int)state[(i + 2) * 7 + j] == 1)
            {
                ctr1 += 2;
            }
            else if ((int)state[i * 7 + j] == -1 && (int)state[(i + 1) * 7 + j + 1] == -1 && (int)state[(i + 2) * 7 + j + 2] == -1)
            {
                ctr2 += 2;
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if ((int)state[i * 7 + j] == 1 && (int)state[(i + 1) * 7 + j] == 1)
            {
                ctr1++;
            }
            else if ((int)state[i * 7 + j] == -1 && (int)state[(i + 1) * 7 + j + 1] == -1)
            {
                ctr2++;
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if ((int)state[i * 7 + j] == 1 && (int)state[(i + 1) * 7 + j + 1] == 1 && (int)state[(i + 2) * 7 + j + 2] == 1)
            {
                ctr1 += 2;
            }
            else if ((int)state[i * 7 + j] == -1 && (int)state[(i + 1) * 7 + j + 1] == -1 && (int)state[(i + 2) * 7 + j + 2] == -1)
            {
                ctr2 += 2;
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if ((int)state[i * 7 + j] == 1 && (int)state[(i + 1) * 7 + j + 1] == 1)
            {
                ctr1++;
            }
            else if ((int)state[i * 7 + j] == -1 && (int)state[(i + 1) * 7 + j + 1] == -1)
            {
                ctr2++;
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 2; j < 7; j++)
        {
            if ((int)state[i * 7 + j] == 1 && (int)state[(i + 1) * 7 + j - 1] == 1 && (int)state[(i + 2) * 7 + j - 2] == 1)
            {
                ctr1 += 2;
            }
            else if ((int)state[i * 7 + j] == -1 && (int)state[(i + 1) * 7 + j - 1] == -1 && (int)state[(i + 2) * 7 + j - 2] == -1)
            {
                ctr2 += 2;
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 1; j < 7; j++)
        {
            if ((int)state[i * 7 + j] == 1 && (int)state[(i + 1) * 7 + j - 1] == 1)
            {
                ctr1++;
            }
            else if ((int)state[i * 7 + j] == -1 && (int)state[(i + 1) * 7 + j - 1] == -1)
            {
                ctr2++;
            }
        }
    }

    return (ctr1 - ctr2) / 2;
}

int minimax(double *state, int depth, bool isMaximiser, int alpha, int beta, int MAX_DEPTH)
{
    int result = checkWin(state);

    if (result == 10 || result == -10)
        return result;

    if (isMovesLeft(state) == false)
        return 0;

    if (depth > MAX_DEPTH)
        return evaluate(state);

    if (isMaximiser == true)
    {
        int bestScore = -100, score;

        for (int j = 0; j < 7; j++)
        {
            int i = first_empty(state, j);

            if (i < 0)
            {
                continue;
            }

            state[i * 7 + j] = 1;
            score = minimax(state, depth + 1, false, alpha, beta, MAX_DEPTH);
            state[i * 7 + j] = 0;

            bestScore = (bestScore > score) ? bestScore : score;
            alpha = (alpha > bestScore) ? alpha : bestScore;

            if (beta <= alpha)
                break;
        }

        return bestScore;
    }
    else
    {
        int bestScore = 100, score;

        for (int j = 0; j < 7; j++)
        {
            int i = first_empty(state, j);

            if (i < 0)
                continue;

            state[i * 7 + j] = -1;
            score = minimax(state, depth + 1, true, alpha, beta, MAX_DEPTH);
            state[i * 7 + j] = 0;

            bestScore = (bestScore < score) ? bestScore : score;
            beta = (beta < bestScore) ? beta : bestScore;

            if (beta <= alpha)
                break;
        }

        return bestScore;
    }
}

/*
int main()
{
    double *state = (double *)calloc(6 * 7, sizeof(double));

    int bestScore = -100, score;
    int best_x = 0, best_y = 0;

    for (int j = 0; j < 7; j++)
    {
        int i = first_empty(state, MOVES[j]);

        if (i < 0)
            continue;

        state[i * 7 + MOVES[j]] = 1;
        score = minimax(state, 0, false, -1000, 1000, 12);
        state[i * 7 + MOVES[j]] = 0;

        if (score > bestScore)
        {
            bestScore = score;
            best_x = i;
            best_y = MOVES[j];
        }
    }

    printf("%d,%d", best_x, best_y);

    return 0;
}
*/
# Connect 4 with Minimax
Connect 4 is implemented using Pygame, using the help of C based code to run the Minimax algorithm for faster computation.

Run these commands to start  
```
cc -fPIC -shared -o minimax.so test.c
python3 test.py
```

# To-do
1. Implement transposition table
2. Implement iterative deepening
3. Improve the evaluate function
4. Use bit manipulation to get faster results

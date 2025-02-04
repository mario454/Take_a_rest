# TAKE A REST

## Participated in this project:

- **Mario Atef**: Main menu, System management and score tracking
- **Mario Saleh**: Guess the number and Snake game
- **Abdel Raouf Abdel Karim**: Bong game
- **Beshoy Nabel**: X&O game

---

## Introduction

**Take a Rest** is a program that includes a simple file management system to store usernames, passwords, and game scores. It features 4 games:

- **Bong** (Multiplayer)
- **X&O** (Multiplayer)
- **Snake** (Single Player)
- **Guess the Number** (Single Player)

---

## File Management System

### Shape()

Generates a rectangle or square using ASCII characters:

- char(201) [╔ ]
- char(205) [ ═ ]
- char(187) [ ╗]
- char(186) [ ║ ]
- char(200) [ ╚ ]
- char(188) [ ╝ ]

\*\*Variable \*\***`DD`**

- If `DD == 0`: The user is in the main page.
- If `DD == 1`: The user is in the games page (display username and high score).

### reg() : (Register)

Prompts the user for a username and checks if it already exists using `check_username()`.

- If the username exists, the user is prompted to re-enter.
- If not, it calls the `pass()` function for password input.\
  Password is confirmed via `confirm_password()`.\
  Once confirmed, user details are saved, and the user enters the games page with an initial score.

### login()

Prompts the user for username.

- If the username does not exist, the user is prompted to register (`reg()`).
- If the username exists, the user is prompted to input a password (`pass()`).
- Password is verified using `check_password()`.\
  If wrong, the user can reset it via `forget_password()`.

### check\_username()

Validates if the username exists in the file.

### pass()

Prompts the user for a password with conditions:

- Minimum 8 characters
- At least one of \*!@%
- Cannot include a comma (`,`).

### confirm\_password()

Checks if the re-entered password matches the original password.

### check\_password()

Verifies if the username-password combination exists in the file.

### forget\_password()

Allows users to reset their password.

### get\_data()

Fetches user information (username, password, high score) from the file.

### update()

Updates the high score after playing Snake or Guess the Number if the new score is higher than the previous.

### games()

Displays the game menu and allows users to choose and play a game.

---

## Games

### Guess the Code

A unique number guessing game.\
Functions include:

- `Arandom_number()`: Generates a number between 1000-9999.
- `NumToDigits()`: Converts the guessed number and random number into digits for comparison.
- `run()`: Main function to enter guesses and compare them to the random number.

### Snake Game

The classic snake game.\
Functions include:

- `print()`: Displays the field, snake, and fruit.
- `input()`: Handles user input to control the snake's direction.
- `logic()`: Manages the snake’s movement, tail, gameover logic, and score increment.
- `run_game()`: Combines all functions to run the game.

### Bong Game

A simple multiplayer ping pong game using 3 classes:

- **cBall**: Manages the ball’s position, movement, and direction.
- **cPaddle**: Handles the paddle’s movement.
- **cGameManager**: Manages the game’s flow, including drawing, input handling, and game logic.

### X&O Game

The classic tic-tac-toe game.\
Functions include:

- `getread()`: Inputs player names and characters.
- `XOGame()`: Main game function, calling other functions for playing and checking the winner.
- `choose()`: Allows players to place their characters on the grid.
- `menu()`: Displays player names, scores, and the game box.
- `checkXO()`: Checks for a winner or a draw.

---

## Features We Could Have Added:

- Header files for the games to simplify debugging and code readability.
- Music and sound effects.
- Basic graphics for an improved user experience.


#ifndef UTILS_H
# define UTILS_H

# include <termios.h>

/*
responsible for initializing the terminal input settings to hide typed characters.

It first retrieves the current terminal settings using tcgetattr,
then itmodifies the c_lflag (local modes) of the terminal attributes to disable the ECHOCTL flag.
The ECHOCTL flag controls whether special control characters should be echoed (displayed)
on the terminal when entered. By setting it to zero, this function ensures that control
characters are not displayed on the screen
*/
void	init_termios(void);

/*
used to reset the terminal input settings to their default state, where typed characters are displayed on the screen.

Similar to the init_termios function,
this function also retrieves the current terminal settings using tcgetattr and then modifies
the c_lflag by enabling the ECHOCTL flag. By doing this, it restores the terminal to its default behavior,
where control characters are displayed when entered by the user.
*/
void	reset_termios(void);

#endif
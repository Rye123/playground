# menu_shellscript

This is a quick and dirty shell script that:
1. Gives a login prompt, demanding a passcode from a list of hardcoded passcodes.
2. Uses a `select` command to display a menu that:
	- Allows reading of a `USERNAME` variable from the earlier login prompt.
	- Prints out a hardcoded file `.menuConfig` in the same directory.

Run with `./test.sh`.

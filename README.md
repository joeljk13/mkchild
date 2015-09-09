mkchild
=======

A quick, simple program for running another process as a child.

Often I find that I want to be able to run `killall XXX` to kill process and
its children, but often that process is a shell script, meaning that that
command would also kill the shell instances that I want to keep. This program
solves that by being the program to kill - just run `killall mkchild` and all
its children will die.

(Or you can use `pkill` instead of `killall`, I think. I don't know `pkill` as
well as `killall`.)

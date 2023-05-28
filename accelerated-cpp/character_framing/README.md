# character_framing

A simple program that frames a given string, such that the string is centralised within the 'frame'.

## Installation
```bash
make
```

## Usage
```bash
./main < [text file]
```

To define separated frames, use `!===!===!` as a delimiter between lines.

For instance, the following text file:
```
the quick brown
fox jumps over the lazy dog.
!===!===!
Peter Piper picks a peck of pickled peppers.
!===!===!
She sells sea shells
by the sea shore.
!===!===!
Lorem ipsum
dolor
sit
amet.
```

will be split into:
```
********************************
*       the quick brown        *
* fox jumps over the lazy dog. *
********************************
************************************************
* Peter Piper picks a peck of pickled peppers. *
************************************************
************************
* She sells sea shells *
*  by the sea shore.   *
************************
***************
* Lorem ipsum *
*    dolor    *
*     sit     *
*    amet.    *
***************
```

Further, `main` will concatenate them such that we have two frames every row, in the following way:
```
******************************** ************************************************
*       the quick brown        * * Peter Piper picks a peck of pickled peppers. *
* fox jumps over the lazy dog. * ************************************************
********************************
************************ ***************
* She sells sea shells * * Lorem ipsum *
*  by the sea shore.   * *    dolor    *
************************ *     sit     *
                         *    amet.    *
                         ***************
```

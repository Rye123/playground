# ascender-descender-detection

A program that outputs the longest word without ascenders or descenders in a given text file.

## Installation
```bash
make
```

To run unit tests, do
```bash
make test
```

## Usage
```bash
./main < [text file]
```

### Example
Using `words.txt` from https://github.com/dwyl/english-words, we get `noncarnivorousness` as the longest word without ascenders or descenders.

## Problem Statement
Write a program to determine whether a word has any ascenders or descenders.
- **Ascender**: A part of lowercase letters that extends above the textline (`b, d, f, h, k, l, t`)
- **Descender**: A part of lowercase letters that descends beneath the textline. (`g, j, p, q, y`)

Extend that program to find the longest word in the dictionary with no ascenders or descenders.


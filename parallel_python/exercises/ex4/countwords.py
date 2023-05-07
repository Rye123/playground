"""
https://milliams.com/courses/parallel_python/Map%20Reduce.html#Exercise-2

Task:
Use the two given functions:
- `count_words(filename)
- `reduce_dicts(dict1, dict2)`

to write a parallel Python script called `countwords.py` that \
counts how many times each word used by Shakespeare appears in \
all of his plays, e.g. by using the command line call
```
python countwords.py shakespeare
```

Have your script print out every word that appears more than \
2000 times across all of the plays. The words should be printed \
out in alphabetical order, and printed together with the \
number of times that they are used.
"""

import re
from typing import Dict, Any
from pathlib import Path
from concurrent.futures import ProcessPoolExecutor
from functools import reduce

def count_words(filename: str) -> Dict[str, int]:
    """
    Count the number of times every word in the file `filename`
    is contained in this file.

    Args:
        filename (str): the filename to count the words in

    Returns:
        dict: a mapping of word to count
    """

    all_words = {}

    with open(filename) as f:
        for line in f:
            words = line.split()

            for word in words:
                #lowercase the word and remove all
                #characters that are not [a-z] or hyphen
                word = word.lower()
                match = re.search(r"([a-z\-]+)", word)

                if match:
                    word = match.groups()[0]

                    if word in all_words:
                        all_words[word] += 1
                    else:
                        all_words[word] = 1

    return all_words

def reduce_dicts(dict1: Dict[Any, Any], dict2: Dict[Any, Any]) -> Dict[Any, Any]:
    """
    Combine (reduce) the passed two dictionaries to return
    a dictionary that contains the keys of both, where the
    values are equal to the sum of values for each key
    """

    # explicitly copy the dictionary, as otherwise
    # we risk modifying 'dict1'
    combined = {}

    for key in dict1:
        combined[key] = dict1[key]

    for key in dict2:
        if key in combined:
            combined[key] += dict2[key]
        else:
            combined[key] = dict2[key]

    return combined

if __name__ == "__main__":
    from sys import argv, exit
    if len(argv) != 2:
        print("Input directory.")
        exit(1)
    dirpath = Path(argv[1])
    all_words = []

    with ProcessPoolExecutor() as pool:
        # Get words for each filename
        all_words = pool.map(count_words, dirpath.iterdir())

    words = reduce(reduce_dicts, all_words)
    
    # map words to a set of tuples
    word_tups = map(lambda tup: tup, words.items())
    
    # filter out words appearing less than 2000 times
    word_tups_filtered = filter(lambda tup : tup[1] > 2000, word_tups)

    # sort in alphabetical order
    sorted_word_tups = sorted(word_tups_filtered, key=lambda word_tup: word_tup[0])
    
    # print nicely
    for word_tup in sorted_word_tups:
        print(f"{word_tup[0]}: {word_tup[1]}")
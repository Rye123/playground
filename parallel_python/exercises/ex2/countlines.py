"""
https://milliams.com/courses/parallel_python/Reduce.html#Exercise

Task: 
Modify your countlines.py script so that, in addition to \
printing out the total number of lines in each Shakespeare play, \
it also uses reduce to print out the total number of lines in all \
Shakespeare plays.
"""
from pathlib import Path
from functools import reduce

def file_line_counter(path: Path) -> int:
    """
    Returns the number of lines in a file at `path`.
    """
    with path.open('r') as f:
        return len(f.readlines())

if __name__ == "__main__":
    from sys import argv, exit
    if len(argv) != 2:
        print("Input directory.")
        exit(1)
    dirpath = Path(argv[1])

    if not (dirpath.exists() and dirpath.is_dir()):
        print("Directory does not exist.")
    
    file_line_counts = list(map(file_line_counter, dirpath.iterdir()))
    print(file_line_counts)
    total_lines = reduce(lambda x, y: x + y, file_line_counts)
    print(total_lines)
    

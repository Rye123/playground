"""
https://milliams.com/courses/parallel_python/Map.html#Exercise

Task: 
Write a Python script, called countlines.py, that will count the \
total number of lines in each of these Shakespeare plays, \
that can be run in the Terminal with:
```
python countlines.py shakespeare
```
"""
from pathlib import Path

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
    
    file_line_counts = map(file_line_counter, dirpath.iterdir())
    print(list(file_line_counts))
    

"""
https://milliams.com/courses/parallel_python/Map%20Reduce.html#Exercise-1

Task: 
Edit your countlines.py script that you wrote for Part 1 so that \
you use concurrent.futures to parallelise the counting of lines. \
Note that you will not be able to use `lambda` in the `pool.map` \
function.
"""

from pathlib import Path
import concurrent.futures

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
    with concurrent.futures.ProcessPoolExecutor() as pool:
        file_line_counts = pool.map(file_line_counter, dirpath.iterdir())
    print(list(file_line_counts))
    

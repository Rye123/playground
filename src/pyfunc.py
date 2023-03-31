from typing import Callable, Iterable, Any, List
from copy import deepcopy

def map(fn: Callable, ls: List[Any], *args, **kwargs) -> List[Any]:
    """
    Applies a function `fn` on every element in `ls`.
    """
    ret = deepcopy(ls)
    for i in range(len(ret)):
        ret[i] = fn(ret[i], *args, **kwargs)
    return ret

def reduce(fn: Callable[[Any, Any], Any], ls: List[Any], initialiser=None) -> Any:
    """
    Aggregates values by applying an aggregation function `fn` \
    sequentially on `ls` and returning the final result.
    - `fn` is a function that takes two arguments:
        - The left argument is the accumulated value.
        - The right argument is the next value in the list.
    """
    if len(ls) == 0:
        raise ValueError("Cannot reduce an empty list.")
    if len(ls) == 1:
        if initialiser is not None:
            return fn(initialiser, ls[0])
        return ls[0]
    acc = reduce(fn, ls[:-1], initialiser) # Accumulated value
    return fn(acc, ls[-1])
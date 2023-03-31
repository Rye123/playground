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
from typing import Callable, Iterable
from copy import deepcopy

def map(fn: Callable, ls: Iterable, *args, **kwargs):
    ret = deepcopy(ls)
    for i in range(len(ret)):
        ret[i] = fn(ret[i], *args, **kwargs)
    return ret
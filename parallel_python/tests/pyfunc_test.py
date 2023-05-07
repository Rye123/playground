import unittest
import src.pyfunc as pyfunc

class MapTest(unittest.TestCase):
    def test_map_works_single_arg(self):
        def addOne(x):
            return x + 1

        ls1 = [1, 2, 3, 4, 5]
        ls1_exp = [2, 3, 4, 5, 6]
        ls1_test = pyfunc.map(addOne, ls1)
        self.assertEqual(ls1_test, ls1_exp)
    
    def test_map_works_multi_args(self):
        ls1 = [1, 2, 3, 4, 5]
        ls1_exp = [3, 4, 5, 6, 7]
        def add(x, y):
            return x+y
        
        ls1_test = pyfunc.map(add, ls1, 2)
        self.assertEqual(ls1_test, ls1_exp)

        def add_elem(ls, elem):
            return ls + [elem]
        
        ls2 = [[1], [2], [3]]
        ls2_exp = [[1, 2], [2, 2], [3, 2]]
        
        ls2_test = pyfunc.map(add_elem, ls2, 2)
        self.assertEqual(ls2_test, ls2_exp)

class ReduceTest(unittest.TestCase):
    def test_reduce_addition(self):
        ls1 = [1, 2, 3, 4, 5, 6]
        ls1_exp_1 = sum(ls1)
        ls1_exp_2 = sum(ls1) + 6

        ls1_test_1 = pyfunc.reduce(lambda x, y: x + y, ls1)
        ls1_test_2 = pyfunc.reduce(lambda x, y: x + y, ls1, 6)
        self.assertEqual(ls1_test_1, ls1_exp_1)
        self.assertEqual(ls1_test_2, ls1_exp_2)

    def test_reduce_lists(self):
        ls1 = [[1, 2], [3, 4], [5, 6]]
        ls1_exp_1 = [1, 2, 3, 4, 5, 6]

        ls1_test_1 = pyfunc.reduce(lambda x, y: x + y, ls1) 
        self.assertEqual(ls1_test_1, ls1_exp_1)

    def test_reduce_strings(self):
        ls1 = ["cat", "dog", "elephant", "fish"]
        def join_str(x, y):
            return f"{x} {y}"
        ls1_exp = "cat dog elephant fish"
        ls1_test = pyfunc.reduce(join_str, ls1)
        self.assertEqual(ls1_test, ls1_exp)
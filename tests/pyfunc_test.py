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



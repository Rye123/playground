import unittest
from simple_ast import *

class TestProcess(unittest.TestCase):
    def test_process(self):
        self.assertEqual(process("1 + 1"), 2.0)
        self.assertEqual(process("2 * 2"), 4.0)
        self.assertEqual(process("1 + 2 * 1"), 3.0)
        self.assertEqual(process("2 + 6 * 3"), 20.0)
        self.assertEqual(process("1/2 + 1/2 + 1/2"), 1.5)
        self.assertAlmostEqual(process("1/2 - 1/2"), 0.0)
        self.assertAlmostEqual(process("3/2 - 1/2 * 3"), 0.0)

import unittest
from business.sortari import quick_sort, shake_sort


class TestSortari(unittest.TestCase):

    def setUp(self):
        self.lista1 = [2, 7, 10, 8, 3, 5, 9, 6, 1, 4]
        self.lista2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

    def test_quick_sort(self):
        self.assertEqual(self.lista2, quick_sort(self.lista1))

    def test_shake_sort(self):
        self.assertEqual(self.lista2, shake_sort(self.lista1))

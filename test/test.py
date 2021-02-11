from wrapper import TestTemplate

import pytest


class TestJsonHTTP(TestTemplate):
    def test_ok(self):
        self.execute({
            'index': 'category_0',
            'match': 'iPhone'
        }, Proto.JSON)

    def test_incorrect_query(self):
        with pytest.raises(Exception):
            self.execute({
                'index': 'category_0',
            }, Proto.JSON)

        with pytest.raises(Exception):
            self.execute({
                'match': 'iPhone'
            }, Proto.JSON)


class TestClassBasic(TestTemplate):
    def test_ping(self):
        code = self.ping()
        assert code == 200

    def test_syntax_error(self):
        with pytest.raises(Exception):
            self.execute('select *;')

    def test_no_such_index(self):
        with pytest.raises(Exception):
            self.execute('select * from test;')

    def test_dummy_index(self):
        code, result = self.execute('select * from category_0 where match("hi");')
        assert len(result) == 0

        code, result = self.execute('select * from category_0 where match("защитное стекло");')
        assert len(result) > 0
        assert result[0] == [411849, 2]
        assert result[42] == [443085, 0]

        code, result = self.execute('select * from category_0 where match("защитное стекло") limit 1;')
        assert len(result) == 1
        assert result[0] == [411849, 2]

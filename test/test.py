from wrapper import SearchServer, SearchClient

import pytest
import requests


class TestTemplate:
    def setup(self):
        self.server = SearchServer()
        self.server.run()
        self.client = SearchClient(self.server)

    def teardown(self):
        self.server.shutdown()

    def execute(self, query):
        return self.client.execute(query)

    def ping(self):
        return self.client.ping()


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

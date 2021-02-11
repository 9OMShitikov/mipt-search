from .wrapper import *


class TestTemplate:
    server = None
    client = None

    def setup(self):
        self.server = SearchServer()
        self.server.run()
        self.client = SearchClient(self.server)

    def teardown(self):
        self.server.shutdown()

    def execute(self, query, proto=Proto.SQL):
        return self.client.execute(query, proto)

    def ping(self):
        return self.client.ping()

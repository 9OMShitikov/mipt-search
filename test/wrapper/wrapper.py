from subprocess import Popen
import requests
from requests.adapters import HTTPAdapter
from requests.packages.urllib3.util.retry import Retry
import json
from enum import Enum

from .error import *


# proto section
class Proto(Enum):
    SQL = 1
    JSON = 2
    PROTOBUF = 3


class SearchServer:
    def __init__(self):
        self.fd = None
        self.proc = None

    def run(self):
        self.fd = open('server_log.txt', 'w')
        self.proc = Popen(["../cmake-build-debug/mipt-searchd",
                           "--config", "../etc/mipt_search.conf"]
                          , stderr=self.fd)
        poll = self.proc.poll()
        if poll is not None:
            assert False

    def shutdown(self):
        self.proc.terminate()
        self.fd.close()


class SearchClient:
    def __init__(self, server):
        self.server = server
        self.session = requests.Session()
        # retry = Retry(connect=3, backoff_factor=0.1, total=5)
        adapter = HTTPAdapter(max_retries=3)
        self.session.mount('http://', adapter)

        while True:
            try:
                self.ping()
                break
            except requests.exceptions.ConnectionError:
                continue

    def execute(self, query, proto=Proto.SQL):
        result = None
        if proto == Proto.SQL:
            result = self.session.get('http://127.0.0.1:5849/sql_command', data=query.encode("utf-8"))
        elif proto == Proto.JSON:
            result = self.session.get('http://127.0.0.1:5849/json_command', data=json.dumps(query).encode("utf-8"))

        if result is None:
            raise Exception("Server return 'None'")

        if result.status_code != 200:
            raise BadStatus("Server return '{}'".format(result.status_code))

        data = json.loads(result.content.decode("utf-8"))
        if data["error"] != "":
            raise Exception(data["error"])

        return data["data"]

    def ping(self):
        result = self.session.get('http://127.0.0.1:5849/ping')
        return result.status_code

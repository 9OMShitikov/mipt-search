from subprocess import Popen
import requests
from requests.adapters import HTTPAdapter
from requests.packages.urllib3.util.retry import Retry
import json


class SearchServer:
    def __init__(self):
        pass

    def run(self):
        self.fd = open('server_log.txt', 'w')
        self.proc = Popen(["../cmake-build-debug/mipt-searchd",
                           "--config", "../etc/mipt_search.conf",
                           "--index_dir", "../etc"], stderr=self.fd)

    def shutdown(self):
        self.proc.terminate()
        self.fd.close()


class SearchClient:
    def __init__(self, server):
        self.server = server
        self.session = requests.Session()
        retry = Retry(connect=3, backoff_factor=0.1)
        adapter = HTTPAdapter(max_retries=retry)
        self.session.mount('http://', adapter)

        while True:
            try:
                self.ping()
                break
            except requests.exceptions.ConnectionError:
                continue

    def execute(self, query):
        result = self.session.get('http://127.0.0.1:5849/sql_command', data=query.encode("utf-8"))
        print(result.content.decode("utf-8"))
        data = json.loads(result.content.decode("utf-8"))
        if data["error"] != "":
            raise Exception(data["error"])

        return result.status_code, data["data"]

    def ping(self):
        result = self.session.get('http://127.0.0.1:5849/ping')
        return result.status_code

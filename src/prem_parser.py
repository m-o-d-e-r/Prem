
from bs4 import BeautifulSoup

from prem_request import Request
from prem_types import Url, File



class Parser:
    def __init__(self, request: Request) -> None:
        self.__content: str = request.content
        self.__soup = BeautifulSoup(self.__content, "lxml")

    def find(self, tag: str):
        ...

    def find_all(self, tag: str):
        return self.__soup.find_all(tag)

#https://linux.die.net/man/5/vsftpd.conf


req = Request(Url("https://linux.die.net/man/5/vsftpd.conf"))
req.do_request()



with open("example.pdict", "w") as file:
    test = Parser(req)

    for i in test.find_all("dt"):
        file.write(i.get_text())


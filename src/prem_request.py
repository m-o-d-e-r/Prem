
import requests
from typing import Any

from prem_types import Url, File
from exceptions import RequestHandlerException



def __do_request_by_url(url: str) -> str:
    response = requests.get(url)
    return response.content


def __read_file(path_to_file: str) -> str:
    with open(path_to_file, "r") as file:
        return file.read()



SOURCE_HANDLERS = {
    Url: __do_request_by_url,
    File : __read_file
}



class Request:
    def __init__(self, source: Url | File) -> None:
        self.__source = source
        self.__content = ""

    def do_request(self) -> None:
        handler = SOURCE_HANDLERS.get(type(self.__source))

        if not handler:
            raise RequestHandlerException("Request handler is not exist for this type of source")

        print(self.__source.get_data())   
        self.__content = handler(self.__source.get_data())

    @property
    def content(self) -> str:
        return self.__content

    @property
    def source(self) -> Url | File:
        return self.__source

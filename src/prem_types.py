
from os.path import exists

from validators import url as url_validator

from exceptions import *



class BaseSource:
    def __init__(self, data: str = "") -> None:
        self._data = data

    def get_data(self) -> str:
        return self._data


class Url(BaseSource):
    def __init__(self, url: str = "") -> None:
        if not url_validator(url):
            raise BadUrlException("Url is not valid")

        super().__init__(url)


class File(BaseSource):
    def __init__(self, path_to_file: str = "") -> None:
        if not exists(path_to_file):
            raise BadFilePathException("File is not exists")

        super().__init__(path_to_file)



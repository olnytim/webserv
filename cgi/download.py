#!/usr/bin/python3

import os
import cgi
import cgitb

# Включаем отладку (можно убрать на продакшене)
cgitb.enable()

# Директория, где хранятся файлы для скачивания
download_dir = os.path.join(os.getcwd(), 'cgi', 'uploads')

# Создаем экземпляр FieldStorage для обработки данных из POST-запроса
form = cgi.FieldStorage()

# Получаем имя файла из POST-запроса
filename = form.getvalue('filename')

# Проверка, что файл существует
if filename:
    filepath = os.path.join(download_dir, filename)

    # Проверяем, существует ли файл на сервере
    if os.path.isfile(filepath):
        # Заголовки для загрузки файла
        print("Content-Type: application/octet-stream")
        print(f"Content-Disposition: attachment; filename={os.path.basename(filepath)}")
        print()

        # Чтение и отправка файла клиенту
        with open(filepath, 'rb') as file:
            sys.stdout.buffer.write(file.read())
    else:
        # Если файл не найден
        print("Content-Type: text/html;charset=utf-8")
        print()
        print(f"<html><body><h1>File '{filename}' not found</h1></body></html>")
else:
    # Если имя файла не было передано
    print("Content-Type: text/html;charset=utf-8")
    print()
    print("<html><body><h1>No file specified</h1></body></html>")

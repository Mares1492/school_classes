import sys

todos = []


def handle_save_todos(data):
    global todos
    todos = data
    print(todos, file=sys.stderr)


def handle_load_todos():
    return todos

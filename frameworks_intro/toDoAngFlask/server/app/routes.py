import sys

from flask import jsonify, request, render_template

from app import app
from app.todoController import handle_save_todos, handle_load_todos


@app.route('/')
@app.route('/index')
def index():
    return "Hello, World!"


@app.route("/todos", methods=["GET"])
def get_todos():
    return jsonify(handle_load_todos())


@app.route("/todos", methods=["POST"])
def save_todos():
    data = request.get_json()
    if not isinstance(data, list):
        return jsonify({"error": "Invalid data format (expected list)"}), 400
    handle_save_todos(data)
    return jsonify({"message": "Todos saved successfully"})


@app.route("/todos/render", methods=["GET"])
def render_todos():
    localtodos = handle_load_todos()
    print(localtodos, file=sys.stderr)
    return render_template('index.html', todos=localtodos)

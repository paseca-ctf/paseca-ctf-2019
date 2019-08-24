from flask import render_template, abort, session, request, send_from_directory, redirect, url_for, safe_join, send_file

from subway import app
from subway.gen_graph import gen_task
import json


@app.route('/tasks/<id>')
def return_task(id):
    filename = safe_join(app.config["SVG_DIR"], id + '.svg')
    print(filename)
    return send_file(filename)


@app.route('/', methods=["GET", "POST"])
def index():
    if "solved" not in session:
        session["solved"] = 0
    if not session.get("cur_task", None):
        id = gen_task([10] * 17)
        session["cur_task"] = id
    with open(safe_join(app.config["SVG_DIR"], session["cur_task"] + '.json')) as f:
        t = json.load(f)
    if request.method == "POST":
        return redirect(url_for("index"))
    return render_template("index.html", pos=t['pos'], start=t['start'])

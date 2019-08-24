from flask import render_template, session, request, redirect, url_for, safe_join, send_file, flash

from subway import app
from subway.gen_graph import gen_task
import json

tasks = [[2]*3, [3]*7, [5]*7, [11]*13, [15]*17]
#tasks = [[15]*17]

@app.route('/tasks/<id>')
def return_task(id):
    filename = safe_join(app.config["SVG_DIR"], id + '.svg')
    print(filename)
    return send_file(filename)

@app.route('/', methods=["GET", "POST"])
def index():
    if "solved" not in session:
        session["solved"] = 0
    if session["solved"] >= len(tasks):
        return "Thanks. Here is your payout: PASECA{bZZzZ_d1d_u_u53_dijkstra}"
    if not session.get("cur_task", None):
        id = gen_task(tasks[session["solved"]])
        session["cur_task"] = id
    with open(safe_join(app.config["SVG_DIR"], session["cur_task"] + '.json')) as f:
        t = json.load(f)
    if request.method == "POST":
        if "another" in request.form:
            session["cur_task"] = None
        else:
            ans = dict(request.form)
            del ans['submit']
            correct = True
            for station, dist in ans.items():
                try:
                    dist = int(dist)
                except ValueError:
                    flash(f"Distance on station {station} is not an integer")
                    correct = False
                    continue
                if dist != t['ans'][station]:
                    flash(f"Station {station} is not {dist} minutes away from {t['start']}")
                    correct = False
            if len(t['ans']) != len(ans):
                correct = False
                flash(f"Hey! Don't try to hack this task."
                f"The correct sollution does not envolve anything except using the browser")
            if correct:
                session["solved"] += 1
                session["cur_task"] = None
                flash("Good job!")
            print(ans)
        return redirect(url_for("index"))
    return render_template("index.html", pos=t['pos'], start=t['start'])

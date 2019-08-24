import secrets
import posixpath
from flask import Flask
import os

app = Flask(__name__)
if not os.path.exists(".secret"):
    open(".secret", "wb").write(secrets.token_bytes(16))
app.config["SECRET_KEY"] = open(".secret", "rb").read()
app.config["N_TASKS"] = 5
app.config["SVG_DIR"] = posixpath.abspath(posixpath.join(posixpath.curdir, "tasks"))

if app.config["DEBUG"]:
    app.config['TEMPLATES_AUTO_RELOAD'] = True

import subway.views

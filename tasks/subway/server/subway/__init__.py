import secrets
import posixpath
from flask import Flask
import os
import matplotlib
matplotlib.use('Agg')

secret_path = "/var/subway/.secret"

app = Flask(__name__)
if not os.path.exists(secret_path):
    open(secret_path, "wb").write(secrets.token_bytes(16))
app.config["SECRET_KEY"] = open(secret_path, "rb").read()
app.config["N_TASKS"] = 5
app.config["SVG_DIR"] = posixpath.abspath(posixpath.join(posixpath.curdir, "tasks"))

if app.config["DEBUG"]:
    app.config['TEMPLATES_AUTO_RELOAD'] = True

import subway.views

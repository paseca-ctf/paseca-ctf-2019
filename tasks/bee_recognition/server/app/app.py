import random
from random import shuffle
from uuid import uuid4
import json
from flask import (
    Flask,
    request,
    render_template,
    session, escape,
    jsonify,
    redirect, url_for)

import config
from data import *

app = Flask(__name__)
app.config.from_object(config)
K = 200
FLAG = 'paseca{u1tr4_be3_recOgn1T1ooon_m45ter}'


def get_bees_ids():
    shuffle(carniolan_ids)
    shuffle(russian_ids)
    shuffle(italian_ids)

    ids = carniolan_ids[:30] + russian_ids[:30] + italian_ids[:30]

    i = random.randint(0, 110)
    j = random.randint(0, 110 - i)
    k = 110 - i - j

    ids += carniolan_ids[30:30 + i]
    ids += russian_ids[30:30 + j]
    ids += italian_ids[30:30 + k]

    shuffle(ids)

    return list(map(int, ids))


def count_score(ans):
    score = 0

    for k, v in ans.items():
        score += int(answers[str(k) + '.png']) == int(v)
        print(answers[str(k) + '.png'], v)

    return score


@app.route('/')
def index():
    user_id = session.get('user_id')
    print(user_id)

    if not user_id:
        print('AAAA')
        uuid = str(uuid4())
        bees_ids = get_bees_ids()
        session['user_id'] = uuid
        session['bees_ids'] = bees_ids

    bees_ids = escape(session['bees_ids'])
    return render_template('index.html', bee_ids=bees_ids)


@app.route('/', methods=['POST'])
def post():
    user_id = session.get('user_id')
    bees_ids = session.get('bees_ids')

    if not user_id or not bees_ids:
        return jsonify({'success': False, 'accuracy': '0%', 'error': 'Invalid cookie'})

    try:
        ans = json.loads(request.form['answers'])

        if len(ans) != K:
            raise Exception

        ans = dict(zip(list(bees_ids), ans))
        score = count_score(ans)

        accuracy = score / K * 100
        if accuracy >= 85:
            return jsonify({'success': True, 'accuracy': f'{accuracy}%', 'flag': FLAG})
        else:
            return jsonify({'success': False, 'accuracy': f'{accuracy}%', 'error': 'Accuracy is too low'})


    except Exception as e:
        print(e)
        return jsonify({'success': False, 'accuracy': '0%', 'error': 'Invalid array'})

    finally:
        session.pop('user_id', None)
        session.pop('bees_ids', None)


if __name__ == '__main__':
    app.run(host='0.0.0.0')

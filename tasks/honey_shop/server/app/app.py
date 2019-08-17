from flask import Flask, render_template, request, session, escape, send_file, make_response

import config

app = Flask(__name__)
app.config.from_object(config)

price = {1: 5, 2: 10, 3: 12, 4: 15, 5: 1337}
items = {1: 'Linden honey', 2: 'Acacia honey', 3: 'Buckwheat honey', 4: 'Herbs honey',
         5: 'Flag honey: ' + str(open('app/flag.txt').read())}


@app.route('/', methods=['GET', 'POST'])
def index():
    msg = ''
    balance = session.get('balance')
    purchases = session.get('purchases')

    if not balance:
        session['balance'] = 1336
        balance = escape(session['balance'])

    if not purchases:
        session['purchases'] = []

    if request.method == 'POST':
        try:
            item = int(request.values.get('item'))
            if balance - price[item] >= 0:
                balance -= price[item]
                session['balance'] = balance
                session['purchases'].append(items[item])

                if len(session['purchases']) > 5:
                    session['purchases'] = session['purchases'][1:]

                msg = 'Successful!'
            else:
                msg = "You don't have enough money!"

        except Exception as e:
            print(e)
            pass
    purchases = list(reversed(session['purchases']))

    return render_template('index.html', balance=balance, msg=msg, purchases=purchases)


@app.route('/download', methods=['GET'])
def download():
    try:
        path = f"/home/shop/{request.args.get('image')}"

        if path.endswith('flag.txt') or path.endswith('.py') or path.endswith('.pyc'):
            return 'Not allowed'

        resp = make_response(open(path, 'rb').read())
        resp.headers['Content-Disposition'] = 'attachment; filename="' + path.split('/')[-1] + '"'
        return resp

    except Exception:
        return 'Unknown Error'


if __name__ == '__main__':
    app.run(host='0.0.0.0')

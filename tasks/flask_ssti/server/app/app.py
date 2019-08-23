import random
from flask import Flask, render_template_string, render_template, request

app = Flask(__name__)
app.config['SECRET_KEY'] = 'folow @osminogka.ann on instagram =)'

#fedya don't remember to remove this part on deploy so nobody will solve that hehe
'''
def encode(line, key, key2):
    return ''.join(chr(x ^ ord(line[x]) ^ ord(key[::-1][x]) ^ ord(key2[x])) for x in range(len(line)))
	
app.config['flag'] = encode('', 'OCd3vUye2dgl4bZDDc7yVV9PR4VvQpIU7o94CGO', '2qf4Fyqq1Ypp23q6sm5MLBnBLOS5bTswFuv9U1G')
'''

app.config['flag'] = '\rVTf\x18r;Y\x11P\x1b~\x1c;A69X@I\x08\x07cbf@\x0fv\x7fr;<~s\x11\x1alcS'

nicknames = ['˜”*°★☆★_%s_★☆★°°*', '%s ~♡ⓛⓞⓥⓔ♡~', '%s Вêчңø в øĤлâйĤé', '♪ ♪ ♪ %s ♪ ♪ ♪ ', '[♥♥♥%s♥♥♥]', '%s, kOтO®Aя )(оТеЛ@ ©4@$tьЯ', '♔%s♔', '[♂+♂=♥]%s[♂+♂=♥]']

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        try:
            p = request.values.get('nickname')
            id = random.randint(0, len(nicknames) - 1)
            if p != None:
                if '.' in p or '_' in p or '\'' in p:
                    return 'Your nickname contains restricted characters!'
                return render_template_string(nicknames[id] % p)

        except Exception as e:
            print(e)
            return 'Exception'
			
    return render_template('index.html')

if __name__ == '__main__':
    app.run(host='0.0.0.0')
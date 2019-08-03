import asyncio
from datetime import datetime
from itsdangerous import URLSafeSerializer, BadData
from starlette.applications import Starlette
from starlette.authentication import (
    AuthenticationBackend, AuthenticationError, SimpleUser, AuthCredentials, requires
)
from starlette.endpoints import HTTPEndpoint
from starlette.middleware.authentication import AuthenticationMiddleware
from starlette.responses import JSONResponse, RedirectResponse
from starlette.templating import Jinja2Templates

from totp import current_number, next_number, last_numbers

serializer = URLSafeSerializer('5y1HtjHuu2W3wvqVLrNEHKAQz8lfOKL4lbYUP8OksVUMnDnowCWjL6VvAZ4hjvRP')
templates = Jinja2Templates(directory='templates')
app = Starlette(debug=True)


class BasicAuthBackend(AuthenticationBackend):
    async def authenticate(self, request):
        if 'session' not in request.cookies:
            return

        auth = request.cookies['session']
        try:
            data = serializer.loads(auth)
            is_authorized, number = data['is_authorized'], data['number']
        except (ValueError, UnicodeDecodeError, BadData):
            raise AuthenticationError('Invalid auth')
        if not is_authorized:
            return

        return AuthCredentials(['authenticated']), SimpleUser(str(number))


app.add_middleware(AuthenticationMiddleware, backend=BasicAuthBackend())


def password_error():
    response = RedirectResponse('/')
    response.set_cookie('error_password', '1', httponly=True)
    return response


async def update_totp():
    while True:
        next_number()
        # print(current_number())
        await asyncio.sleep(30)


@app.on_event('startup')
async def startup():
    loop = asyncio.get_event_loop()
    loop.create_task(update_totp())


@app.route('/last-totps')
async def last_otp(request):
    return JSONResponse(last_numbers)


@app.route('/')
async def homepage(request):
    if request.user.is_authenticated:
        return RedirectResponse('/flag')

    error_password = 'error_password' in request.cookies
    response = templates.TemplateResponse('index.html', {'request': request, 'error': error_password})
    response.delete_cookie('error_password')
    return response


@app.route('/login')
class Login(HTTPEndpoint):
    async def post(self, request):
        if request.user.is_authenticated:
            return RedirectResponse('/flag')

        try:
            password = int((await request.form())['totp'])
        except (ValueError, KeyError):
            return password_error()

        if password == current_number():
            print('{} Got flag with {}'.format(datetime.now(), current_number()))
            session = serializer.dumps({'is_authorized': True, 'number': password})
            response = RedirectResponse('/flag')
            response.set_cookie('session', session, max_age=60*60, httponly=True)
            return response
        else:
            return password_error()


@app.route('/flag')
@requires('authenticated', redirect='homepage')
async def flag(request):
    return templates.TemplateResponse('flag.html', {'request': request})

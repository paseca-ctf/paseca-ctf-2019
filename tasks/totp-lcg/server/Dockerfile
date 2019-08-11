FROM tiangolo/uvicorn-gunicorn-starlette:python3.7-alpine3.8

RUN pip install --no-cache-dir jinja2 python-multipart itsdangerous

ENV PYTHONUNBUFFERED=1

COPY ./app /app

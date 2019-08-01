FROM tiangolo/uvicorn-gunicorn-starlette:python3.7

RUN pip install jinja2 python-multipart itsdangerous

ENV PYTHONUNBUFFERED=1

COPY ./app /app

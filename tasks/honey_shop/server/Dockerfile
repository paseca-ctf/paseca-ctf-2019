FROM python:alpine
WORKDIR /
COPY ./app /app
RUN pip install -r app/requirements.txt
CMD mkdir /home/shop ; cp app/static/images/* /home/shop ; python app/app.py

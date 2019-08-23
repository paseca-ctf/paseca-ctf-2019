FROM python:alpine
WORKDIR /app
COPY . .
ENV PYTHONUNBUFFERED=1
RUN pip install -r requirements.txt
CMD ["python", "app/app.py"]

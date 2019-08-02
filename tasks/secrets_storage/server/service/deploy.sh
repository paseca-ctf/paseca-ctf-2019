socat TCP-LISTEN:1337,fork,reuseaddr EXEC:'python /service/secretsstorage.py'

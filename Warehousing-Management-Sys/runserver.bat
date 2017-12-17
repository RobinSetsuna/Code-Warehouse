python manage.py makemigrations commodity_server
python manage.py migrate commodity_server
python manage.py makemigrations manager_server
python manage.py migrate manager_server
python manage.py makemigrations auth
python manage.py migrate auth
python manage.py makemigrations sessions
python manage.py migrate sessions
python manage.py runserver
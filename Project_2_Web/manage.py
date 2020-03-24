#!/usr/bin/env python
"""Django's command-line utility for administrative tasks."""
import os
import sys
from folder_management.application.app.base_application import *


def main():
    app = BaseApplication()

    os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'Project_2.settings')
    try:
        from django.core.management import execute_from_command_line
    except ImportError as exc:
        raise ImportError(
            "Couldn't import Django. Are you sure it's installed and "
            "available on your PYTHONPATH environment variable? Did you "
            "forget to activate a virtual environment?"
        ) from exc
    app.run()
    execute_from_command_line(sys.argv)




if __name__ == '__main__':
    main()

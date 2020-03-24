from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('base.py', views.base, name='base'),
    path('process', views.process, name='process')
]
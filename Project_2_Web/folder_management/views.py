from django.shortcuts import render

# Create your views here.


def index(request):
    return render(request, "folder_management/index.html", {})


def base(request):
    return render(request, "../../application/app/base.py", {})

def process(request):
    if request.method =="GET":
        operation = request.GET['operation']
        item_name = request.GET['item_name']
        print(operation)
        print(item_name)
        return render(request, "folder_management/application/app/base_application.py")



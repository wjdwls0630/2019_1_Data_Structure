print("""
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8" />
    <link rel="apple-touch-icon" sizes="76x76" href="static/assets/img/apple-icon.png">
    <link rel="icon" type="image/png" href="static/assets/img/favicon.png">
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
    <title>
        Material Kit by Creative Tim
    </title>
    <meta content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0, shrink-to-fit=no' name='viewport' />
    <!--     Fonts and icons     -->
    <link rel="stylesheet" type="text/css" href="https://fonts.googleapis.com/css?family=Roboto:300,400,500,700|Roboto+Slab:400,700|Material+Icons" />
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/latest/css/font-awesome.min.css">
    <!-- CSS Files -->
    <link href="static/assets/css/material-kit.css?v=2.0.5" rel="stylesheet" />
    <!-- CSS Just for demo purpose, don't include it in your project -->
    <link href="static/assets/demo/demo.css" rel="stylesheet" />
</head>
<body class="landing-page sidebar-collapse">
<button class="btn btn-round" data-toggle="modal" data-target="#management">
    <i class="material-icons">menu</i>Management

</button>

<div class="modal fade" id="management" tabindex="-1" role="">
    <div class="modal-dialog modal-login" role="document">
        <div class="modal-content">
            <div class="modal-header">
                <div class="card card-nav-tabs card-plain">
                    <div class="card-header card-header-rose card-header-primary ">
                        <div class="nav-tabs-navigation">
                            <div class="nav-tabs-wrapper">
                                <button type="button" class="close" data-dismiss="modal" aria-hidden="true">
                                    <i class="material-icons">clear</i>
                                </button>
                                <ul class="nav nav-pills nav-pills-rose" role="tablist">
                                    <li class="nav-item">
                                        <a class="nav-link active" data-toggle="tab" href="#add_item" aria-expanded="true">
                                            <i class="material-icons">add</i>
                                            Add
                                        </a>
                                    </li>
                                    <li class="nav-item">
                                        <a class="nav-link" data-toggle="tab" href="#delete_item" aria-expanded="false">
                                            <i class="material-icons">delete</i>
                                            Delete
                                        </a>
                                    </li>
                                    <li class="nav-item">
                                        <a class="nav-link" data-toggle="tab" href="#update_item" aria-expanded="false">
                                            <i class="material-icons">update</i>
                                            Update
                                        </a>
                                    </li>
                                </ul>

                            </div>
                        </div>

                    </div>
                </div>
            </div>
            <div class="modal-body">
                <p class="description text-center">Enter Item Name</p>
                <div class="card-body">
                    <div class="form-group bmd-form-group">
                        <div class="input-group">
                            <input type="text" class="form-control" placeholder="Item Name" name="target">
                        </div>
                    </div>
                    <div class="tab-content">
                        <div class="tab-pane" id="add_item">
                            <input class="form-check-input" type="radio" name="operation" value="add" required checked>
                            this item to add
                        </div>
                        <div class="tab-pane" id="delete_item">
                            <input class="form-check-input" type="radio" name="operation" value="delete" required >
                            this item to delete
                        </div>
                        <div class="tab-pane" id="update_item">
                            <input type="text" class="form-control" placeholder="Item Name to Update..." name="value" required>
                            <input class="form-check-input" type="radio" name="operation" value="update" required>
                            this item to update
                        </div>
                    </div>
                </div>
                <button type="button" class="btn btn-primary" onclick="send_command()">Submit</button>

            </div>
            <div class="modal-footer justify-content-center">
            </div>
        </div>
    </div>
</div>
</div>
<!--   Core JS Files   -->
<script src="static/assets/js/process.js" type="text/javascript"></script>
<script src="static/assets/js/core/jquery.min.js" type="text/javascript"></script>
<script src="static/assets/js/core/popper.min.js" type="text/javascript"></script>
<script src="static/assets/js/core/bootstrap-material-design.min.js" type="text/javascript"></script>
<script src="static/assets/js/plugins/moment.min.js"></script>
<!--	Plugin for the Datepicker, full documentation here: https://github.com/Eonasdan/bootstrap-datetimepicker -->
<script src="static/assets/js/plugins/bootstrap-datetimepicker.js" type="text/javascript"></script>
<!--  Plugin for the Sliders, full documentation here: http://refreshless.com/nouislider/ -->
<script src="static/assets/js/plugins/nouislider.min.js" type="text/javascript"></script>
<!--  Google Maps Plugin    -->
<script src="https://maps.googleapis.com/maps/api/js?key=YOUR_KEY_HERE"></script>
<!-- Control Center for Material Kit: parallax effects, scripts for the example pages etc -->
<script src="static/assets/js/material-kit.js?v=2.0.5" type="text/javascript"></script>

</body>
</html>


""")
command = js2py.eval_js(send_command_py)
print(command)

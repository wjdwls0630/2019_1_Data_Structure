function send_command() {
    var operation = document.getElementsByName('operation')
    var target = document.getElementsByName('target')
    var value = document.getElementsByName('value')
    return operation+' '+target+' '+value
}
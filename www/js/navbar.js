function initNavbar(path){
    navbar = document.getElementById("navbar");
    navbar.innerHtml = "";

    parts = path.split("/");
    parts = parts.filter(function(str){return str != ""}); 

    for (var i = 0; i < parts.length; i++){
        var a = document.createElement("a");
        a.appendChild(document.createTextNode(parts[i]))
        a.href="https://www.google.com";    // todo correct path

        var li = document.createElement("li");
        li.appendChild(a);

        navbar.appendChild(li);
    }
}
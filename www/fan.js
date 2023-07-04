function fan_onload(){
    setInterval(update, 24);
}

var rotation = 0;

function update(){
    rotation += 5;
    document.getElementById("fan").setAttribute("transform","rotate("+rotation+")");
}


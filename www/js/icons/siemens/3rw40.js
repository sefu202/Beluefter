setInterval(siemens_3rw40_init, 500);

var lastColor = "red";

async function siemens_3rw40_init(){
    var q1 = document.getElementById("Q1");
    if (lastColor == "green"){
        lastColor = "black";
    }
    else{
        lastColor = "green";
    }
    q1.innerHTML = await siemens_3rw40(lastColor, "Motorstarter", "Q1");

}


async function siemens_3rw40(color, name, bmk){
    let x = await fetch("svg/icons/siemens/3rw40.svg");
    let svgContent = await x.text();
    svgContent = svgContent.replace("%BMK", bmk);
    svgContent = svgContent.replace("%NAME", name);
    svgContent = svgContent.replace("%COLOR", color);
    return svgContent;
  
}


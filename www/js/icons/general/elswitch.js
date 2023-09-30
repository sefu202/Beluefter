

async function elswitch_init(){
    var sw = document.getElementById("K1");
    var sw2 = document.getElementById("K2");

    sw.innerHTML = await elswitch("red", "Rev Sw 1", "K1", false);
    sw2.innerHTML = await elswitch("black", "Rev Sw 2", "K2", true);
}


async function elswitch(color, name, bmk, bClosed){
    let x = await fetch("svg/icons/general/elswitch.svg");
    let svgContent = await x.text();
    svgContent = svgContent.replace("%BMK", bmk);
    svgContent = svgContent.replace("%NAME", name);
    svgContent = svgContent.replace("%COLOR", color);
    if (bClosed){
        svgContent = svgContent.replace("%CLOSED", "visible");
        svgContent = svgContent.replace("%OPEN", "hidden");
    }
    else{
        svgContent = svgContent.replace("%CLOSED", "hidden");
        svgContent = svgContent.replace("%OPEN", "visible");
    }
    return svgContent;
  
}


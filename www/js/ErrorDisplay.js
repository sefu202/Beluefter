function initErrorDisplay(){
    setErrorDisplay("xxxx", "NO DATA", "red");
    Updater.registerUpdateFunc(updateErrorDisplay);
}

function setErrorDisplay(errorNumber, errorText, color){
    var errorDisplay = document.getElementById("errorDisplay");
    errorDisplay.innerHTML = errorNumber + " " + errorText;
    errorDisplay.style.borderColor = color;
}

function updateErrorDisplay(j){
    obj = j["errorDisplay"];
    setErrorDisplay(obj.errorNumber, obj.errorText, obj.color)
}
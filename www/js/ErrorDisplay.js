function initErrorDisplay(){
    setErrorDisplay("xxxx", "NO DATA", "red")
}

function setErrorDisplay(errorNumber, errorText, color){
    var errorDisplay = document.getElementById("errorDisplay");
    errorDisplay.innerHTML = errorNumber + " " + errorText;
    errorDisplay.style.borderColor = color;
}
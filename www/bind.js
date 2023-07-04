var bindingsMap = {};

function bind_init(){
    fetchValues();
    var timer = setInterval(fetchValues, 1000);

    bind("motorspeed", "innerHtml", "speed");
    bind("motorspeed2", "innerHtml", "speed");
    bind("btnAuto", "visible", "btnAutoVisible");
    bind("btnAuto", "active", "btnAutoActive");
    bind("btnAuto", "enabled", "btnAutoEnabled");
}

function setBoundValue(elementId, attributeId, value){
    switch(attributeId){
        case "innerHtml":
            document.getElementById(elementId).innerHTML = value;
        break;
        case "visible":
            var elementClassList = document.getElementById(elementId).classList;
            var isVisible = !elementClassList.contains("hmibutton-invisible");

            if (value && !isVisible){
                elementClassList.remove("hmibutton-invisible");
            }
            else if (!value && isVisible){
                elementClassList.add("hmibutton-invisible");
            }

        break;
        case "active":
            var elementClassList = document.getElementById(elementId).classList;
            var isActive = elementClassList.contains("hmibutton-active");

            if (value && !isActive){
                elementClassList.add("hmibutton-active");
            }
            else if (!value && isActive){
                elementClassList.remove("hmibutton-active");
            }

        break;
        case "enabled":
            var elementClassList = document.getElementById(elementId).classList;
            var isEnabled = !elementClassList.contains("hmibutton-disabled");

            if (value && !isEnabled){
                elementClassList.remove("hmibutton-disabled");
            }
            else if (!value && isEnabled){
                elementClassList.add("hmibutton-disabled");
            }

        break;
    }
}

async function fetchValues(){
    let x = await fetch("Api.json");
    let y = await x.text();
    
    var j = JSON.parse(y);

    for (var i = 0; i < j.length; i++){
        processVariable(j[i].varName, j[i].varValue);
    }
}

function bind(elementId, elementAttribute, bindVariable){
    if (!bindingsMap[bindVariable]){
        bindingsMap[bindVariable] = [];
    }
    bindingsMap[bindVariable].push({elementId:elementId, elementAttribute:elementAttribute});
    console.log(bindingsMap);
}

function processVariable(variableName, variableValue){
    var boundElements = bindingsMap[variableName];
    for (var i = 0; i < boundElements.length; i++){
        setBoundValue(boundElements[i].elementId, boundElements[i].elementAttribute, variableValue);
    }
}

function createChart(){
    const chart = new frappe.Chart("#chart", {  // or a DOM element,
        // new Chart() in case of ES6 module with above usage
title: "My Awesome Chart",
data: data,
type: 'axis-mixed', // or 'bar', 'line', 'scatter', 'pie', 'percentage'
height: 250,
colors: ['#7cd6fd', '#743ee2']
})
}


class Chart{
    constructor(id, elem){
        this.id = id;
        this.style = "fill:white;stroke:red;stroke-width:4"
        this.element = elem;
    }
}

var charts = new Map;

function chart(id){
    var chart
    if (!charts.has(id)){
        var elem = document.getElementById(id);
        chart = new Chart(id, elem);
        charts.set(id, chart);
    }
    else{
        chart = charts.get(id);
    }



    console.log(document.getElementById(chart.id));
}
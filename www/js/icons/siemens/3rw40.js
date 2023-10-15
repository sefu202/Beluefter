async function Siemens3RW40OnLoad(){    
    var icons = document.getElementsByClassName("Siemens3RW40");
    for (var idx = 0; idx < icons.length; idx++){
        Siemens3RW40.registerIcon(icons[idx].id);
    }

    let x = await fetch("svg/icons/siemens/3rw40.svg");
    Siemens3RW40.svgContentTempl = await x.text();
}

/**
 * @brief Siemens 3Rw40
 */
class Siemens3RW40{

    /**
     * @brief Creates a new button
     * @param {string} iconId element id
     */
    constructor(iconId){
        this.iconId = iconId;
        this.element = document.getElementById(iconId)
        this.actualColor = "black";

        Updater.registerUpdateFunc(this.update.bind(this))
        
        this.intervalId = setInterval(this.doBlink.bind(this), 500);
    }

    /**
     * @brief Update the icon state
     */
    update(j){
        let obj = j[this.iconId]
        this.color = obj.color;
        this.name = obj.name;
        this.bmk = obj.bmk;
        this.blink = obj.blink;
        this.siemens_3rw40();
    }

    siemens_3rw40(){
        let svg = Siemens3RW40.svgContentTempl;
        svg = svg.replace("%BMK", this.bmk);
        svg = svg.replace("%NAME", this.name);
        svg = svg.replace("%COLOR", this.actualColor);
        this.element.innerHTML = svg;
    }

    doBlink(){
        if (this.blink){
            if (this.actualColor == this.color){
                this.actualColor = "black";
            }
            else{
                this.actualColor = this.color;
            }
        }
        else {
            this.actualColor = this.color;
        }
        this.siemens_3rw40();
    }

    static iconMap = new Map();   // All created icons by id
    static svgContentTempl = ""; // SVG Content Template


    static registerIcon(iconId){
        var icon = new Siemens3RW40(iconId);
        Siemens3RW40.iconMap.set(iconId, icon);
    }
}

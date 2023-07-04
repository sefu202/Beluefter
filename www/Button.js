
function buttonOnLoad(){
    var btns = document.getElementsByClassName("hmibutton");
    for (var idx = 0; idx < btns.length; idx++){
        Button.registerButton(btns[idx].id);
    }
}

/**
 * @brief HMI Button Class
 */
class Button{

    /**
     * @brief Creates a new button
     * @param {string} buttonId element id
     */
    constructor(buttonId){
        this.buttonId = buttonId;
        this.element = document.getElementById(buttonId)
        this.isOn = false;
        this.isDisabled = false;
        this.isVisible = true;
        this.errorOnClick = "";

        //document.getElementById(buttonId).onclick = event => {this.onClick();};
        this.element.onclick = this.onClick.bind(this);
        this.update();

        this.intervalId = setInterval(this.update.bind(this), 2000);
    }

    /**
     * @brief Update the button state
     */
    async update(){
        let x = await fetch("http://192.168.1.105:64969/"+this.buttonId);
        let y = await x.text();
        let obj = JSON.parse(y);
        
        this.isOn = obj.isOn;
        this.isActive = obj.isActive;
        this.isDisabled = obj.isDisabled;
        this.isVisible = obj.isVisible;
        this.errorOnClick = obj.errorOnClick;
        this.setButtonStyles();
    }

    /**
     * @brief Sets button styles according to its state
     */
    setButtonStyles(){
        this.setButtonStyle(this.isOn, "hmibutton-active");
        this.setButtonStyle(this.isDisabled, "hmibutton-disabled");
        this.setButtonStyle(!this.isVisible, "hmibutton-invisible");
    }

    /**
     * @brief sets / removes class from button
     * @param {bool} value true = set / false = unset class
     * @param {*} classname classname for style
     */
    setButtonStyle(value, classname){
        if (value){
            this.element.classList.add(classname);
        }
        else{
            this.element.classList.remove(classname);
        }
    }

    /**
     * @brief Execute click action
     */
    async onClick(){
        if (this.isDisabled){
            alert(this.errorOnClick);
            return;
        }
        this.isOn = !this.isOn;
        let x = await fetch("http://192.168.1.105:64969/"+this.buttonId, {method: "POST", body: JSON.stringify(this.isOn)});
        this.update();

        this.setButtonStyles();
    }

    static buttonMap = new Map();   // All created buttons by id

    /**
     * @brief Registers a button by id
     * @param {string} buttonId Button element Id
     */
    static registerButton(buttonId){
        var btn = new Button(buttonId);
        Button.buttonMap.set(buttonId, btn);
    }
}

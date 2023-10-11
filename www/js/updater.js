function updater(){
    Updater.getUpdater();
}

function postUpdate(obj){
    Updater.getUpdater().postUpdate(obj);
}

class Updater{

    constructor(){
        this.setup();
    }

    async setup(){

        let x = await fetch("backendConf.json");
        let y = await x.text();
        let j = JSON.parse(y);

        if (window.location.pathname.indexOf(j.removePrefix) == 0) {
            this.url = j.addPrefix + window.location.pathname.substring(j.removePrefix.length);
        }
        this.url = this.url.substr(0, this.url.lastIndexOf(".html")) + j.postfix;
        this.intervalId = setInterval(this.update.bind(this), j.updateRate);
    }

    async update(){
        let x = await fetch(this.url);
        let y = await x.text();
        let j = JSON.parse(y);
        
        for (let i = 0; i < Updater.updateFuncs.length; i++){
            try {
                Updater.updateFuncs[i](j);
            } catch(err) {
                console.error(err);
            }
        }
    }

    async postUpdate(obj){
        console.log(this.url);
        let x = await fetch(this.url, {method: "POST", body: JSON.stringify(obj)});
    }

    static updateFuncs = [];

    static updater;

    static getUpdater(){
        if (Updater.updater == null){
            Updater.updater = new Updater;
        }
        return Updater.updater;
    }

    static registerUpdateFunc(updateFunc){
        Updater.updateFuncs.push(updateFunc);
    }
}
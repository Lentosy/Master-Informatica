/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

function toonPlanten() {
    var kleur = document.getElementById("kleur").value;
    var request = initRequest();
    request.open("GET","http://localhost:8080/PlantService/Planten/"+kleur,true);
    request.onreadystatechange = function(){
        plantenInHtml(request);
    };
    request.send(null);
}

function initRequest() {
    return new XMLHttpRequest();
}

function plantenInHtml(request) {
    if (request.readyState == 4 && request.status == 200) {
        var overzicht = document.getElementById("planten");
        var planten = JSON.parse(request.responseText);
        overzicht.innerHTML = "Gevonden planten<br>";
        for (var i = 0; i < planten.length; i++) {
            overzicht.innerHTML += planten[i].naam + " " + planten[i].prijs + "<br> " 
                + "<img src='figuren/"+planten[i].bestandAfbeelding+"' width='150'><br>";
        }
    }
    
}

